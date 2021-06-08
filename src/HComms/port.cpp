#include "../includes/HComms/port.h"

namespace Drishti{
    namespace HComms{
        Port::Port(Types::uint16_t PortNumber){
            this->PortNumber = PortNumber;
        }

        Port::~Port(){

        }

        Port8Bit::Port8Bit(Types::uint16_t PortNumber) : Port(PortNumber) {

        }

        Port8Bit::~Port8Bit(){

        }

        void Port8Bit::Write(Types::uint8_t Data){
            __asm__ volatile("outb %0, %1" : : "a" (Data), "Nd" (PortNumber));
        }

        Types::uint8_t Port8Bit::Read(){
            Types::uint8_t Result;
            __asm__ volatile("inb %1, %0" : "=a" (Result) : "Nd" (PortNumber));
            return Result;
        }

        Port16Bit::Port16Bit(Types::uint16_t PortNumber) : Port(PortNumber) {

        }

        Port16Bit::~Port16Bit(){

        }

        void Port16Bit::Write(Types::uint16_t Data){
            __asm__ volatile("outw %0, %1" : : "a" (Data), "Nd" (PortNumber));
        }

        Types::uint16_t Port16Bit::Read(){
            Types::uint16_t Result;
            __asm__ volatile("inw %1, %0" : "=a" (Result) : "Nd" (PortNumber));
            return Result;
        }

        Port32Bit::Port32Bit(Types::uint16_t PortNumber) : Port(PortNumber) {

        }

        Port32Bit::~Port32Bit(){

        }

        void Port32Bit::Write(Types::uint32_t Data){
            __asm__ volatile("outl %0, %1" : : "a" (Data), "Nd" (PortNumber));
        }

        Types::uint32_t Port32Bit::Read(){
            Types::uint32_t Result;
            __asm__ volatile("inl %1, %0" : "=a" (Result) : "Nd" (PortNumber));
            return Result;
        }

        Port8BitSlow::Port8BitSlow(Types::uint16_t PortNumber) : Port8Bit(PortNumber) {

        }

        Port8BitSlow::~Port8BitSlow(){

        }

        void Port8BitSlow::Write(Types::uint8_t Data){
            __asm__ volatile("outb %0, %1\njmp 1f\n1: jmp 1f\n1:" : : "a" (Data), "Nd" (PortNumber));
        }
    }
}