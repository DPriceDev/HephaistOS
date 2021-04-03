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

#include "video_buffer_display.h"
#include "drivers/io/io.h"

const kernel::uint32_t &kernel::VideoBufferDisplay::getWidth() const {
    return width;
}

const kernel::uint32_t &kernel::VideoBufferDisplay::getHeight() const {
    return height;
}

kernel::uint32_t
kernel::VideoBufferDisplay::setDisplayBuffer(const Display::Character *character, uint32_t length) const {
    auto *videoPointer = reinterpret_cast<unsigned char *>(address::videoMemoryAddress);
    unsigned int index = 0;
    for (; index < screenBufferLength; index += 2) {
        videoPointer[index] = character->character;
        videoPointer[index + 1] = character->textColour;
        character++;

        if (index == length) {
            break;
        }
    }
    return index / 2;
}

kernel::uint32_t kernel::VideoBufferDisplay::setDisplayBuffer(const Display::Character *character,
                                                              uint32_t length,
                                                              uint32_t x,
                                                              uint32_t y) const {
    auto *videoPointer = reinterpret_cast<unsigned char *>(address::videoMemoryAddress);
    uint32_t index = 0;
    uint32_t offset = (y * characterWidth) + (x * 2);
    for (; index < screenBufferLength ; index += 2) {
        videoPointer[index + offset] = character->character;
        videoPointer[index + offset + 1] = character->textColour;
        character++;

        if (index >= length) {
            break;
        }
    }
    return index / 2;
}

void
kernel::VideoBufferDisplay::clearDisplayBuffer(Display::Colour textColour, Display::Colour backgroundColour) const {
    uint8_t *videoPointer = reinterpret_cast<unsigned char *>(address::videoMemoryAddress);
    for (unsigned int index = 0; index < screenBufferLength; index += 2) {
        videoPointer[index] = ' ';
        videoPointer[index + 1] = textColour | backgroundColour << 4;
    }
}

void kernel::VideoBufferDisplay::setCursorPosition(uint32_t x, uint32_t y) const {
    static const uint8_t offset = 8;
    uint32_t cursorPosition = (y * width) + x;

    outportb(address::videoCursorLowAddress, 0x0F);
    outportb(address::videoCursorHighAddress, cursorPosition);
    outportb(address::videoCursorLowAddress, 0x0E);
    outportb(address::videoCursorHighAddress, cursorPosition >> offset);
}

void kernel::VideoBufferDisplay::showCursor() const {
    outportb(address::videoCursorLowAddress, 0x0A);
    outportb(address::videoCursorHighAddress, (inportb(address::videoCursorHighAddress) & 0xC0) | cursorStart);
    outportb(address::videoCursorLowAddress, 0x0B);
    outportb(address::videoCursorHighAddress, (inportb(address::videoCursorHighAddress) & 0xE0) | cursorEnd);
}

void kernel::VideoBufferDisplay::hideCursor() const {
    outportb(address::videoCursorLowAddress, 0x0A);
    outportb(address::videoCursorHighAddress, 0x20);
}

kernel::Display::Cursor kernel::VideoBufferDisplay::getCursorPosition() const {
    static const uint8_t offset = 8;

    outportb(address::videoCursorLowAddress, 0x0F);
    uint16_t position = inportb(address::videoCursorHighAddress);

    outportb(address::videoCursorLowAddress, 0x0E);
    position += static_cast<uint16_t>(inportb(address::videoCursorHighAddress)) << offset;

    return Display::Cursor{
            position % width,
            position / width,
    };
}