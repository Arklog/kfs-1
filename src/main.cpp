//
// Created by pierre on 12/17/25.
//

#include "lib/container/Array.hpp"
#include "lib/vga/vga.hpp"
#include "lib/vga/VGAMonitor.hpp"
#include "lib/keyboard/keyboardHandler.hpp"
#include "lib/logging/logging.hpp"



extern "C" void k_main() {
    container::Array<vga::VGAMonitor, 4> g_monitors{};
    g_monitors[0].set_page(0);
    g_monitors[1].set_page(1);
    g_monitors[2].set_page(2);
    g_monitors[3].set_page(3);

    decltype(g_monitors)::iterator g_current_monitor = g_monitors.begin();
    g_monitor = &(*g_current_monitor);

    auto &monitor = *g_monitor;
    monitor.init();
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
//
//    g_current_monitor++;
//    g_monitor = &(*g_current_monitor);
//
//    logging::info("prout");


    for (int i = 0; i < 4; ++i) {
        logging::set_logger(g_monitors[i]);
        logging::info("monitor {}", i);
    }
    while (true) {
        kbd::handler(g_monitors, g_current_monitor);
    }
}
