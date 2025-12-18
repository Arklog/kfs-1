//
// Created by pierre on 12/18/25.
//

#include "catch2/catch_all.hpp"
#include "arch/i386/vga/VGACursor.hpp"

#include "arch/i386/vga/vga.hpp"

TEST_CASE("VGACursor basic functionality", "[vga][VGACursor]") {
    vga::VGACursor cursor;

    REQUIRE(cursor.begin() == reinterpret_cast<vga::VGACursor::iterator>(0xB8000));
    REQUIRE(cursor.end() == reinterpret_cast<vga::VGACursor::iterator>(0xB8000 + 80 * 25 * sizeof(vga::t_vga_char)));
    REQUIRE(cursor.cbegin() == reinterpret_cast<vga::VGACursor::const_iterator>(0xB8000));
    REQUIRE(cursor.cend() == reinterpret_cast<vga::VGACursor::const_iterator>(0xB8000 + 80 * 25 * sizeof(vga::t_vga_char)));
    REQUIRE(*(cursor.pos()) == reinterpret_cast<vga::VGACursor::iterator>(0xB8000));
    REQUIRE(cursor.ipos() == 0);

    SECTION("CURSOR INCREMENT") {
        auto pos = cursor.pos();
        ++(*pos); // Move cursor forward by one character
        REQUIRE(cursor.ipos() == 1);
    }

    SECTION("CURSOR next_line") {
        cursor.next_line();
        REQUIRE(cursor.ipos() == 80);
        cursor.next_line();
        REQUIRE(cursor.ipos() == 160);
    }
}