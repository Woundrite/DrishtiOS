#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#include "types.h"
#include "port.h"
#include "driver.h"
#include "interrupts.h"

class KeyboardEventHandler{
    public:
        KeyboardEventHandler();

        virtual void OnKeyUp(char);
        virtual void OnKeyDown(char);
};

class KeyboardDriver : public InterruptHandler, public Driver {
    Port8Bit DataPort;
    Port8Bit CommandPort;

    KeyboardEventHandler* Handler;
    public:
        KeyboardDriver(InterruptManager* Manager, KeyboardEventHandler *Handler);
        ~KeyboardDriver();
        virtual uint32_t HandleInterrupt(uint32_t esp);
        virtual void Activate();
};

#endif