#include "includes/Common/types.h"
#include "includes/gdt.h"
#include "includes/HComms/port.h"
#include "includes/HComms/interrupts.h"
#include "includes/HComms/pci.h"
#include "includes/Drivers/driver.h"
#include "includes/Drivers/keyboard.h"
#include "includes/Drivers/mouse.h"
#include "includes/Drivers/vga.h"
#include "includes/GUI/desktop.h"

namespace Drishti{
	void printf(char* str) {
		Types::uint16_t* VideoMemory = (Types::uint16_t*)0xb8000;

		static Types::uint8_t x = 0, y = 0;

		for(int i = 0; str[i] != '\0'; ++i){

			switch(str[i]){
				case '\n':
					y++;
					x = 0;
					break;
				default:
					VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | str[i];
					x++;
			}

			if(x >= 80){
				y++;
				x = 0;
			}

			if(y >= 25){
				
				for(y=0; y<25; y++)
					for(x=0; x<80; x++)
						VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | ' ';
				x = 0;
				y = 0;
			}
		}
	}

	void PrintHex(Types::uint8_t key){
		char* foo = "00";
		char* hex = "0123456789ABCDEF";
		foo[0] = hex[(key >> 4) & 0x0F];
		foo[1] = hex[key & 0x0F];
		printf(foo);
	}

	void PrintHex(char* str, Types::uint8_t key){
		char* foo = "00";
		char* hex = "0123456789ABCDEF";
		foo[0] = hex[(key >> 4) & 0x0F];
		foo[1] = hex[key & 0x0F];
		printf(str);
		printf(foo);
	}

	class PrintKeyboardEventHandler : public Drivers::KeyboardEventHandler{
		public:
			void OnKeyDown(char c){
				char* foo = " ";
				foo[0] = c;
				printf(foo);
			}
	};

	class MouseToConsole : public Drivers::MouseEventHandler{

		Types::int8_t x, y;

		public:

			MouseToConsole(){
				Types::uint16_t* VideoMemory = (Types::uint16_t*)0xb8000;
				x = 40;
				y = 12;
				VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0x0F00) << 4
									| (VideoMemory[80*y+x] & 0xF000) >> 4
									| (VideoMemory[80*y+x] & 0x00FF);
			}

			void OnMouseMove(int xOffset, int yOffset){
				static Types::uint16_t* VideoMemory = (Types::uint16_t*)0xb8000;
				
				VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0x0F00) << 4
											| (VideoMemory[80*y+x] & 0xF000) >> 4
											| (VideoMemory[80*y+x] & 0x00FF);

				x += xOffset;
				if(x >= 80) x = 79;
				if(x < 0) x = 0;
				y += yOffset;
				if(y >= 25) y = 24;
				if(y < 0) y = 0;

				VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0x0F00) << 4
											| (VideoMemory[80*y+x] & 0xF000) >> 4
											| (VideoMemory[80*y+x] & 0x00FF);
			}
	};

	typedef void (*constructor)();
	extern "C" constructor start_ctors;
	extern "C" constructor end_ctors;
	extern "C" void callConstructors() {
		for(constructor* i = &start_ctors; i != &end_ctors; i++)
			(*i)();
	}

	extern "C" void KernelBoot(void* multiboot_structure, Types::uint32_t BootIdentifier) {
		printf("Hello world!");

		GlobalDescriptorTable gdt;
		HComms::InterruptManager Interrupts(&gdt);

		printf("\n[System]: Initializing Hardware\n");

		GUI::Desktop desktop(320, 200, 0x00, 0x00, 0xA8);

		Drivers::DriverManager driverManager;

		// PrintKeyboardEventHandler KeyboardHandler;
		// Drivers::KeyboardDriver Keyboard(&Interrupts, &KeyboardHandler);
		Drivers::KeyboardDriver Keyboard(&Interrupts, &desktop);
		driverManager.AddDriver(&Keyboard);

		// MouseToConsole MouseHandler;
		// Drivers::MouseDriver Mouse(&Interrupts, &MouseHandler);
		Drivers::MouseDriver Mouse(&Interrupts, &desktop);
		driverManager.AddDriver(&Mouse);

		HComms::PeripheralComponentInterconnectController PCIController;
		PCIController.SelectDrivers(&driverManager, &Interrupts);

		Drivers::VideoGraphicsArray vga;

		driverManager.ActivateAll();

		Interrupts.Activate();

		vga.SetMode(320, 200, 8);
		desktop.Draw(&vga);

		while(1){
			desktop.Draw(&vga);
		}
	}
}