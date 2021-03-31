;////////////////////////////////////////////////////////////////
;/ Title:           boot
;/ Filename:        boot.asm
;/ Last Changed:    23/10/19
;/ Created:         23/10/19
;/ Author:          David Price
;/
;/ Description:
;/
;/
;/ Changes:
;/      - 09:46 23/10/19: File Created.
;/      - 10:59 31/03/21: Refactored to use multi-boot header
;////////////////////////////////////////////////////////////////
global loader
global stack_ptr

extern kernelMain

stackSize:      equ             0x4000

; ------------------------------------------------------------- ;
; Multi-boot Header
; Variables
MODULEALIGN:    equ             1 << 0
MEMINFO:        equ             1 << 1
FLAGS:          equ             MODULEALIGN | MEMINFO
MAGIC:          equ             0x1BADB002
CHECKSUM:       equ             -(MAGIC + FLAGS)

; header
section .mbheader
align 4
MultiBootHeader:
                dd              MAGIC
                dd              FLAGS
                dd              CHECKSUM

; ------------------------------------------------------------- ;
section .text

loader:
                mov             esp, stack+stackSize
                push            eax
                push            ebx
                call            kernelMain
                cli

; ------------------------------------------------------------- ;
; Halts the CPU
halt:
  hlt
  jmp halt

; ------------------------------------------------------------- ;
; clears the screen. FIX?
clrScreen:
                xor	            bx, bx		                    ; A faster method of clearing BX to 0
                ret


; ------------------------------------------------------------- ;
; Converts an integer to a string value.
intToString:
                xor             si, si                          ; Clear the di register to hold the resultant string.
intToString.loop:
;               add             si, 9
                mov             byte [si], 0
                mov             bx, 10

intToString.next_digit:
                xor             dx, dx                          ; Clear previous remainder flag dx
                div             bx                              ; eax /= 10
                add             dl, '0'                         ; Convert the remainder to ASCII
                dec             si                              ; store characters in reverse order
                mov             [si], dl
                test            ax, ax
                jnz             intToString.next_digit          ; Repeat until eax==0
                mov             ax,si
                ret

; ------------------------------------------------------------- ;
; Prints a char to the screen. (precede: mov al, 'A')
printChar:
	            mov	            ah, 0x0e
	            int	            0x10
                ret

; ------------------------------------------------------------- ;
; prints a string to the screen. (precede: mov si, "string")
printString:
                mov             ah, 0x0e                        ; 0x0e means 'Write Character in TTY mode'
printString.loop:
                lodsb
                or			al, al				                ; al=current character
                jz			printString.finished			    ; null terminator found
                int			10h
                jmp			printString.loop
printString.finished:
                ret

newLine:
                mov         DL, 10                              ;printing new line
                mov         AH, 02h
                int	        21h
                mov         DL, 13
                mov         AH, 02h
                int	        21h
                ret
; ------------------------------------------------------------- ;
; BSS Memory Section
section .bss
align           4
stack:
resb            stackSize
stack_ptr:


;global loader
;
;extern kernalMain
;
;MODULEALIGN equ 1<<0
;MEMINFO equ 1<<1
;FLAGS equ MODULEALIGN | MEMINFO
;MAGIC equ 0x1BADB002
;CHECKSUM equ -(MAGIC + FLAGS)
;
;section .mbheader
;align 4
;MultiBootHeader:
;  dd MAGIC
;  dd FLAGS
;  dd CHECKSUM
;
;; Start the bootloader Program.
;start: jmp loader
;
;; Variables.
;msgTitle	db	"HephaestOS Alpha v1.0.", 0
;msgAuthor	db	"Written by David Price.", 0
;CR equ 0DH
;LF equ 0AH
;

;; Load the 32 bit bootloader.
;loader:
;	xor	ax, ax
;	mov	ds, ax
;	mov	es, ax
;
;    mov	si, msgTitle
;    call printString
;    call newLine
;    mov	si, msgAuthor
;    call printString
;
;    xor	ax, ax						                    ; clear ax
;	int	0x12						                    ; get the amount of KB from the BIOS
;    call intToString
;    call printString
;
;
;
;    jmp loader32
;
;loader32:
;    bits 32
;
;    mov esi,msgAuthor
;	mov ebx,0xb8000
;.loop:
;	lodsb
;	or al,al
;	jz halt
;	or eax,0x0100
;	mov word [ebx], ax
;	add ebx,2
;	jmp .loop
;
;    jmp halt
;
;; Stop the program.
;halt:
;    cli                                                 ; clear interrupt flag
;    hlt                                                 ; halt execution
;
;times 510 - ($-$$) db 0                                 ; pad remaining 510 bytes with zeroes
;dw 0xaa55                                               ; Boot Signiture