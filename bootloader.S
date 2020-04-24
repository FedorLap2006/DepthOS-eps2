/* .set os_stack_size equ 4096 * 1024 * 1024 + 500; in bytes

; BITS 32

; section .boot

; multiboot_header_magic_number equ 0x1BADB002
; multiboot_header_flags equ 0 | (1 << 1) | (1 << 0)
; ; multiboot_header_len equ multiboot_header_end - multiboot_header
; multiboot_header_checksum -(multiboot_magic_number + multiboot_flags)

; align 4

; multiboot_header:
; 	dd multiboot_header_magic_number
; 	dd multiboot_header_flags
; 	dd multiboot_header_checksum

; multiboot_header_end:

; section .bss

; align 4

; stack_space_root:
; 	resb os_stack_size
; stack_space_top:

; section .text

; global _os_entry_point

; _os_entry_point:
; 	mov esp, stack_space_top

; 	push ebx
; 	push eax

; 	call kmain

; 	cli
; .stop:
; 	hlt
; 	jmp .stop*/

.set OS_STACK_SIZE, 1000000

.section .boot

.align 4

.set BOOTH_FLAGS, 0 | (1 << 1) | (1 << 0)
.set BOOTH_MAGIC, 0x1BADB002
.set BOOTH_CHECKSUM, -(BOOTH_MAGIC + BOOTH_FLAGS)

boot_header:
	.long BOOTH_MAGIC
	.long BOOTH_FLAGS
	.long BOOTH_CHECKSUM


.section .bss, "aw", @nobits

stack_root:
	.skip OS_STACK_SIZE
stack_top:

.section .text

.align 4
.global _os_entry_point

// .extern set_up_gdt

.extern _gdt_init

// _protected_mode:
//  call _gdt_init
//  jmp $0x8, $1f
// 1:
//   ret

_os_entry_point:
	mov $stack_top, %esp

	push %ebx
	push %eax

//	call set_up_gdt
	// sti
	call kmain

	cli 
1:hlt
	jmp 1b
