//
// Created by alice on 13/01/2026.
//


#include "arch/i386/vga/vga.hpp"
#include "arch/i386/vga/VGAMonitor.hpp"
#include "arch/i386/vga/VGADisplay.hpp"
#include "catch2/catch_all.hpp"

TEST_CASE("ScrollbackBuffer", "[vga]") {
    static uint8_t test_buff[25 * 80 * 2];
    vga::VGADisplay::vga = reinterpret_cast<vga::t_vga_char*>(test_buff);
    vga::VGADisplay::testing = true;
    vga::VGAMonitor monitor;
    monitor.init();

    REQUIRE(monitor._buffer.line_count() == 0);
    monitor << "test11111111111";
    REQUIRE(monitor._buffer.line_count() == 1);


    monitor << "test2" << vga::color::color_set::BLACK_ON_WHITE;
    monitor << "test3" << vga::endl;
    monitor << "test4" << vga::endl;
    monitor << "test5" << vga::endl;
    monitor << "test6" << vga::endl;
    monitor << "test7" << vga::endl;
    monitor << "test8" << vga::endl;

    REQUIRE(monitor._buffer.line_length(0) ==  25);
    REQUIRE(monitor._buffer.line_length(1) ==  5);
    REQUIRE(monitor._buffer.line_length(2) ==  5);
    REQUIRE(monitor._buffer.line_length(3) ==  5);
    REQUIRE(monitor._buffer.line_length(4) ==  5);
    REQUIRE(monitor._buffer.line_length(5) ==  5);
    REQUIRE(monitor._buffer.line_length(6) ==  0);

    REQUIRE(monitor._buffer.line_count() == 7);
}