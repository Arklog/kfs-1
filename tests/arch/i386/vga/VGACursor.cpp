//
// Created by alice on 14/01/2026.
//

#include "arch/i386/vga/vga.hpp"
#include "arch/i386/vga/VGAMonitor.hpp"
#include "arch/i386/vga/VGADisplay.hpp"
#include "catch2/catch_all.hpp"

TEST_CASE("VGACursor", "[vga]") {
    static uint8_t test_buff[25 * 80 * 2];
    vga::VGACursor cursor;

    cursor.set(10, 24);
    cursor.newline();
    REQUIRE(cursor.line == 11);
    REQUIRE(cursor.column == 0);
    cursor.back(24);
    REQUIRE(cursor.column == 24);
    cursor.advance();
    REQUIRE(cursor.column == 25);
    cursor.up(32);
    REQUIRE(cursor.line == 9);
    REQUIRE(cursor.column == 25);
    cursor.up(15);
    REQUIRE(cursor.column == 15);
    REQUIRE(cursor.line == 8);
    cursor.down(8);
    REQUIRE(cursor.column == 8);
    REQUIRE(cursor.line == 9);
    cursor.advance(8);
    REQUIRE(cursor.column == 0);
    REQUIRE(cursor.line == 10);
}