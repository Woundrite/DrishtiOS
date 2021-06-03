#ifndef __MOUSE_H
#define __MOUSE_H

#include "types.h"
#include "port.h"
#include "driver.h"
#include "interrupts.h"

class MouseEventHandler{
    public:
        MouseEventHandler();

        virtual void OnActivate();
        virtual void OnMouseButtonReleased(uint8_t button);
        virtual void OnMouseButtonPressed(uint8_t button);
        virtual void OnMouseMove(int x, int y);
};
class MouseDriver : public InterruptHandler, public Driver {
    Port8Bit DataPort;
    Port8Bit CommandPort;

    uint8_t buffer[3];
    uint8_t offset;
    uint8_t buttons;

    MouseEventHandler* Handler;
    public:
        MouseDriver(InterruptManager* Manager, MouseEventHandler* Handler);
        ~MouseDriver();
        virtual uint32_t HandleInterrupt(uint32_t esp);
        virtual void Activate();
};

#endif