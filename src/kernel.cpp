#include "includes/types.h"
#include "includes/gdt.h"

void printf(char* str) {
    uint16_t* VideoMemory = (uint16_t*)0xb8000;

    for(int i = 0; str[i] != '\0'; ++i)
        VideoMemory[i] = (VideoMemory[i] & 0xFF00) | str[i];
}

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors() {

    GlobalDescriptorTable gdt;

    for(constructor* i = &start_ctors; i != &end_ctors; i++)
        (*i)();
}

extern "C" void KernelBoot(void* multiboot_structure, uint32_t BootIdentifier) {
    printf("Hello world!");

    while(1);
}