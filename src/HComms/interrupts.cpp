#include "../includes/HComms/interrupts.h"

namespace Drishti{
    void printf(char* str);
    void PrintHex(Types::uint8_t key);
    void PrintHex(char* str, Types::uint8_t key);
    
    namespace HComms{
        InterruptHandler::InterruptHandler(Types::uint8_t InterruptNumber, InterruptManager* interruptManager){
            this->InterruptNumber = InterruptNumber;
            this->interruptManager = interruptManager;
            interruptManager->handlers[InterruptNumber] = this;
        }

        InterruptHandler::~InterruptHandler(){
            if(interruptManager->handlers[InterruptNumber] == this)
                interruptManager->handlers[InterruptNumber] = 0;
        }

        Types::uint32_t InterruptHandler::HandleInterrupt(Types::uint32_t esp){
            return esp;
        }


        InterruptManager::GateDescriptor InterruptManager::InterruptDescriptorTable[256];

        InterruptManager* InterruptManager::ActiveInterruptManager = 0;

        void InterruptManager::SetInterruptDescriptorTableEntry(Types::uint8_t interruptNumber, Types::uint16_t codeSegmentSelectorOffset, void (*handler)(), Types::uint8_t DescriptorPrevelageLevel, Types::uint8_t DescriptorType){

            const Types::uint8_t IDT_DESC_PRESENT = 0x80;

            InterruptDescriptorTable[interruptNumber].HandlerAddressLowBits = ((Types::uint32_t)handler) & 0xFFFF;
            InterruptDescriptorTable[interruptNumber].HandlerAddressHighBits = (((Types::uint32_t)handler) >> 16) & 0xFFFF;
            InterruptDescriptorTable[interruptNumber].GDT_CodeSegmentSelector = codeSegmentSelectorOffset;
            InterruptDescriptorTable[interruptNumber].access = IDT_DESC_PRESENT | DescriptorType | ((DescriptorPrevelageLevel&3) << 5);
            InterruptDescriptorTable[interruptNumber].reserved = 0;
        }   

        InterruptManager::InterruptManager(GlobalDescriptorTable* GDT): picMasterCommand(0x20), picMasterData(0x21), picSlaveCommand(0xA0), picSlaveData(0xA1){
            Types::uint16_t CodeSegment = GDT->CodeSegmentSelector();
            const Types::uint8_t IDT_INTERRUPT_GATE = 0xE;

            for(Types::uint16_t i = 0; i<256; i++){
                handlers[i] = 0;
                SetInterruptDescriptorTableEntry(i, CodeSegment, &IgnoreInterruptRequest, 0, IDT_INTERRUPT_GATE);
            }

            SetInterruptDescriptorTableEntry(0x20, CodeSegment, &HandleInterruptRequest0x00, 0, IDT_INTERRUPT_GATE);
            SetInterruptDescriptorTableEntry(0x21, CodeSegment, &HandleInterruptRequest0x01, 0, IDT_INTERRUPT_GATE);
            SetInterruptDescriptorTableEntry(0x2C, CodeSegment, &HandleInterruptRequest0x0C, 0, IDT_INTERRUPT_GATE);

            picMasterCommand.Write(0x11);
            picSlaveCommand.Write(0x11);

            picMasterData.Write(0x20);
            picSlaveData.Write(0x28);

            picMasterData.Write(0x04);
            picSlaveData.Write(0x02);

            picMasterData.Write(0x01);
            picSlaveData.Write(0x01);

            picMasterData.Write(0x00);
            picSlaveData.Write(0x00);

            InterruptDescriptorTablePointer IDT;
            IDT.size = 256 * sizeof(GateDescriptor) - 1;
            IDT.base = (Types::uint32_t)InterruptDescriptorTable;
            asm volatile("lidt %0" : : "m" (IDT));
        }

        InterruptManager::~InterruptManager(){

        }

        void InterruptManager::Activate(){
            if(ActiveInterruptManager != 0)
                ActiveInterruptManager->Deactivate();
            ActiveInterruptManager = this;
            asm("sti");
        }

        void InterruptManager::Deactivate(){
            if(ActiveInterruptManager != 0){
                ActiveInterruptManager = this;
                asm("sti");
            }
        }

        Types::uint32_t InterruptManager::HandleInterrupt(Types::uint8_t InterruptNumber, Types::uint32_t esp){
            if(ActiveInterruptManager !=0){
                ActiveInterruptManager->MainHandleInterrupt(InterruptNumber, esp);
            }
            return esp;
        }

        Types::uint32_t InterruptManager::MainHandleInterrupt(Types::uint8_t InterruptNumber, Types::uint32_t esp){
            if(handlers[InterruptNumber] != 0){
                esp = handlers[InterruptNumber]->HandleInterrupt(esp);
            } else if(InterruptNumber != 0x20){
                PrintHex("UNHANDLED INTERRUPT 0", InterruptNumber);
            }
            
            if(InterruptNumber != 0x20){
                // printf(" INTERRUPT!! ");
            }

            if(0x20 <= InterruptNumber && InterruptNumber < 0x30){
                picMasterCommand.Write(0x20);
                if(0x28 <= InterruptNumber)
                picSlaveCommand.Write(0x20);
            }

            return esp;
        }
    }
}