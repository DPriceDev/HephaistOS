/* Copyright (C) 2022 David Price - All Rights Reserved
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

#ifndef HEPHAIST_OS_KERNEL_BOOT_MEMORY_MAP_H
#define HEPHAIST_OS_KERNEL_BOOT_MEMORY_MAP_H

#include "multiboot_info.h"

namespace kernel::boot::grub {

    struct [[gun::packed]] MemoryMap {
        uint32_t size;
    };

    /**
     *
     * @param info
     */
    auto constructMemoryMap(const MultiBootInfo * multiBootInfo) -> void;

}

#endif // HEPHAIST_OS_KERNEL_BOOT_MEMORY_MAP_H
