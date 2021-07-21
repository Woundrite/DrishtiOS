#pragma once

#include "../Common/types.h"
#include "../HComms/port.h"
#include "../Drivers/driver.h"
#include "../HComms/interrupts.h"

namespace Drishti{
	namespace Drivers{
		class KeyboardEventHandler{
			public:
				KeyboardEventHandler();

				virtual void OnKeyUp(char);
				virtual void OnKeyDown(char);
		};

		class KeyboardDriver : public HComms::InterruptHandler, public Driver {
			HComms::Port8Bit DataPort;
			HComms::Port8Bit CommandPort;

			KeyboardEventHandler* Handler;
			public:
				KeyboardDriver(HComms::InterruptManager* Manager, KeyboardEventHandler *Handler);
				~KeyboardDriver();
				virtual Types::uint32_t HandleInterrupt(Types::uint32_t esp);
				virtual void Activate();
		};
	}
}