; Copyright (C) 2021 David Price - All Rights Reserved
; This file is part of HephaistOS.
;
; HephaistOS is free software: you can redistribute it and/or modify
; it under the terms of the GNU General Public License as published by
; the Free Software Foundation, either version 3 of the License, or
; (at your option) any later version.
;
; HephaistOS is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; GNU General Public License for more details.
;
; You should have received a copy of the GNU General Public License
; along with HephaistOS.  If not, see <https://www.gnu.org/licenses/>.

; Definitions of methods that can be called by external code.
global loadIdtTable

; Takes a pointer to a IDT size and address (in that order) and loads it into the idt register.
loadIdtTable:
                mov             eax, [esp+4]                    ; Get the pointer to the IDT, passed as a parameter on the stack
                lidt            [eax]                           ; Load the new IDT pointer
                ret