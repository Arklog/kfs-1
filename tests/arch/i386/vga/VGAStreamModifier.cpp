//
// Created by pierre on 12/20/25.
//

#include "catch2/catch_all.hpp"
#include "arch/i386/vga/VGAStreamModifier.hpp"

TEST_CASE("VGAStreamColorModifier", "[vga]") {
    vga::t_vga_char c{0};
    vga::modifier::VGAStreamColorModifier mod1{1};
    vga::modifier::VGAStreamColorModifier mod2{vga::color::WHITE, vga::color::BLACK};

    mod1(c.data.color);
    REQUIRE(c.data.color == 1);

    mod2(c.data.color);
    REQUIRE(c.get_foreground() == vga::color::WHITE);
    REQUIRE(c.get_background() == vga::color::BLACK);
}

TEST_CASE("VGAStramBackgroundModifier", "[vga]") {
    vga::t_vga_char c{0};
    c.set_foreground(vga::color::WHITE);
    c.set_background(vga::color::RED);

    vga::modifier::VGAStreamBackgroundModifier mod1{vga::color::BLUE};
    vga::modifier::VGAStreamBackgroundModifier mod2{3};
    vga::modifier::VGAStreamBackgroundModifier mod3{0xff};

    mod1(c.data.color);
    REQUIRE(c.get_background() == vga::color::BLUE);
    REQUIRE(c.get_foreground() == vga::color::WHITE);

    mod2(c.data.color);
    REQUIRE(c.get_background() == static_cast<vga::color::t_vga_color>(3));
    REQUIRE(c.get_foreground() == vga::color::WHITE);

    // check no overflow
    mod3(c.data.color);
    REQUIRE(c.get_foreground() == vga::color::WHITE);
}

TEST_CASE("VGAStreamForegroundModifier", "[vga]") {
    vga::t_vga_char c{0};
    c.set_foreground(vga::color::WHITE);
    c.set_background(vga::color::RED);

    vga::modifier::VGAStreamForegroundModifier mod1{vga::color::BLUE};
    vga::modifier::VGAStreamForegroundModifier mod2{3};
    vga::modifier::VGAStreamForegroundModifier mod3{0xff};

    mod1(c.data.color);
    REQUIRE(c.get_foreground() == vga::color::BLUE);
    REQUIRE(c.get_background() == vga::color::RED);

    mod2(c.data.color);
    REQUIRE(c.get_foreground() == static_cast<vga::color::t_vga_color>(3));
    REQUIRE(c.get_background() == vga::color::RED);

    // check no overflow
    mod3(c.data.color);
    REQUIRE(c.get_background() == vga::color::RED);
}