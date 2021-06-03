#include "includes/types.h"
#include "includes/gdt.h"
#include "includes/port.h"
#include "includes/interrupts.h"
#include "includes/driver.h"
#include "includes/keyboard.h"
#include "includes/mouse.h"

void printf(char* str) {
    uint16_t* VideoMemory = (uint16_t*)0xb8000;

    static uint8_t x = 0, y = 0;

    for(int i = 0; str[i] != '\0'; ++i){

        switch(str[i]){
            case '\n':
                y++;
                x = 0;
                break;
            default:
                VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | str[i];
                x++;
        }

        if(x >= 80){
            y++;
            x = 0;
        }

        if(y >= 25){
            
            for(y=0; y<25; y++)
                for(x=0; x<80; x++)
                    VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | ' ';
            x = 0;
            y = 0;
        }
    }
}

void PrintHex(uint8_t key){
    char* foo = "00";
    char* hex = "0123456789ABCDEF";
    foo[0] = hex[(key >> 4) & 0x0F];
    foo[1] = hex[key & 0x0F];
    printf(foo);
}

void PrintHex(char* str, uint8_t key){
    char* foo = "00";
    char* hex = "0123456789ABCDEF";
    foo[0] = hex[(key >> 4) & 0x0F];
    foo[1] = hex[key & 0x0F];
    printf(str);
    printf(foo);
}

class PrintKeyboardEventHandler : public KeyboardEventHandler{
    public:
        void OnKeyDown(char c){
            char* foo = " ";
            foo[0] = c;
            printf(foo);
        }
};

class MouseToConsole : public MouseEventHandler{

    int8_t x, y;

    public:

        MouseToConsole(){
            uint16_t* VideoMemory = (uint16_t*)0xb8000;
            x = 40;
            y = 12;
            VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0x0F00) << 4
                                  | (VideoMemory[80*y+x] & 0xF000) >> 4
                                  | (VideoMemory[80*y+x] & 0x00FF);
        }

        void OnMouseMove(int xOffset, int yOffset){
            static uint16_t* VideoMemory = (uint16_t*)0xb8000;
            
            VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0x0F00) << 4
                                        | (VideoMemory[80*y+x] & 0xF000) >> 4
                                        | (VideoMemory[80*y+x] & 0x00FF);

            x += xOffset;
            if(x >= 80) x = 79;
            if(x < 0) x = 0;
            y += yOffset;
            if(y >= 25) y = 24;
            if(y < 0) y = 0;

            VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0x0F00) << 4
                                        | (VideoMemory[80*y+x] & 0xF000) >> 4
                                        | (VideoMemory[80*y+x] & 0x00FF);
        }
};

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors() {
    for(constructor* i = &start_ctors; i != &end_ctors; i++)
        (*i)();
}

extern "C" void KernelBoot(void* multiboot_structure, uint32_t BootIdentifier) {
    printf("Hello world!");

    GlobalDescriptorTable gdt;
    InterruptManager Interrupts(&gdt);

    printf("\n[System]: Initializing Hardware\n");

    DriverManager driverManager;

    PrintKeyboardEventHandler KeyboardHandler;
    KeyboardDriver Keyboard(&Interrupts, &KeyboardHandler);
    driverManager.AddDriver(&Keyboard);

    MouseToConsole MouseHandler;
    MouseDriver Mouse(&Interrupts, &MouseHandler);
    driverManager.AddDriver(&Mouse);

    driverManager.ActivateAll();

    Interrupts.Activate();

    while(1);
}