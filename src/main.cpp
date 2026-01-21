//
// Created by pierre on 12/17/25.
//


#include "lib/vga/vga.hpp"
#include "lib/vga/VGAMonitor.hpp"
#include "lib/keyboard/keyboardHandler.hpp"
#include "lib/logging/logging.hpp"

extern "C" void k_main() {
    vga::VGAMonitor  monitor{};
    g_monitor = &monitor;
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

    while (true) {
        kbd::handler();
    }
}
