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

#ifndef TEST
# define MONITOR_MACRO vga::VGAMonitor
# include "arch/i386/vga/VGAMonitor.hpp"
#else
# include <fstream>
# define MONITOR_MACRO std::ofstream
#endif

namespace logging {
    using t_logger       = MONITOR_MACRO;
    using t_logger_color = vga::color::t_color_set;

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
     * @param logger
     */
    void set_logger(t_logger &logger);

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
#ifndef TEST
                << vga::VGAColorChange(log_color_map[log_level])
#endif
                << log_message_map[log_level]
#ifndef TEST
                << vga::VGAColorChange(vga::color::DEFAULT)
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
