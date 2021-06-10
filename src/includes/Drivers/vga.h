#pragma once

#include "../Common/types.h"
#include "../HComms/port.h"
#include "../Drivers/driver.h"
#include "../HComms/interrupts.h"

namespace Drishti{
	namespace Drivers{
		class VideoGraphicsArray{
			private:
				HComms::Port8Bit Misc;
				HComms::Port8Bit CRTCIndexPort; // CRTC stands for cathode ray tube controller
				HComms::Port8Bit CRTCDataPort;
				HComms::Port8Bit SequencerIndexPort;
				HComms::Port8Bit SequencerDataPort;
				HComms::Port8Bit GraphicsControllerIndexPort;
				HComms::Port8Bit GraphicsControllerDataPort;
				HComms::Port8Bit AttributeControllerIndexPort;
				HComms::Port8Bit AttributeControllerReadPort;
				HComms::Port8Bit AttributeControllerWritePort;
				HComms::Port8Bit AttributeControllerResetPort;

				void WriteRegisters(Types::uint8_t* Registers);
				Types::uint8_t* GetFrameBufferSegment();

				virtual Types::uint8_t GetColorIndex(Types::uint8_t R, Types::uint8_t G, Types::uint8_t B);


			public:
				VideoGraphicsArray();
				~VideoGraphicsArray();

				virtual bool SupportsMode(Types::uint32_t width ,Types::uint32_t height, Types::uint32_t ColorDepth);
				virtual bool SetMode(Types::uint32_t width ,Types::uint32_t height, Types::uint32_t ColorDepth);
				virtual void PutPixel(Types::uint32_t X, Types::uint32_t Y, Types::uint8_t R, Types::uint8_t G, Types::uint8_t B);
				virtual void PutPixel(Types::uint32_t X, Types::uint32_t Y, Types::uint8_t ColorIndex);
		};
	}
}