/* Copyright (C) 2021 David Price - All Rights Reserved
 * This file is part of HephaistOS.
 *
 * HephaistOS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HephaistOS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HephaistOS.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef SYS_DISPLAY_H
#define SYS_DISPLAY_H

//#include "drivers/io/IO.hpp"
#include "hardware/register_address.h"

namespace SYS {

    namespace DISP {

        const unsigned int WIDTH(80);                                    //
        const unsigned int D_WIDTH(WIDTH * 2);                           //
        const unsigned int HEIGHT(25);                                   //
        const unsigned int SCREEN_SIZE(WIDTH * HEIGHT);                  //

        const unsigned int DISPLAY_PAGES(8);                             //
        const unsigned int SCREEN_BUFFER_SIZE(DISPLAY_PAGES * WIDTH);    //
        const unsigned char BLANK(0x20);


//----------------------------------------------------------------------------//
// CURSOR FUNCTIONS //

// Function: MoveCursor
// Desc: Moves the on screen text mode 0 cursor (bios screen) to a specified
//       Location.
//
// inputs: x        - x coordinate of the cursor.
//         y        - y coordinate of the cursor.
//
        void MoveCursor(unsigned int x, unsigned int y) {
            unsigned char position = static_cast<unsigned char>((y * DISP::WIDTH) + x);

//            outportb(0x3D4, 0x0F);
//            outportb(0x3D5, position);
//
//            outportb(0x3D4, 0x0E);
//            outportb(0x3D5, position >> 8);
        }

// Function: MoveCursor
// Desc: Moves the on screen text mode 0 cursor (bios screen) to a specified
//       Location.
// inputs: pos      - combined x and y position of cursor.
//
        void MoveCursor(unsigned char pos) {
//            outportb(0x3D4, 0x0F);
//            outportb(0x3D5, pos);
//
//            outportb(0x3D4, 0x0E);
//            outportb(0x3D5, pos >> 8);
        }

//------------------------------------------------//
// Function: CursorPosition
// Desc: functions gets the cursor position for text mode 0 (BIOs screen) from
//       the port registers and returns it as an int.
//       This returns the Linear Position, (screen width * y) + x
//
// Output: int - returns the position of the cursor (linear position)

//
        unsigned int CursorPosition() {
//            outportb(0x3D4, 0x0F);
//            unsigned int pos = inportb(0x3D5);
//
//            outportb(0x3D4, 0x0E);
//            pos += static_cast<unsigned int>(inportb(0x3D5) << 8);
//
//            return pos;
            return 0;
        }


//----------------------------------------------------------------------------//
// Function: ScrollScreen
// Desc: 
//       
//
        void ScrollScreen() {
            auto dest_ptr = reinterpret_cast<unsigned short *>(address::videoMemoryAddress);
            auto source_ptr = reinterpret_cast<unsigned short *>(address::videoMemoryAddress + DISP::D_WIDTH);

//            SYS::memcpy(dest_ptr, source_ptr, (DISP::SCREEN_SIZE - 1) * 2);
        }

//----------------------------------------------------------------------------//
// Function: NewLine
// Desc: 
//       
//
        void NewLine() {
            unsigned int position = (DISP::CursorPosition() / DISP::WIDTH) + 1;

            DISP::MoveCursor(static_cast<unsigned char>(position * WIDTH));

            if (DISP::CursorPosition() >= DISP::SCREEN_SIZE) {
                DISP::ScrollScreen();
                DISP::MoveCursor(static_cast<unsigned char>(DISP::WIDTH * (DISP::HEIGHT - 1)));
            }
        }

//----------------------------------------------------------------------------//
// Function: ClearScreen
// Desc: 
//       
//
        void cls(unsigned char colour = 0x0F) {
            auto dest_ptr = reinterpret_cast<unsigned char *>(address::videoMemoryAddress);

            for (unsigned int c = 0; c < DISP::SCREEN_SIZE * 2; c += 2) {
                *dest_ptr++ = BLANK;
                *dest_ptr++ = colour;
            }

            DISP::MoveCursor(0);
        }

    }   // End of DISP namespace

//----------------------------------------------------------------------------//
// Function: PutStr
// Desc: While in text mode, this function will write to the screen the 
//       provided characters (char array), in the provided foreground and,
//       background textColour, at the cursor location.
//
// inputs: str      - char array holding characters to output to screen.
//         textColour   - int holding textColour value.
//
    void PutStr(const char *str, char fore_colour = 15 /*, int back_colour = 15 */) {
        // setup pointer to 0,0 location in the video memory.
        auto VideoMemory = reinterpret_cast<unsigned char *>(address::videoMemoryAddress);

        // while the is not empty.
        while (*str != 0) {
            // if the x cursor is off the screen, reset to zero and add a row.
            if (*str == '\n' || *str == '\r') {
                DISP::NewLine();
                str++;
                continue;
            }

            // update cursor location in the video memory pointer.
            VideoMemory = reinterpret_cast<unsigned char *>(address::videoMemoryAddress
                                                            + DISP::CursorPosition()
                                                            + DISP::CursorPosition());

            // add the characters value and increment both memory and characters.
            // add textColour value and increment the memory to next cursor location.
            *VideoMemory++ = static_cast<unsigned char>(*str++);
            *VideoMemory++ = static_cast<unsigned char>(fore_colour);

            DISP::MoveCursor(static_cast<unsigned char>(DISP::CursorPosition() + 1));

            if (DISP::CursorPosition() >= DISP::SCREEN_SIZE) {
                DISP::ScrollScreen();
                DISP::MoveCursor(static_cast<unsigned char>(DISP::WIDTH * (DISP::HEIGHT - 1)));
            }
        }
    }


} // End of SYS namespace
#endif