//
// Created by pierre on 12/17/25.
//

#include "lib/container/Array.hpp"
#include "lib/vga/vga.hpp"
#include "lib/vga/VGAMonitor.hpp"
#include "lib/keyboard/keyboardHandler.hpp"
#include "lib/logging/logging.hpp"



extern "C" void k_main() {
    // create screens and assign vga page
    container::Array<vga::VGAMonitor, 4> g_monitors{};
    g_monitors[0].init(0);
    g_monitors[1].init(1);
    g_monitors[2].init(2);
    g_monitors[3].init(3);

    // set first screen as current
    decltype(g_monitors)::iterator g_current_monitor = g_monitors.begin();
    g_monitor = &(*g_current_monitor);

    for (unsigned i = 0; i < g_monitors.size(); ++i) {
        auto &monitor = g_monitors[i];
        g_current_monitor = g_monitors.begin() + i;
        g_monitor = &(*g_current_monitor);

        logging::set_logger(monitor);

        monitor << vga::color::color_set::CYAN_ON_BLACK;
        monitor << "           ,--.                                        ,--,               " << vga::endl;
        monitor << "       ,--/  /|    ,---,.  .--.--.                   ,--.'|      ,----,   " << vga::endl;
        monitor << R"(    ,---,': / '  ,'  .' | /  /    '.              ,--,  | :    .'   .' \  )" << vga::endl;
        monitor << "    :   : '/ / ,---.'   ||  :  /`. /     ,---,.,---.'|  : '  ,----,'    | " << vga::endl;
        monitor << "    |   '   ,  |   |   .';  |  |--`    ,'  .' |;   : |  | ;  |    :  .  ; " << vga::endl;
        monitor << "    '   |  /   :   :  :  |  :  ;_    ,---.'   ,|   | : _' |  ;    |.'  /  " << vga::endl;
        monitor << R"(    |   ;  ;   :   |  |-, \  \    `. |   |    |:   : |.'  |  `----'/  ;   )" << vga::endl;
        monitor << R"(    :   '   \  |   :  ;/|  `----.   \:   :  .' |   ' '  ; :    /  ;  /    )" << vga::endl;
        monitor << R"(    |   |    ' |   |   .'  __ \  \  |:   |.'   \   \  .'. |   ;  /  /-,   )" << vga::endl;
        monitor << R"(    '   : |.  \'   :  '   /  /`--'  /`---'      `---`:  | '  /  /  /.`|   )" << vga::endl;
        monitor << R"(    |   | '_\.'|   |  |  '--'.     /                 '  ; |./__;      :   )" << vga::endl;
        monitor << R"(    '   : |    |   :  \    `--'---'                  |  : ;|   :    .'    )" << vga::endl;
        monitor << "    ;   |,'    |   | ,'                              '  ,/ ;   | .'       " << vga::endl;
        monitor << "    '---'      `----'                                '--'  `---'          "<< vga::endl;
        monitor << vga::color::color_set::WHITE_ON_BLACK;

        logging::debug("monitor {}", i);
    }

    g_current_monitor = g_monitors.begin();
    logging::set_logger(*g_current_monitor);
    g_monitor = &(*g_current_monitor);

    logging::info("Welcome to KFS:");
    logging::info("Credits:");
    logging::info("\t- pducloux: aka 'magic ultra (sexy ?) unicorn ninja'");
    logging::info("\t- hedubois: aka '?'");

    while (true) {
        kbd::handler(g_monitors, g_current_monitor);
    }
}
