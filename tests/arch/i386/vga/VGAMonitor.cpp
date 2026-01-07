//
// Created by alice on 07/01/2026.
//

#include "arch/i386/vga/vga.hpp"
#include "arch/i386/vga/VGAMonitor.hpp"
#include "arch/i386/vga/VGADisplay.hpp"
#include "catch2/catch_all.hpp"

TEST_CASE("VGADisplay", "[vga]") {
    vga::t_vga_char test_buff[25 *80];
    vga::VGAMonitor monitor;
    vga::VGADisplay::vga = test_buff;
    monitor.init();

    char first_line[80] = "first first first first first first first first first first first first first  ";

    char test_line[80] = "test test test test test test test test test test test test test test test test";

    monitor << first_line << test_line << test_line << test_line << test_line
            << test_line << test_line << test_line << test_line << test_line
            << test_line << test_line << test_line << test_line << test_line
            << test_line << test_line << test_line << test_line << test_line
            << test_line << test_line << test_line << test_line << test_line;

    REQUIRE(test_buff[0].data.ascii == 'f');

    monitor << test_line;
    REQUIRE(test_buff[0].data.ascii == 't');
}


TEST_CASE("VGAMonitor color modifier", "[vga]") {
    vga::t_vga_char test_buff[25 *80];
    vga::VGAMonitor monitor;
    vga::VGADisplay::vga = test_buff;
    monitor.init();

    monitor << "T" << vga::VGAColorChange{vga::color::BLACK, vga::color::CYAN} << "est";
    REQUIRE(test_buff[0].data.color == 15);
    REQUIRE(test_buff[1].data.color == 48);

    REQUIRE(test_buff[0].get_foreground() == vga::color::WHITE);
    REQUIRE(test_buff[1].get_background() == vga::color::BLACK);
}
