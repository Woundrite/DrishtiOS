#include "../includes/GUI/widget.h"

namespace Drishti{
	namespace GUI{
		Widget::Widget(Widget* Parent, Types::int32_t X, Types::int32_t Y, Types::int32_t W, Types::int32_t H, Types::uint8_t R, Types::uint8_t G, Types::uint8_t B): KeyboardEventHandler(){
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

		bool Widget::ContainsCoordinate(Types::int32_t X, Types::int32_t Y){
			return this->X <= X && X < this->X + this->W && this->Y <= Y && Y < this->Y + this->H;
		}

		void Widget::OnMouseButtonDown(Types::int32_t X, Types::int32_t Y, Types::uint8_t Button){
			GetFocus(this);
		}
		void Widget::OnMouseButtonUp(Types::int32_t X, Types::int32_t Y, Types::uint8_t Button){
			
		}
		void Widget::OnMouseMove(Types::int32_t OldX, Types::int32_t OldY, Types::int32_t NewX, Types::int32_t NewY){
			
		}

		void Widget::OnKeyDown(char* str){
			
		}
		void Widget::OnKeyUp(char* str){
			
		}

			CompositeWidget::CompositeWidget(Widget* Parent, Types::int32_t X, Types::int32_t Y, Types::int32_t W, Types::int32_t H, Types::uint8_t R, Types::uint8_t G, Types::uint8_t B): Widget(Parent, X, Y, W, H, R, G, B){
				FocussedChild = 0;
				NumChildren = 0;
			}
			CompositeWidget::~CompositeWidget(){
				//...
			}
			void CompositeWidget::GetFocus(Widget* widget){
				this->FocussedChild = widget;
				if(Parent != 0){
					Parent->GetFocus(this);
				}
			}

			void CompositeWidget::Draw(GraphicsContext* GC){
				Widget::Draw(GC);
				for(int i = NumChildren; i >= 0; --i){
					Children[i]->Draw(GC);
				}
			}

			void CompositeWidget::OnMouseButtonDown(Types::int32_t X, Types::int32_t Y, Types::uint8_t Button){
				for(int i = 0; i < NumChildren; ++i){
					if(Children[i]->ContainsCoordinate(X - this->X, Y - this->Y)){
						Children[i]->OnMouseButtonDown(X - this->X, Y - this->Y, Button);
						break;
					}
				}
			}
			void CompositeWidget::OnMouseButtonUp(Types::int32_t X, Types::int32_t Y, Types::uint8_t Button){
				for(int i = 0; i < NumChildren; ++i){
					if(Children[i]->ContainsCoordinate(X - this->X, Y - this->Y)){
						Children[i]->OnMouseButtonUp(X - this->X, Y - this->Y, Button);
						break;
					}
				}
			}
			void CompositeWidget::OnMouseMove(Types::int32_t OldX, Types::int32_t OldY, Types::int32_t NewX, Types::int32_t NewY){
				int Firstchild = -1;
				for(int i = 0; i < NumChildren; ++i){
					if(Children[i]->ContainsCoordinate(OldX - this->X, OldY - this->Y)){
						Children[i]->OnMouseMove(OldX - this->X, OldY - this->Y, NewX - this->X, NewY - this->Y);
						break;
					}
				}

				for(int i = 0; i < NumChildren; ++i){
					if(Children[i]->ContainsCoordinate(NewX - this->X, NewY - this->Y)){
						if(Firstchild != i)
							Children[i]->OnMouseMove(X - this->X, Y - this->Y, NewX - this->X, NewY - this->Y);
						break;
					}
				}
			}

			void CompositeWidget::OnKeyDown(char* str){
				if(FocussedChild != 0){
					FocussedChild->OnKeyDown(str);
				}
			}
			void CompositeWidget::OnKeyUp(char* str){
				if(FocussedChild != 0){
					FocussedChild->OnKeyUp(str);
				}
			}
		

	}
}