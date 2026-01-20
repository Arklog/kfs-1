//
// Created by pierre on 12/23/25.
//

#ifndef KFS_1_LOG_HPP
#define KFS_1_LOG_HPP

#ifndef LOG_BUFFER_SIZE
# define LOG_BUFFER_SIZE 1024
#endif

#include "arch/i386/vga/vga.hpp"
#include "lib/format/format.hpp"

namespace logging {
    using t_logger_color = vga::color::color_set::t_color_set;

    class LoggerBase {
    public:
        virtual LoggerBase& operator<<(const char *) = 0;
        virtual LoggerBase& operator<<(t_logger_color) = 0;
    };

    template<typename T>
    class LoggerWrapper: public LoggerBase {
    public:
        LoggerWrapper(): _logger{} {}
        LoggerWrapper(T* logger_interface): _logger(logger_interface) {};

        LoggerWrapper& operator <<(const char *str) override {
            *_logger << str;
            return *this;
        }

        LoggerWrapper& operator<<(t_logger_color color) override {
            *_logger << color;
            return *this;
        }

    private:
        T *_logger;
    };

    using t_logger       = LoggerBase;

    extern t_logger *g_logger;

    /**
     * The log level type
     */
    typedef enum {
        DEBUG = 0,
        INFO  = DEBUG + 1,
        WARN  = INFO + 1,
        ERROR = WARN + 1,
    } t_log_level;

    /**
     * A map of t_log_level to t_logger_color, allow to determine the color to be used when printing log message
     */
    extern const t_logger_color log_color_map[4];

    /**
     * A map of t_log_level to const char *, allow to determine the message to display when printing log message
     */
    extern const char *log_message_map[4];

    /**
     * Set the global logging instance
     *
     * @tparam The LoggerWrapper underlying type
     * @param logger
     */
     template<typename T>
     void set_logger(T& logger) {
         static LoggerWrapper<T> static_logger;
         static_logger = LoggerWrapper<T>{&logger};
         g_logger = &static_logger;
     }

    /**
     * Get the global logging instance
     *
     * @return
     */
    t_logger &get_logger();

    /**
     * Log a message of log_level level to the logger instance provided by set_logger
     *
     * @tparam TArgs
     * @param log_level The log level
     * @param format    The format string
     * @param args      The arguments for the format string
     *
     * @return The number of character written
     */
    template<typename... TArgs>
    int printk(t_log_level log_level, const char *format, TArgs... args) {
        static char buffer[LOG_BUFFER_SIZE];
        auto &      logger = get_logger();

        logger << "["
#ifndef KFS_HOST_TEST
                << log_color_map[log_level]
#endif
                << log_message_map[log_level]
#ifndef KFS_HOST_TEST
                << vga::color::color_set::DEFAULT
#endif
                << "]: ";

        auto endbuffer = format::fmt(buffer, format, args...);

        logger << buffer << "\n";
        return endbuffer - buffer + 9 + 1;
    }

    /**
     * Log a debug message
     *
     * @tparam TArgs
     * @param format    The format string
     * @param args      The format string's arguments
     *
     * @return The number of character written
     */
    template<typename... TArgs>
    int debug(const char *format, TArgs... args) {
        return printk(DEBUG, format, args...);
    }

    /**
     * Log an info message
     *
     * @tparam TArgs
     * @param format    The format string
     * @param args      The format string's arguments
     *
     * @return The number of character written
     */
    template<typename... TArgs>
    int info(const char *format, TArgs... args) {
        return printk(INFO, format, args...);
    }

    /**
     * Log a warning message
     *
     * @tparam TArgs
     * @param format    The format string
     * @param args      The format string's arguments
     *
     * @return The number of character written
     */
    template<typename... TArgs>
    int warn(const char *format, TArgs... args) {
        return printk(WARN, format, args...);
    }

    /**
     * Log an error message
     *
     * @tparam TArgs
     * @param format    The format string
     * @param args      The format string's arguments
     *
     * @return The number of character written
     */
    template<typename... TArgs>
    int error(const char *format, TArgs... args) {
        return printk(ERROR, format, args...);
    }
}

#endif //KFS_1_LOG_HPP
