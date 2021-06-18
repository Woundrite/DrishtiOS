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

mov eax, cr4
or eax, 0x20
mov cr4, eax

mov edi, 0x300000

mov eax, 0x30100F
stosd
mov ecx, 0x03FF
xor eax, eax
rep stosd

mov eax, 0x30200F
stosd
mov ecx, 0x03FF
xor eax, eax
rep stosd

mov ecx, 0x0200
mov esi, 0x008B

map.loop: 
mov eax, esi
stosd
xor eax, eax
stosd
add esi, 0x200000
sub ecx, 1
jnz map.loop

mov eax, 0x300000
mov cr3, eax

mov ecx, 0xC0000080
rdmsr
or eax, 0x00000100
wrmsr

mov eax, cr0
or eax, 0x80000000
mov cr0, eax
jmp 0x30 kernel.long mode


[bits 64]
kernel.long mode:
call KernelBoot
jmp $ 