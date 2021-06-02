#include "includes/keyboard.h"

KeyboardDriver::KeyboardDriver(InterruptManager* Manager):InterruptHandler(0x21, Manager), DataPort(0x60), CommandPort(0x64){
    while(CommandPort.Read() & 0x1)
        DataPort.Read();
    CommandPort.Write(0xAE); // activate interrupts
    CommandPort.Write(0x20); // gget current state of keyboard
    uint8_t status = (DataPort.Read() | 1) & ~0x10;
    CommandPort.Write(0x60); //set/change state
    DataPort.Write(status);
    DataPort.Write(0xF4);
}
KeyboardDriver::~KeyboardDriver(){

}

void printf(char*);

uint32_t KeyboardDriver::HandleInterrupt(uint32_t esp){
    uint8_t key = DataPort.Read();

    if(key < 0x80){
        switch(key){
            case 0x45:
            case 0xC5:
            case 0xFA:
                break;
            default:
                char* foo = "KEYBOARD 0x00";
                char* hex = "0123456789ABCDEF";
                foo[11] = hex[(key >> 4) & 0x0F];
                foo[13] = hex[key & 0x0F];
                printf(" ");
                printf(foo);
                printf(" ");
        }
    }
    return esp;
}