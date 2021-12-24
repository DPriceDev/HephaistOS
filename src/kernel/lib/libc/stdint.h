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

#ifndef HEPHAIST_OS_KERNEL_LIB_STD_INT_H
#define HEPHAIST_OS_KERNEL_LIB_STD_INT_H

namespace kernel {
    using int8_t = char;
    using uint8_t = unsigned char;

    using int16_t = short;
    using uint16_t = unsigned short;

    using int32_t = int;
    using uint32_t = unsigned int;

    using int64_t = long long int;
    using uint64_t = unsigned long long int;

    using uintptr_t =  unsigned int;

    // todo: move to common file
    // Set of bit-masks that can be used to mask parts of an Integer.
    constexpr uint16_t Mask16Bit = 0xFFFF;
    constexpr uint8_t Mask8Bit = 0xFF;
    constexpr uint8_t Mask4Bit = 0xF;

    // todo: move to common file
    // Set of bit-offsets that can be used to move an integer by a power of 2.
    constexpr uint8_t Offset16Bit = 16U;
    constexpr uint8_t Offset24Bit = 24U;
}

#endif // HEPHAIST_OS_KERNEL_LIB_STD_INT_H
