#pragma once

#include "../Common/types.h"
#include "../HComms/port.h"
#include "../Drivers/driver.h"
#include "../HComms/interrupts.h"

namespace Drishti{
	namespace Drivers{
		class MouseEventHandler{
			public:
				MouseEventHandler();

				virtual void OnActivate();
				virtual void OnMouseButtonReleased(Types::uint8_t button);
				virtual void OnMouseButtonPressed(Types::uint8_t button);
				virtual void OnMouseMove(int x, int y);
		};
		class MouseDriver : public HComms::InterruptHandler, public Driver {
			HComms::Port8Bit DataPort;
			HComms::Port8Bit CommandPort;

			Types::uint8_t buffer[3];
			Types::uint8_t offset;
			Types::uint8_t buttons;

			MouseEventHandler* Handler;
			public:
				MouseDriver(HComms::InterruptManager* Manager, MouseEventHandler* Handler);
				~MouseDriver();
				virtual Types::uint32_t HandleInterrupt(Types::uint32_t esp);
				virtual void Activate();
		};
	}
}