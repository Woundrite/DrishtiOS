#include "includes/keyboard.h"

KeyboardEventHandler::KeyboardEventHandler(){

}

void KeyboardEventHandler::OnKeyUp(char){}

void KeyboardEventHandler::OnKeyDown(char){}

KeyboardDriver::KeyboardDriver(InterruptManager* Manager, KeyboardEventHandler *Handler):InterruptHandler(0x21, Manager), DataPort(0x60), CommandPort(0x64){
    this->Handler = Handler;
}
KeyboardDriver::~KeyboardDriver(){

} 

void printf(char*);
void PrintHex(uint8_t key);
void PrintHex(char* str, uint8_t key);

void KeyboardDriver::Activate(){
    while(CommandPort.Read() & 0x1)
        DataPort.Read();
    CommandPort.Write(0xAE); // activate interrupts
    CommandPort.Write(0x20); // gget current state of keyboard
    uint8_t status = (DataPort.Read() | 1) & ~0x10;
    CommandPort.Write(0x60); //set/change state
    DataPort.Write(status);
    DataPort.Write(0xF4);
}

uint32_t KeyboardDriver::HandleInterrupt(uint32_t esp){
    uint8_t key = DataPort.Read();

    if(Handler == 0)
        return esp;

    static bool IsShiftPressed = false;
    switch(key){
        case 0x45: //Numlock
        case 0xC5:
        case 0xFA:
            break;
        case 0x1E:
            if(IsShiftPressed)
                Handler->OnKeyDown('A');
            else
                Handler->OnKeyDown('a');
            break;
        case 0x30:
            if(IsShiftPressed)
                Handler->OnKeyDown('B');
            else
                Handler->OnKeyDown('b');
            break;
        case 0x2E:
            if(IsShiftPressed)
                Handler->OnKeyDown('C');
            else
                Handler->OnKeyDown('c');
            break;
        case 0x20:
            if(IsShiftPressed)
                Handler->OnKeyDown('D');
            else
                Handler->OnKeyDown('d');
            break;
        case 0x12:
            if(IsShiftPressed)
                Handler->OnKeyDown('E');
            else
                Handler->OnKeyDown('e');
            break;
        case 0x21:
            if(IsShiftPressed)
                Handler->OnKeyDown('F');
            else
                Handler->OnKeyDown('f');
            break;
        case 0x22:
            if(IsShiftPressed)
                Handler->OnKeyDown('G');
            else
                Handler->OnKeyDown('g');
            break;
        case 0x23:
            if(IsShiftPressed)
                Handler->OnKeyDown('H');
            else
                Handler->OnKeyDown('h');
            break;
        case 0x17:
            if(IsShiftPressed)
                Handler->OnKeyDown('I');
            else
                Handler->OnKeyDown('i');
            break;
        case 0x24:
            if(IsShiftPressed)
                Handler->OnKeyDown('J');
            else
                Handler->OnKeyDown('j');
            break;
        case 0x25:
            if(IsShiftPressed)
                Handler->OnKeyDown('K');
            else
                Handler->OnKeyDown('k');
            break;
        case 0x26:
            if(IsShiftPressed)
                Handler->OnKeyDown('L');
            else
                Handler->OnKeyDown('l');
            break;
        case 0x32:
            if(IsShiftPressed)
                Handler->OnKeyDown('M');
            else
                Handler->OnKeyDown('m');
            break;
        case 0x31:
            if(IsShiftPressed)
                Handler->OnKeyDown('N');
            else
                Handler->OnKeyDown('n');
            break;
        case 0x18:
            if(IsShiftPressed)
                Handler->OnKeyDown('O');
            else
                Handler->OnKeyDown('o');
            break;
        case 0x19:
            if(IsShiftPressed)
                Handler->OnKeyDown('P');
            else
                Handler->OnKeyDown('p');
            break;
        case 0x10:
            if(IsShiftPressed)
                Handler->OnKeyDown('Q');
            else
                Handler->OnKeyDown('q');
            break;
        case 0x13:
            if(IsShiftPressed)
                Handler->OnKeyDown('R');
            else
                Handler->OnKeyDown('r');
            break;
        case 0x1F:
            if(IsShiftPressed)
                Handler->OnKeyDown('S');
            else
                Handler->OnKeyDown('s');
            break;
        case 0x14:
            if(IsShiftPressed)
                Handler->OnKeyDown('T');
            else
                Handler->OnKeyDown('t');
            break;
        case 0x16:
            if(IsShiftPressed)
                Handler->OnKeyDown('U');
            else
                Handler->OnKeyDown('u');
            break;
        case 0x2F:
            if(IsShiftPressed)
                Handler->OnKeyDown('V');
            else
                Handler->OnKeyDown('v');
            break;
        case 0x11:
            if(IsShiftPressed)
                Handler->OnKeyDown('W');
            else
                Handler->OnKeyDown('w');
            break;
        case 0x2D:
            if(IsShiftPressed)
                Handler->OnKeyDown('X');
            else
                Handler->OnKeyDown('x');
            break;
        case 0x15:
            if(IsShiftPressed)
                Handler->OnKeyDown('Y');
            else
                Handler->OnKeyDown('y');
            break;
        case 0x2C:
            if(IsShiftPressed)
                Handler->OnKeyDown('Z');
            else
                Handler->OnKeyDown('z');
            break;
        case 0x02:
            if(IsShiftPressed)
                Handler->OnKeyDown('!');
            else
                Handler->OnKeyDown('1');
            break;
        case 0x03:
            if(IsShiftPressed)
                Handler->OnKeyDown('@');
            else
                Handler->OnKeyDown('2');
            break;
        case 0x04:
            if(IsShiftPressed)
                Handler->OnKeyDown('#');
            else
                Handler->OnKeyDown('3');
            break;
        case 0x05:
            if(IsShiftPressed)
                Handler->OnKeyDown('$');
            else
                Handler->OnKeyDown('4');
            break;
        case 0x06:
            if(IsShiftPressed)
                Handler->OnKeyDown('%');
            else
                Handler->OnKeyDown('5');
            break;
        case 0x07:
            if(IsShiftPressed)
                Handler->OnKeyDown('^');
            else
                Handler->OnKeyDown('6');
            break;
        case 0x08:
            if(IsShiftPressed)
                Handler->OnKeyDown('&');
            else
                Handler->OnKeyDown('7');
            break;
        case 0x09:
            if(IsShiftPressed)
                Handler->OnKeyDown('*');
            else
                Handler->OnKeyDown('8');
            break;
        case 0x0A:
            if(IsShiftPressed)
                Handler->OnKeyDown('(');
            else
                Handler->OnKeyDown('9');
            break;
        case 0x0B:
            if(IsShiftPressed)
                Handler->OnKeyDown(')');
            else
                Handler->OnKeyDown('0');
            break;
        case 0x39:
            Handler->OnKeyDown(' ');
            break;
        case 0x38:
        //     Handler->OnKeyDown(' ALT ');
        //     break;
        // case 0x1D:
        //     Handler->OnKeyDown(' CTRL ');
        //     break;
        // case 0x3A:
        //     Handler->OnKeyDown(' CAPSLOCK ');
            break;
        case 0xAA:
        case 0xB6:
            IsShiftPressed = false;
            break;
        case 0x36:
        case 0x2A:
            IsShiftPressed = true;
            break;
        // case 0x01:
        //     Handler->OnKeyDown(' ESC ');
        //     break;
        // case 0x29:
        //     if(IsShiftPressed)
        //         Handler->OnKeyDown('~');
        //     else
        //         Handler->OnKeyDown('`');
        //     break;
        // case 0x3B:
        //     Handler->OnKeyDown(' F1 ');
        //     break;
        // case 0x3C:
        //     Handler->OnKeyDown(' F2 ');
        //     break;
        // case 0x3D:
        //     Handler->OnKeyDown(' F3 ');
        //     break;
        // case 0x3E:
        //     Handler->OnKeyDown(' F4 ');
        //     break;
        // case 0x3F:
        //     Handler->OnKeyDown(' F5 ');
        //     break;
        // case 0x40:
        //     Handler->OnKeyDown(' F6 ');
        //     break;
        // case 0x41:
        //     Handler->OnKeyDown(' F7 ');
        //     break;
        // case 0x42:
        //     Handler->OnKeyDown(' F8 ');
        //     break;
        // case 0x43:
        //     Handler->OnKeyDown(' F9 ');
        //     break;
        // case 0x44:
        //     Handler->OnKeyDown(' F10 ');
        //     break;
        // case 0x57:
        //     Handler->OnKeyDown(' F11 ');
        //     break;
        // case 0x58:
        //     Handler->OnKeyDown(' F12 ');
        //     break;
        // case 0x47:
        //     Handler->OnKeyDown(' Home ');
        //     break;
        // case 0x0E:
        //     Handler->OnKeyDown(' BACKSPACE ');
        //     break;
        // case 0x4F:
        //     Handler->OnKeyDown(' End ');
        //     break;
        // case 0x52:
        //     Handler->OnKeyDown(' INSERT ');
        //     break;
        // case 0x53:
        //     Handler->OnKeyDown(' DELETE ');
        //     break;
        // case 0x5B:
        //     Handler->OnKeyDown(' WINKEY ');
        //     break;
        // case 0x48:
        //     Handler->OnKeyDown(' UP_ARROW ');
        //     break;
        // case 0x50:
        //     Handler->OnKeyDown(' DOWN_ARROW ');
        //     break;
        // case 0x4D:
        //     Handler->OnKeyDown(' LEFT_ARROW ');
        //     break;
        // case 0x4B:
        //     Handler->OnKeyDown(' RIGHT_ARROW ');
        //     break;
        case 0x0C:
            if(IsShiftPressed)
                Handler->OnKeyDown('_');
            else
                Handler->OnKeyDown('-');
            break;
        case 0x0D:
            if(IsShiftPressed)
                Handler->OnKeyDown('+');
            else
                Handler->OnKeyDown('=');
            break;
        case 0x0F:
            Handler->OnKeyDown('\t');
            break;
        case 0x49:
            Handler->OnKeyDown(' PAGE_UP ');
            break;
        case 0x51:
            Handler->OnKeyDown(' PAGE_DOWN ');
            break;
        case 0x1C:
            Handler->OnKeyDown(' \n ');
            break;
        case 0x35:
            if (IsShiftPressed)
                Handler->OnKeyDown('?');
            else
                Handler->OnKeyDown('/');
            break;
        case 0x34:
            if(IsShiftPressed)
                Handler->OnKeyDown('>');
            else
                Handler->OnKeyDown('.');
            break;
        case 0x33:
            if(IsShiftPressed)
                Handler->OnKeyDown('<');
            else
                Handler->OnKeyDown(',');
            break;
        case 0x1A:
            if(IsShiftPressed)
                Handler->OnKeyDown('{');
            else
                Handler->OnKeyDown('[');
            break;
        case 0x1B:
            if(IsShiftPressed)
                Handler->OnKeyDown('}');
            else
                Handler->OnKeyDown(']');
            break;
        case 0x2B:
            if(IsShiftPressed)
                Handler->OnKeyDown('|');
            else
                Handler->OnKeyDown('\\');
            break;
        case 0x27:
            if(IsShiftPressed)
                Handler->OnKeyDown(':');
            else
                Handler->OnKeyDown(';');
            break;
        case 0x28:
            if(IsShiftPressed)
                Handler->OnKeyDown('\"');
            else
                Handler->OnKeyDown('\'');
            break;
        default:
            if(key < 0x80){
                PrintHex("KEYBOARD 0x", key);
            }
    }
    return esp;
}