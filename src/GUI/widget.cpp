#include "../includes/GUI/widget.h"

namespace Drishti{
    namespace GUI{
        Widget::Widget(Widget* Parent, Types::int32_t X, Types::int32_t Y, Types::int32_t W, Types::int32_t H, Types::uint8_t R, Types::uint8_t G, Types::uint8_t B){
            this->Parent = Parent;
            this->X = X;
            this->Y = Y;
            this->W = W;
            this->H = H;
            this->R = R;
            this->G = G;
            this->B = B;
        }

        Widget::~Widget(){
            
        }
                
        void Widget::GetFocus(Widget* widget){
            if(Parent != 0){
                Parent->GetFocus(widget);
            }
        }
        void Widget::ModelToScreen(Types::int32_t &X, Types::int32_t &Y){
            if(Parent!=0)
                Parent->ModelToScreen(X, Y);
            X += this->X;
            Y += this->Y;
        }

        void Widget::Draw(GraphicsContext* GC){
            int x = 0;
            int y = 0;
            ModelToScreen(x, y);
            GC->FillRectangle(x, y, W, H, R, G, B);
        }
        void Widget::OnMouseButtonDown(Types::int32_t X, Types::int32_t Y){
            GetFocus(this);
        }
        void Widget::OnMouseButtonUp(Types::int32_t X, Types::int32_t Y){
            
        }
        void Widget::OnMouseMove(Types::int32_t OldX, Types::int32_t OldY, Types::int32_t NewX, Types::int32_t NewY){
            
        }

        void Widget::OnKeyDown(Types::int32_t X, Types::int32_t Y){
            
        }
        void Widget::OnKeyUp(Types::int32_t X, Types::int32_t Y){
            
        }

    }
}