#include "../includes/GUI/desktop.h"

namespace Drishti{
	namespace GUI{
		Desktop::Desktop(Types::int32_t W, Types::int32_t H, Types::uint8_t R, Types::uint8_t G, Types::uint8_t B): CompositeWidget(0, 0, 0, W, H, R, G, B), MouseEventHandler(){
			MouseX = W/2;
			MouseY = H/2;
		}
		Desktop::~Desktop(){
			
		}

		void Desktop::Draw(GraphicsContext* GC){
			CompositeWidget::Draw(GC);

			for(int i = 0; i<4; i++){
				GC->PutPixel(MouseX-i, MouseY, 0xFF, 0xFF, 0xFF);
				GC->PutPixel(MouseX+i, MouseY, 0xFF, 0xFF, 0xFF);
				GC->PutPixel(MouseX, MouseY-i, 0xFF, 0xFF, 0xFF);
				GC->PutPixel(MouseX, MouseY+i, 0xFF, 0xFF, 0xFF);
			}
		}

		void Desktop::OnMouseButtonReleased(Types::uint8_t button){
			CompositeWidget::OnMouseButtonUp(MouseX, MouseY, button);
		}
		void Desktop::OnMouseButtonPressed(Types::uint8_t button){
			CompositeWidget::OnMouseButtonDown(MouseX, MouseY, button);
		}
		void Desktop::OnMouseMove(int x, int y){

			X /= 4;
			Y /= 4;

			Types::int32_t NewMouseX = MouseX + x;
			if(NewMouseX < 0) NewMouseX = 0;
			if(NewMouseX >= W) NewMouseX = W - 1;

			Types::int32_t NewMouseY = MouseY + x;
			if(NewMouseY < 0) NewMouseY = 0;
			if(NewMouseY >= H) NewMouseY = H - 1;

			CompositeWidget::OnMouseMove(MouseX, MouseY, NewMouseX, NewMouseY);

			MouseX = NewMouseX;
			MouseY = NewMouseY;
		}
	}
}