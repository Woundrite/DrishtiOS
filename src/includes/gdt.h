#pragma once

#include "Common/types.h"

namespace Drishti{
	class GlobalDescriptorTable{
		public:
			class SegmentDescriptor {
				private:
					Types::uint16_t limit_low;
					Types::uint16_t base_low;
					Types::uint8_t base_high;
					Types::uint8_t type;
					Types::uint8_t limit_high;
					Types::uint8_t base_vhigh;
				public:
					SegmentDescriptor(Types::uint32_t base, Types::uint32_t limit, Types::uint8_t type);
					Types::uint32_t Base();
					Types::uint32_t Limit();
		}__attribute__((packed));

		private:
			SegmentDescriptor nullSegmentSelector;
			SegmentDescriptor unusedSegmentSelector;
			SegmentDescriptor codeSegmentSelector;
			SegmentDescriptor dataSegmentSelector;

		public:
			GlobalDescriptorTable();
			~GlobalDescriptorTable();

			Types::uint16_t CodeSegmentSelector();
			Types::uint16_t DataSegmentSelector();

	};
}