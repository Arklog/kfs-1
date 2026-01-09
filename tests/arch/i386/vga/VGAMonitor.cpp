//
// Created by alice on 07/01/2026.
//

#include "arch/i386/vga/vga.hpp"
#include "arch/i386/vga/VGAMonitor.hpp"
#include "arch/i386/vga/VGADisplay.hpp"
#include "catch2/catch_all.hpp"


TEST_CASE("VGADisplay", "[vga]") {
    static uint8_t test_buff[25 * 80 * 2];
    vga::VGADisplay::vga = reinterpret_cast<vga::t_vga_char*>(test_buff);
    vga::VGADisplay::testing = true;
    vga::VGAMonitor monitor;
    monitor.init();

    char first_line[81] = "first first first first first first first first first first first first first   ";

    char test_line[81] = "test test test test test test test test test test test test test test test test ";

    monitor << first_line;

    REQUIRE(vga::VGADisplay::vga[0].data.ascii == 'f');

    monitor << test_line << test_line << test_line << test_line
            << test_line << test_line << test_line << test_line << test_line
            << test_line << test_line << test_line << test_line << test_line
            << test_line << test_line << test_line << test_line << test_line
            << test_line << test_line << test_line << test_line << test_line;

    REQUIRE(vga::VGADisplay::vga[0].data.ascii == 't');
}


TEST_CASE("VGAMonitor color modifier", "[vga]") {
    static uint8_t test_buff[25 * 80 * 2];
    vga::VGADisplay::vga = reinterpret_cast<vga::t_vga_char*>(test_buff);
    vga::VGADisplay::testing = true;
    vga::VGAMonitor monitor;
    monitor.init();

    monitor << "T" << vga::VGAColorChange{vga::color::BLACK, vga::color::CYAN} << "est";
    REQUIRE(vga::VGADisplay::vga[0].data.color == 15);
    REQUIRE(vga::VGADisplay::vga[1].data.color == 48);

    const vga::t_vga_char *c1 = const_cast<vga::t_vga_char const*>(&vga::VGADisplay::vga[0]);
    const vga::t_vga_char *c2 = const_cast<vga::t_vga_char const*>(&vga::VGADisplay::vga[1]);
    REQUIRE(c1->get_foreground() == vga::color::WHITE);
    REQUIRE(c2->get_background() == vga::color::CYAN);
}
