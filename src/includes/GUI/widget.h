#pragma once

#include "../Common/types.h"
#include "../Common/GraphicsContext.h"
#include "../Drivers/vga.h"

namespace Drishti{
    namespace GUI{

        class Widget{
            protected:
                Widget* Parent;
                Types::int32_t X;
                Types::int32_t Y;
                Types::int32_t W;
                Types::int32_t H;

                Types::uint8_t R;
                Types::uint8_t G;
                Types::uint8_t B;
                bool Focussable;

            public:

                Widget(Widget* Parent, Types::int32_t X, Types::int32_t Y, Types::int32_t W, Types::int32_t H, Types::uint8_t R, Types::uint8_t G, Types::uint8_t B);

                ~Widget();

                virtual void GetFocus(Widget* widget);
                virtual void ModelToScreen(Types::int32_t &X, Types::int32_t &Y);

                virtual void Draw(GraphicsContext* GC);
                virtual void OnMouseButtonDown(Types::int32_t X, Types::int32_t Y);
                virtual void OnMouseButtonUp(Types::int32_t X, Types::int32_t Y);
                virtual void OnMouseMove(Types::int32_t OldX, Types::int32_t OldY, Types::int32_t NewX, Types::int32_t NewY);

                virtual void OnKeyDown(Types::int32_t X, Types::int32_t Y);
                virtual void OnKeyUp(Types::int32_t X, Types::int32_t Y);
        };

    }
}