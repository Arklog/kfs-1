//
// Created by alice on 14/01/2026.
//

#include "arch/i386/vga/vga.hpp"
#include "arch/i386/vga/VGAMonitor.hpp"
#include "arch/i386/vga/VGADisplay.hpp"
#include "catch2/catch_all.hpp"

TEST_CASE("VGACursor", "[vga]") {
    static uint8_t test_buff[25 * 80 * 2];
    vga::VGADisplay::vga = reinterpret_cast<vga::t_vga_char*>(test_buff);
    vga::VGADisplay::testing = true;
    vga::VGAMonitor monitor;
    monitor.init();

    monitor << "test1" << vga::endl;
    monitor << "test2" << vga::endl;
    monitor << "test3" << vga::endl;
    monitor << "test4" << vga::endl;
    monitor << "test5" << vga::endl;
    monitor << "test6" << vga::endl;
    monitor << "test7" << vga::endl;
    monitor << "test8" << vga::endl;
    monitor.backspace();
    REQUIRE(monitor._cursor.line == 7);
    //REQUIRE(monitor._cursor.column == monitor._buffer.line_length(7));
}