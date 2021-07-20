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

#include "catch2/catch.hpp"
#include "kernel/klibc/stdio/stdio.h"

TEST_CASE("Test sprintf parses characters correctly") {
    using namespace kernel::lib;

    const auto * format = "example %cexample exam%cple %c%c test";
    char buffer[34];
    const int32_t count = sprintf(buffer, format, 'a', 'b', 'c', 'd');
    CHECK(count == 33);

    CHECK_THAT(buffer, Catch::Matchers::Equals("example aexample exambple cd test"));
}