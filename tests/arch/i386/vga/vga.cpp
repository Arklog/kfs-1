//
// Created by alice on 07/01/2026.
//

#include "catch2/catch_all.hpp"

#include "arch/i386/vga/vga.hpp"

TEST_CASE("t_vga_char", "[libvga]") {
    SECTION("background color") {
        vga::t_vga_char vga_char('A', vga::color::BLACK, vga::color::WHITE);

        REQUIRE(vga_char.get_background() == vga::color::WHITE);
        REQUIRE(vga_char.get_foreground() == vga::color::BLACK);

        vga_char.set_background(vga::color::BLUE);
        REQUIRE(vga_char.get_background() == vga::color::BLUE);

        vga_char.data.color = vga::color::RED << 4 | vga::color::GREEN;
        REQUIRE(vga_char.get_background() == vga::color::RED);
        REQUIRE(vga_char.get_foreground() == vga::color::GREEN);

        vga_char.set_color(vga::color::BLACK, vga::color::CYAN);
        REQUIRE(vga_char.get_foreground() == vga::color::BLACK);
        REQUIRE(vga_char.get_background() == vga::color::CYAN);
    }

    SECTION("color set") {
        vga::t_vga_char c{};

        c.data.color = vga::color::BLACK_ON_WHITE;
        REQUIRE(c.get_foreground() == vga::color::BLACK);
        REQUIRE(c.get_background() == vga::color::WHITE);

        c.data.color = vga::color::CYAN_ON_BLACK;
        REQUIRE(c.get_foreground() == vga::color::CYAN);
        REQUIRE(c.get_background() == vga::color::BLACK);

        c.data.color = vga::color::GREEN_ON_BLACK;
        REQUIRE(c.get_foreground() == vga::color::GREEN);
        REQUIRE(c.get_background() == vga::color::BLACK);

        c.data.color = vga::color::RED_ON_BLACK;
        REQUIRE(c.get_foreground() == vga::color::RED);
        REQUIRE(c.get_background() == vga::color::BLACK);

        c.data.color = vga::color::WHITE_ON_BLACK;
        REQUIRE(c.get_foreground() == vga::color::WHITE);
        REQUIRE(c.get_background() == vga::color::BLACK);

        c.data.color = vga::color::BROWN_ON_BLACK;
        REQUIRE(c.get_foreground() == vga::color::BROWN);
        REQUIRE(c.get_background() == vga::color::BLACK);
    }
}
