.set BOOTIDENTIFIER, 0x1badb002
.set FLAGS, (1<<0 | 1<<1)
.set CHECKSUM, -(BOOTIDENTIFIER + FLAGS)

.section .multiboot
    .long BOOTIDENTIFIER
    .long FLAGS
    .long CHECKSUM

.section .text
.extern KernelBoot
.extern callConstructors
.global loader

loader:
    mov $Kernel_Stack, %esp

    call callConstructors

    push %eax
    push %ebx
    call KernelBoot

_stop:
    cli
    hlt
    jmp _stop

.section .bss
.space 2*1024*1024 ; # 2MB

Kernel_Stack: