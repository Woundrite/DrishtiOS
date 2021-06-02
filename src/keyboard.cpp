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
            case 0x1E:
                printf("A");
                break;
            case 0x30:
                printf("B");
                break;
            case 0x2E:
                printf("C");
                break;
            case 0x20:
                printf("D");
                break;
            case 0x12:
                printf("E");
                break;
            case 0x21:
                printf("F");
                break;
            case 0x22:
                printf("G");
                break;
            case 0x23:
                printf("H");
                break;
            case 0x17:
                printf("I");
                break;
            case 0x24:
                printf("J");
                break;
            case 0x25:
                printf("K");
                break;
            case 0x26:
                printf("L");
                break;
            case 0x32:
                printf("M");
                break;
            case 0x31:
                printf("N");
                break;
            case 0x18:
                printf("O");
                break;
            case 0x19:
                printf("P");
                break;
            case 0x10:
                printf("Q");
                break;
            case 0x13:
                printf("R");
                break;
            case 0x1F:
                printf("S");
                break;
            case 0x14:
                printf("T");
                break;
            case 0x16:
                printf("U");
                break;
            case 0x2F:
                printf("V");
                break;
            case 0x11:
                printf("W");
                break;
            case 0x2D:
                printf("X");
                break;
            case 0x15:
                printf("Y");
                break;
            case 0x2C:
                printf("Z");
                break;
            case 0x02:
                printf("1");
                break;
            case 0x03:
                printf("2");
                break;
            case 0x04:
                printf("3");
                break;
            case 0x05:
                printf("4");
                break;
            case 0x06:
                printf("5");
                break;
            case 0x07:
                printf("6");
                break;
            case 0x08:
                printf("7");
                break;
            case 0x09:
                printf("8");
                break;
            case 0x0A:
                printf("9");
                break;
            case 0x0B:
                printf("0");
                break;
            case 0x39:
                printf(" ");
                break;
            case 0x38:
                printf(" ALT ");
                break;
            case 0x1D:
                printf(" CTRL ");
                break;
            case 0x3A:
                printf(" TAB ");
                break;
            case 0x2A:
                printf(" SHIFT ");
                break;
            case 0x01:
                printf(" ESC ");
                break;
            case 0x29:
                printf("`/~");
                break;
            case 0x3B:
                printf(" F1 ");
                break;
            case 0x3C:
                printf(" F2 ");
                break;
            case 0x3D:
                printf(" F3 ");
                break;
            case 0x3E:
                printf(" F4 ");
                break;
            case 0x3F:
                printf(" F5 ");
                break;
            case 0x40:
                printf(" F6 ");
                break;
            case 0x41:
                printf(" F7 ");
                break;
            case 0x42:
                printf(" F8 ");
                break;
            case 0x43:
                printf(" F9 ");
                break;
            case 0x44:
                printf(" F10 ");
                break;
            case 0x57:
                printf(" F11 ");
                break;
            // case 0x1E:
            //     printf(" F12 ");
            //     break;
            case 0x47:
                printf(" Home ");
                break;
            case 0x4F:
                printf(" End ");
                break;
            case 0x52:
                printf(" INSERT ");
                break;
            case 0x53:
                printf(" DELETE ");
                break;
            default:
                char* foo = "KEYBOARD 0x00";
                char* hex = "0123456789ABCDEF";
                foo[11] = hex[(key >> 4) & 0x0F];
                foo[12] = hex[key & 0x0F];
                printf(" ");
                printf(foo);
                printf(" ");
        }
    }
    return esp;
}