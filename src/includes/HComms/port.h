#pragma once

#include "../Common/types.h"

namespace Drishti{
	namespace HComms{
		class Port{
			protected:
				Types::uint16_t PortNumber;
				Port(Types::uint16_t PortNumber);
				~Port();
		};

		class Port8Bit : public Port{
			public:
				Port8Bit(Types::uint16_t PortNumber);
				~Port8Bit();
				virtual void Write(Types::uint8_t Data);
				virtual Types::uint8_t Read();
		};

		class Port8BitSlow : public Port8Bit{
			public:
				Port8BitSlow(Types::uint16_t PortNumber);
				~Port8BitSlow();
				virtual void Write(Types::uint8_t Data);
		};

		class Port16Bit : public Port{
			public:
				Port16Bit(Types::uint16_t PortNumber);
				~Port16Bit();
				virtual void Write(Types::uint16_t Data);
				virtual Types::uint16_t Read();
		};

		class Port32Bit : public Port{
			public:
				Port32Bit(Types::uint16_t PortNumber);
				~Port32Bit();
				virtual void Write(Types::uint32_t Data);
				virtual Types::uint32_t Read();
		};
	}
}