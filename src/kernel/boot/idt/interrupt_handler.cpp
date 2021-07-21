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

#include <kernel/drivers/video_buffer_display.h>
#include <kernel/terminal/Terminal.h>
#include "interrupt_handler.h"
#include "programmable_interrupt_controller.h"
#include "kernel/klibc/stdio.h"

namespace kernel::boot::idt {

    extern "C" void handleInterrupt(InterruptInfo interruptInfo) {
        VideoBufferDisplay display{};
        auto terminal = Terminal{display};

        if(interruptInfo.interruptCode != 0) {
            terminal.clear(Display::green); // todo: not working?
            terminal.println("Interrupt!");
            char text[24];
            lib::sprintf(text, "Interrupt code: %u", interruptInfo.interruptCode);
            terminal.println(text);

        }

        sendEoiFlag(interruptInfo.interruptCode);
    }

    extern "C" void handleException(ExceptionInfo exceptionInfo) {
        VideoBufferDisplay display{ };
        auto terminal = Terminal{ display };
        terminal.clear(Display::green); // todo: not working?

        terminal.println("Exception!");
        char text[24];
        lib::sprintf(text, "Exception code: %u", exceptionInfo.interruptCode);
        terminal.println(text);

        terminal.println(exceptionDescription[exceptionInfo.interruptCode]);

        while (true) { }
    }
}