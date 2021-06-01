#ifndef __INTERRUPTS_H
#define __INTERRUPTS_H

#include "types.h"
#include "port.h"
#include "gdt.h"

class InterruptManager{
    protected:

        static InterruptManager* ActiveInterruptManager;

        struct GateDescriptor{
            uint16_t HandlerAddressLowBits;
            uint16_t GDT_CodeSegmentSelector;
            uint8_t reserved;
            uint8_t access;
            uint16_t HandlerAddressHighBits;

        }__attribute__((packed));

        static GateDescriptor InterruptDescriptorTable[256];

        struct InterruptDescriptorTablePointer{
            uint16_t size;
            uint32_t base;
        }__attribute__((packed));

        static void SetInterruptDescriptorTableEntry(uint8_t interruptNumber, uint16_t codeSegmentSelectorOffset, void (*handler)(), uint8_t DescriptorPrevelageLevel, uint8_t DescriptorType);

        Port8BitSlow picMasterCommand;
        Port8BitSlow picMasterData;
        Port8BitSlow picSlaveCommand;
        Port8BitSlow picSlaveData;
    public:
        InterruptManager(GlobalDescriptorTable* GDT);
        ~InterruptManager();

        void Activate();
        void Deactivate();

        static uint32_t HandleInterrupt(uint8_t InterruptNumber, uint32_t esp);
        uint32_t MainHandleInterrupt(uint8_t InterruptNumber, uint32_t esp);

        static void IgnoreInterruptRequest();
        static void HandleInterruptRequest0x00();
        static void HandleInterruptRequest0x01();
};

#endif