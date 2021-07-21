#include "../includes/Drivers/mouse.h"

namespace Drishti{
	namespace Drivers{
		MouseEventHandler::MouseEventHandler(){

		}

		void MouseEventHandler::OnActivate(){

		}

		void MouseEventHandler::OnMouseButtonPressed(Types::uint8_t button){

		}

		void MouseEventHandler::OnMouseButtonReleased(Types::uint8_t button){

		}

		void MouseEventHandler::OnMouseMove(int x, int y){

		}

		MouseDriver::MouseDriver(HComms::InterruptManager* Manager, MouseEventHandler* Handler):InterruptHandler(0x2C, Manager), DataPort(0x60), CommandPort(0x64){
			this->Handler = Handler;
		}
		MouseDriver::~MouseDriver(){

		}

		void printf(char*);

		void MouseDriver::Activate(){

			offset = 0; // crude solution for mouse return problems TODO: find better solution
			buttons = 0;

			CommandPort.Write(0xA8); // activate interrupts
			CommandPort.Write(0x20); // gget current state of keyboard
			Types::uint8_t status = DataPort.Read() | 2;
			CommandPort.Write(0x60); //set/change state
			DataPort.Write(status);
			
			CommandPort.Write(0xD4);
			DataPort.Write(0xF4);
			DataPort.Read();
		}

		Types::uint32_t MouseDriver::HandleInterrupt(Types::uint32_t esp){

			Types::uint8_t status = CommandPort.Read();
			if(!(status & 0x20))
				return esp;

			buffer[offset] = DataPort.Read();

			if(Handler == 0)
				return esp;

			offset = (offset + 1) % 3;

			if(offset == 0){
				if(buffer[1] != 0 || buffer[2] != 0){

					Handler->OnMouseMove((int)buffer[1], -((int)buffer[2]));
				}
			}

			for(Types::uint8_t i = 0; i < 3; i++){
				if((buffer[0] & (0x1 << 1)) != (buttons & (0x1 << 1))){
					if(buttons & (0x1 << 1))
						Handler->OnMouseButtonReleased(i+1);
					else
						Handler->OnMouseButtonPressed(i+1);
				}
			}
			buffer[offset];
		}
	}
}