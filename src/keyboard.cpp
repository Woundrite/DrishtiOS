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

    static bool IsShiftPressed = false;
    switch(key){
        case 0x45: //Numlock
        case 0xC5:
        case 0xFA:
            break;
        case 0x1E:
            if(IsShiftPressed)
                printf("A");
            else
                printf("a");
            break;
        case 0x30:
            if(IsShiftPressed)
                printf("B");
            else
                printf("b");
            break;
        case 0x2E:
            if(IsShiftPressed)
                printf("C");
            else
                printf("c");
            break;
        case 0x20:
            if(IsShiftPressed)
                printf("D");
            else
                printf("d");
            break;
        case 0x12:
            if(IsShiftPressed)
                printf("E");
            else
                printf("e");
            break;
        case 0x21:
            if(IsShiftPressed)
                printf("F");
            else
                printf("f");
            break;
        case 0x22:
            if(IsShiftPressed)
                printf("G");
            else
                printf("g");
            break;
        case 0x23:
            if(IsShiftPressed)
                printf("H");
            else
                printf("h");
            break;
        case 0x17:
            if(IsShiftPressed)
                printf("I");
            else
                printf("i");
            break;
        case 0x24:
            if(IsShiftPressed)
                printf("J");
            else
                printf("j");
            break;
        case 0x25:
            if(IsShiftPressed)
                printf("K");
            else
                printf("k");
            break;
        case 0x26:
            if(IsShiftPressed)
                printf("L");
            else
                printf("l");
            break;
        case 0x32:
            if(IsShiftPressed)
                printf("M");
            else
                printf("m");
            break;
        case 0x31:
            if(IsShiftPressed)
                printf("N");
            else
                printf("n");
            break;
        case 0x18:
            if(IsShiftPressed)
                printf("O");
            else
                printf("o");
            break;
        case 0x19:
            if(IsShiftPressed)
                printf("P");
            else
                printf("p");
            break;
        case 0x10:
            if(IsShiftPressed)
                printf("Q");
            else
                printf("q");
            break;
        case 0x13:
            if(IsShiftPressed)
                printf("R");
            else
                printf("r");
            break;
        case 0x1F:
            if(IsShiftPressed)
                printf("S");
            else
                printf("s");
            break;
        case 0x14:
            if(IsShiftPressed)
                printf("T");
            else
                printf("t");
            break;
        case 0x16:
            if(IsShiftPressed)
                printf("U");
            else
                printf("u");
            break;
        case 0x2F:
            if(IsShiftPressed)
                printf("V");
            else
                printf("v");
            break;
        case 0x11:
            if(IsShiftPressed)
                printf("W");
            else
                printf("w");
            break;
        case 0x2D:
            if(IsShiftPressed)
                printf("X");
            else
                printf("x");
            break;
        case 0x15:
            if(IsShiftPressed)
                printf("Y");
            else
                printf("y");
            break;
        case 0x2C:
            if(IsShiftPressed)
                printf("Z");
            else
                printf("z");
            break;
        case 0x02:
            if(IsShiftPressed)
                printf("!");
            else
                printf("1");
            break;
        case 0x03:
            if(IsShiftPressed)
                printf("@");
            else
                printf("2");
            break;
        case 0x04:
            if(IsShiftPressed)
                printf("#");
            else
                printf("3");
            break;
        case 0x05:
            if(IsShiftPressed)
                printf("$");
            else
                printf("4");
            break;
        case 0x06:
            if(IsShiftPressed)
                printf("%");
            else
                printf("5");
            break;
        case 0x07:
            if(IsShiftPressed)
                printf("^");
            else
                printf("6");
            break;
        case 0x08:
            if(IsShiftPressed)
                printf("&");
            else
                printf("7");
            break;
        case 0x09:
            if(IsShiftPressed)
                printf("*");
            else
                printf("8");
            break;
        case 0x0A:
            if(IsShiftPressed)
                printf("(");
            else
                printf("9");
            break;
        case 0x0B:
            if(IsShiftPressed)
                printf(")");
            else
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
            printf(" CAPSLOCK ");
            break;
        case 0xAA:
        case 0xB6:
            IsShiftPressed = false;
            break;
        case 0x36:
        case 0x2A:
            IsShiftPressed = true;
            break;
        case 0x01:
            printf(" ESC ");
            break;
        case 0x29:
            if(IsShiftPressed)
                printf("~");
            else
                printf("`");
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
        case 0x58:
            printf(" F12 ");
            break;
        case 0x47:
            printf(" Home ");
            break;
        case 0x0E:
            printf(" BACKSPACE ");
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
        case 0x5B:
            printf(" WINKEY ");
            break;
        case 0x48:
            printf(" UP_ARROW ");
            break;
        case 0x50:
            printf(" DOWN_ARROW ");
            break;
        case 0x4D:
            printf(" LEFT_ARROW ");
            break;
        case 0x4B:
            printf(" RIGHT_ARROW ");
            break;
        case 0x0C:
            if(IsShiftPressed)
                printf("_");
            else
                printf("-");
            break;
        case 0x0D:
            if(IsShiftPressed)
                printf("+");
            else
                printf("=");
            break;
        case 0x0F:
            printf("\t");
            break;
        case 0x49:
            printf(" PAGE_UP ");
            break;
        case 0x51:
            printf(" PAGE_DOWN ");
            break;
        case 0x1C:
            printf(" \n ");
            break;
        case 0x35:
            if (IsShiftPressed)
                printf("?");
            else
                printf("/");
            break;
        case 0x34:
            if(IsShiftPressed)
                printf(">");
            else
                printf(".");
            break;
        case 0x33:
            if(IsShiftPressed)
                printf("<");
            else
                printf(",");
            break;
        case 0x1A:
            if(IsShiftPressed)
                printf("{");
            else
                printf("[");
            break;
        case 0x1B:
            if(IsShiftPressed)
                printf("}");
            else
                printf("]");
            break;
        case 0x2B:
            if(IsShiftPressed)
                printf("|");
            else
                printf("\\");
            break;
        case 0x27:
            if(IsShiftPressed)
                printf(":");
            else
                printf(";");
            break;
        case 0x28:
            if(IsShiftPressed)
                printf("\"");
            else
                printf("\'");
            break;
        default:
            if(key < 0x80){
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