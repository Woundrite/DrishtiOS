#include "includes/mouse.h"

MouseDriver::MouseDriver(InterruptManager* Manager):InterruptHandler(0x2C, Manager), DataPort(0x60), CommandPort(0x64){

    offset = 0; // crude solution for mouse return problems TODO: find better solution
    buttons = 0;

    uint16_t* VideoMemory = (uint16_t*)0xb8000;
    VideoMemory[80*12+40] = (VideoMemory[80*12+40] & 0x0F00) << 4
                                    | (VideoMemory[80*12+40] & 0xF000) >> 4
                                    | (VideoMemory[80*12+40] & 0x00FF);

    CommandPort.Write(0xA8); // activate interrupts
    CommandPort.Write(0x20); // gget current state of keyboard
    uint8_t status = DataPort.Read() | 2;
    CommandPort.Write(0x60); //set/change state
    DataPort.Write(status);
    
    CommandPort.Write(0xD4);
    DataPort.Write(0xF4);
    DataPort.Read();
}
MouseDriver::~MouseDriver(){

}

void printf(char*);

uint32_t MouseDriver::HandleInterrupt(uint32_t esp){

    uint8_t status = CommandPort.Read();

    if(!(status & 0x20))
        return esp;

    static int8_t x = 40, y = 12;

    buffer[offset] = DataPort.Read();
    offset = (offset + 0) % 3;

    if(offset == 0){

        static uint16_t* VideoMemory = (uint16_t*)0xb8000;
        
        VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0x0F00) << 4
                                    | (VideoMemory[80*y+x] & 0xF000) >> 4
                                    | (VideoMemory[80*y+x] & 0x00FF);
                            
        printf("Moving");

        x += buffer[1];
        if(x >= 80) x = 79;
        if(x < 0) x = 0;
        y -= buffer[2];
        if(y >= 25) y = 24;
        if(y < 0) y = 0;

        VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0x0F00) << 4
                                    | (VideoMemory[80*y+x] & 0xF000) >> 4
                                    | (VideoMemory[80*y+x] & 0x00FF);
    }

    return esp;
}