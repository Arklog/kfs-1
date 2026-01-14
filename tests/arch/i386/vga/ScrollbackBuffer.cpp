//
// Created by alice on 13/01/2026.
//


#include "arch/i386/vga/vga.hpp"
#include "arch/i386/vga/VGAMonitor.hpp"
#include "arch/i386/vga/VGADisplay.hpp"
#include "catch2/catch_all.hpp"

static const vga::ScrollbackBuffer::buffer_type::value_type empty_line{};
static const vga::ScrollbackBuffer::buffer_type::value_type test_line{vga::t_vga_char{'t', vga::color::color_set::WHITE_ON_BLACK},
                                                                    vga::t_vga_char{'e', vga::color::color_set::WHITE_ON_BLACK},
                                                                    vga::t_vga_char{'s', vga::color::color_set::WHITE_ON_BLACK},
                                                                    vga::t_vga_char{'t', vga::color::color_set::WHITE_ON_BLACK}};

TEST_CASE("ScrollbackBuffer", "[vga]") {
    SECTION("clear") {
        vga::ScrollbackBuffer buffer;
        auto &_buffer = buffer.get_buffer();

        _buffer.push_bash(test_line);
        _buffer.push_bash(test_line);

        REQUIRE(buffer.line_count()  == 2);
        REQUIRE(buffer.line(0).size() == 4);
        REQUIRE(buffer.line(1).size() == 4);

        buffer.clear();
        REQUIRE(buffer.line_count()  == 0);
    }

    SECTION("write") {
        vga::ScrollbackBuffer buffer;
        vga::VGACursor cursor{};
        auto &_buffer = buffer.get_buffer();

        _buffer.push_bash(test_line);

        buffer.write(cursor, vga::t_vga_char{'A', vga::color::color_set::WHITE_ON_BLACK});
        REQUIRE(buffer.line_count() == 1);
        REQUIRE(buffer.line(0).size() == 5);
        REQUIRE(buffer.line(0)[0].data.ascii == 'A');
        REQUIRE(buffer.line(0)[0].data.color == vga::color::color_set::WHITE_ON_BLACK);
    }

    SECTION("newline") {
        vga::ScrollbackBuffer buffer;
        vga::VGACursor cursor{};
        auto &_buffer = buffer.get_buffer();

        _buffer.push_bash(test_line);

        buffer.newline(0, 2);
        REQUIRE(buffer.line_count() == 2);
        REQUIRE(buffer.line(0).size() == 2);
        REQUIRE(buffer.line(1).size() == 2);
        REQUIRE(buffer.line(0)[0].data.ascii == 't');
        REQUIRE(buffer.line(0)[1].data.ascii == 'e');
        REQUIRE(buffer.line(1)[0].data.ascii == 's');
        REQUIRE(buffer.line(1)[1].data.ascii == 't');
    }

    SECTION("merge_lines") {
        { // basic merge
            vga::ScrollbackBuffer buffer;
            vga::VGACursor cursor{};
            auto &_buffer = buffer.get_buffer();

            _buffer.push_bash(test_line);
            _buffer.push_bash(test_line);

            buffer.merge_lines(0, 1);
            REQUIRE(buffer.line_count() == 1);
            REQUIRE(buffer.line(0).size() == 8);
            REQUIRE(buffer.line(0)[0].data.ascii == 't');
            REQUIRE(buffer.line(0)[1].data.ascii == 'e');
            REQUIRE(buffer.line(0)[2].data.ascii == 's');
            REQUIRE(buffer.line(0)[3].data.ascii == 't');
            REQUIRE(buffer.line(0)[4].data.ascii == 't');
            REQUIRE(buffer.line(0)[5].data.ascii == 'e');
            REQUIRE(buffer.line(0)[6].data.ascii == 's');
            REQUIRE(buffer.line(0)[7].data.ascii == 't');
        }

        { // overflow
            vga::ScrollbackBuffer buffer;
            vga::VGACursor cursor{};
            auto &_buffer = buffer.get_buffer();

            vga::ScrollbackBuffer::line_type long_line;
            while (long_line.available_space()) {
                long_line.push_bash(vga::t_vga_char{'x', vga::color::color_set::WHITE_ON_BLACK});
            }

            _buffer.push_bash(test_line);
            _buffer.push_bash(long_line);
            buffer.merge_lines(0, 1);

            REQUIRE(buffer.line_count() == 2);
            REQUIRE(buffer.line(0).size() == vga::VGA_WIDTH);
            REQUIRE(buffer.line(1).size() == 4);

            for (const auto& i: {_buffer[0].begin() + 4, _buffer[0].end()}) {
                REQUIRE(i->data.ascii == 'x');
                REQUIRE(i->data.color == vga::color::color_set::WHITE_ON_BLACK);
            }

            for (const auto& i: _buffer[1]) {
                REQUIRE(i.data.ascii == 'x');
                REQUIRE(i.data.color == vga::color::color_set::WHITE_ON_BLACK);
            }
        }
    }
}