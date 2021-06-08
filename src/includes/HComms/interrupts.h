#pragma once

#include "../Common/types.h"
#include "../HComms/port.h"
#include "../gdt.h"
namespace Drishti
{
    namespace HComms{
        class InterruptManager;

        class InterruptHandler{
            protected:
                Types::uint8_t InterruptNumber;
                InterruptManager* interruptManager;

                InterruptHandler(Types::uint8_t InterruptNumber, InterruptManager* interruptManager);
                ~InterruptHandler();
            public:
                virtual Types::uint32_t HandleInterrupt(Types::uint32_t esp);
        };

        class InterruptManager{
            friend class InterruptHandler;
            protected:

                static InterruptManager* ActiveInterruptManager;
                InterruptHandler* handlers[256];

                struct GateDescriptor{
                    Types::uint16_t HandlerAddressLowBits;
                    Types::uint16_t GDT_CodeSegmentSelector;
                    Types::uint8_t reserved;
                    Types::uint8_t access;
                    Types::uint16_t HandlerAddressHighBits;

                }__attribute__((packed));

                static GateDescriptor InterruptDescriptorTable[256];

                struct InterruptDescriptorTablePointer{
                    Types::uint16_t size;
                    Types::uint32_t base;
                }__attribute__((packed));

                static void SetInterruptDescriptorTableEntry(Types::uint8_t interruptNumber, Types::uint16_t codeSegmentSelectorOffset, void (*handler)(), Types::uint8_t DescriptorPrevelageLevel, Types::uint8_t DescriptorType);

                Port8BitSlow picMasterCommand;
                Port8BitSlow picMasterData;
                Port8BitSlow picSlaveCommand;
                Port8BitSlow picSlaveData;
            public:
                InterruptManager(GlobalDescriptorTable* GDT);
                ~InterruptManager();

                void Activate();
                void Deactivate();

                static Types::uint32_t HandleInterrupt(Types::uint8_t InterruptNumber, Types::uint32_t esp);
                Types::uint32_t MainHandleInterrupt(Types::uint8_t InterruptNumber, Types::uint32_t esp);

                static void IgnoreInterruptRequest();
                static void HandleInterruptRequest0x00();
                static void HandleInterruptRequest0x01();
                static void HandleInterruptRequest0x0C();
        };
    }
}