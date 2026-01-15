//
// Created by pierre on 12/23/25.
//

#include "logging.hpp"

namespace logging {
    const t_logger_color log_color_map[4] = {
            vga::color::color_set::CYAN_ON_BLACK,
            vga::color::color_set::WHITE_ON_BLACK,
            vga::color::color_set::BROWN_ON_BLACK,
            vga::color::color_set::RED_ON_BLACK
    };

    const char *log_message_map[4] = {
            "DEBUG",
            "INFO ",
            "WARN ",
            "ERROR"
    };

    t_logger *g_logger = nullptr;

    t_logger &get_logger() {
        return *g_logger;
    }
}
