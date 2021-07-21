#pragma once

#include "../Common/types.h"
#include "../Common/GraphicsContext.h"
#include "../Drivers/vga.h"
#include "../Drivers/keyboard.h"
namespace Drishti{
    namespace GUI{

        class Widget: public Drivers::KeyBoardEventHandler{
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

                virtual void OnKeyDown(char* str);
                virtual void OnKeyUp(char* str);
        };

        class CompositeWidget : public Widget{
        private:
            Widget* Children[100];
            int NumChildren;
            Widget* FocussedChild;
        public:
            CompositeWidget(Widget* Parent, Types::int32_t X, Types::int32_t Y, Types::int32_t W, Types::int32_t H, Types::uint8_t R, Types::uint8_t G, Types::uint8_t B);
            ~CompositeWidget();
            virtual void GetFocus(Widget* widget);

            virtual void Draw(GraphicsContext* GC);
            virtual void OnMouseButtonDown(Types::int32_t X, Types::int32_t Y);
            virtual void OnMouseButtonUp(Types::int32_t X, Types::int32_t Y);
            virtual void OnMouseMove(Types::int32_t OldX, Types::int32_t OldY, Types::int32_t NewX, Types::int32_t NewY);

            void OnKeyDown(char* str);
            void OnKeyUp(char* str);
        };
        

    }
}