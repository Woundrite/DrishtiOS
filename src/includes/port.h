#ifndef __PORT_H
#define __PORT_H

#include "types.h"

class Port{
    protected:
        uint16_t PortNumber;
        Port(uint16_t PortNumber);
        ~Port();
};

class Port8Bit : public Port{
    public:
        Port8Bit(uint16_t PortNumber);
        ~Port8Bit();
        virtual void Write(uint8_t Data);
        virtual uint8_t Read();
};

class Port8BitSlow : public Port8Bit{
    public:
        Port8BitSlow(uint16_t PortNumber);
        ~Port8BitSlow();
        virtual void Write(uint8_t Data);
};

class Port16Bit : public Port{
    public:
        Port16Bit(uint16_t PortNumber);
        ~Port16Bit();
        virtual void Write(uint16_t Data);
        virtual uint16_t Read();
};

class Port32Bit : public Port{
    public:
        Port32Bit(uint16_t PortNumber);
        ~Port32Bit();
        virtual void Write(uint32_t Data);
        virtual uint32_t Read();
};



#endif