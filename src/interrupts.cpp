#include "includes/interrupts.h"

void printf(char* str);

InterruptManager::GateDescriptor InterruptManager::InterruptDescriptorTable[256];

void InterruptManager::SetInterruptDescriptorTableEntry(uint8_t interruptNumber, uint16_t codeSegmentSelectorOffset, void (*handler)(), uint8_t DescriptorPrevelageLevel, uint8_t DescriptorType){

    const uint8_t IDT_DESC_PRESENT = 0x80;

    InterruptDescriptorTable[interruptNumber].HandlerAddressLowBits = ((uint32_t)handler) & 0xFFFF;
    InterruptDescriptorTable[interruptNumber].HandlerAddressHighBits = (((uint32_t)handler) >> 16) & 0xFFFF;
    InterruptDescriptorTable[interruptNumber].GDT_CodeSegmentSelector = codeSegmentSelectorOffset;
    InterruptDescriptorTable[interruptNumber].access = IDT_DESC_PRESENT | DescriptorType | ((DescriptorPrevelageLevel&3) << 5);
    InterruptDescriptorTable[interruptNumber].reserved = 0;
}   

InterruptManager::InterruptManager(GlobalDescriptorTable* GDT): picMasterCommand(0x20), picMasterData(0x21), picSlaveCommand(0xA0), picSlaveData(0xA1){
    uint16_t CodeSegment = GDT->CodeSegmentSelector();
    const uint8_t IDT_INTERRUPT_GATE = 0xE;

    for(uint16_t i = 0; i<256; i++)
        SetInterruptDescriptorTableEntry(i, CodeSegment, &IgnoreInterruptRequest, 0, IDT_INTERRUPT_GATE);
    
    SetInterruptDescriptorTableEntry(0x20, CodeSegment, &HandleInterruptRequest0x00, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x21, CodeSegment, &HandleInterruptRequest0x01, 0, IDT_INTERRUPT_GATE);

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
    IDT.base = (uint32_t)InterruptDescriptorTable;
    asm volatile("lidt %0" : : "m" (IDT));
}

InterruptManager::~InterruptManager(){

}

void InterruptManager::Activate(){
    asm("sti");
}

uint32_t InterruptManager::HandleInterrupt(uint8_t InterruptNumber, uint32_t esp){
    printf(" Interrupt");

    return esp;
}