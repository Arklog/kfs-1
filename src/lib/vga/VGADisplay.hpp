//
// Created by alice on 21/12/2025.
//

#ifndef KFS_1_VGADISPLAY_HPP
#define KFS_1_VGADISPLAY_HPP

#include "include/stdint.hpp"
#include "lib/port/port.hpp"

#include "ScrollbackBuffer.hpp"
#include "VGACursor.hpp"
#include "VGAMonitor.hpp"


namespace vga {
    /**
     * Handler for the vga writting operations. Renders a window on the
     * scrollback buffer based on the current view line and displays the cursor.
     */

    class VGADisplay {
    public:
        /**
         * clear the vga buffer.
         */
        static void clear(int page);

        /**
         * Renders the current page.
         * @param page
         */
        static void render_page(int page);

        /**
         * Renders the current visible portion of the scrollback buffer into the vga buffer, at the given page.
         * @param buffer
         * @param view_line current first visible line.
         * @param page current vga page.
         */
        static void render(const ScrollbackBuffer &buffer, uint32_t view_line, int page);

        /**
         * handles display of the cursor on the screen.
         * @param cursor
         * @param view_line
         */
        static void update_hw_cursor(const VGACursor &cursor, uint32_t view_line);

/*     private: */
        /** pointer to the VGA text buffer (0xB8000). */
        static volatile t_vga_char* vga;
        static bool testing;
    };

}

#endif //KFS_1_VGADISPLAY_HPP