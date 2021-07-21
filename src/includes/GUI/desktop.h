#pragma once

#include "../Common/types.h"
#include "../Common/GraphicsContext.h"
#include "../Drivers/mouse.h"
#include "../GUI/widget.h"


namespace Drishti{
	namespace GUI{
		class Desktop : public CompositeWidget, public Drivers::MouseEventHandler {
			protected:
				Types::uint32_t MouseX;
				Types::uint32_t MouseY;

			public:
				Desktop(Types::int32_t W, Types::int32_t H, Types::uint8_t R, Types::uint8_t G, Types::uint8_t B);
				~Desktop();

				void Draw(GraphicsContext* GC);

				void OnMouseButtonReleased(Types::uint8_t button);
				void OnMouseButtonPressed(Types::uint8_t button);
				void OnMouseMove(int x, int y);
		};
	}
}