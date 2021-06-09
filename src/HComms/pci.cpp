#include "../includes/HComms/pci.h"

namespace Drishti{
	void printf(char* str);
	void PrintHex(Types::uint8_t key);
	void PrintHex(char* str, Types::uint8_t key);
	namespace HComms{
		PeripheralComponentInterconnectController::PeripheralComponentInterconnectController():dataPort(0xCFC), commandPort(0xCF8){

		}
		PeripheralComponentInterconnectController::~PeripheralComponentInterconnectController(){

		}

		Types::uint32_t PeripheralComponentInterconnectController::Read(Types::uint16_t Bus, Types::uint16_t Device, Types::uint16_t Function, Types::uint32_t RegisterOffset){
			Types::uint32_t id = 0x1 << 31 | ((Bus & 0xFF) << 16) | ((Device & 0x1F) << 11) | ((Function & 0x07) << 8) | (RegisterOffset & 0xFC);
			commandPort.Write(id);
			Types::uint32_t result  = dataPort.Read();

			return result >> (8 * RegisterOffset % 4);
		}
		void PeripheralComponentInterconnectController::Write(Types::uint16_t Bus, Types::uint16_t Device, Types::uint16_t Function, Types::uint32_t RegisterOffset, Types::uint32_t Value){
			Types::uint32_t id = 0x1 << 31 | ((Bus & 0xFF) << 16) | ((Device & 0x1F) << 11) | ((Function & 0x07) << 8) | (RegisterOffset & 0xFC);
			commandPort.Write(id);
			dataPort.Write(Value); 
		}

		bool PeripheralComponentInterconnectController::DeviceHasFunctions(Types::uint16_t Bus, Types::uint16_t Device){
			return Read(Bus, Device, 0, 0x0E) & (1<<7);
		}
		void PeripheralComponentInterconnectController::SelectDrivers(Drivers::DriverManager* Manager){
			for(int bus = 0; bus < 8; bus++){
				for(int device = 0; device < 32; device++){

					int numFunctions = DeviceHasFunctions(bus, device) ? 8 : 1;
					for(int function = 0; function < numFunctions; function++){
						PeripheralComponentInterconnectDeviceDescriptor dev = GetDeviceDescriptor(bus, device, function);

						if(dev.Vendor_ID == 0x0000 || dev.Vendor_ID == 0xFFFF)
							break;
						
						printf("PCI BUS ");
						PrintHex(bus & 0xFF);

						printf(", DEVICE ");
						PrintHex(device & 0xFF);

						printf(", FUNCTION ");
						PrintHex(function & 0xFF);

						printf(" = VENDOR ");
						PrintHex((dev.Vendor_ID & 0xFF) >> 8);
						PrintHex(dev.Vendor_ID & 0xFF);
						printf(", DEVICE ");
						PrintHex((dev.Device_ID & 0xFF) >> 8);
						PrintHex(dev.Device_ID & 0xFF);
						printf("\n");
					}
				}
			}
		}

		PeripheralComponentInterconnectDeviceDescriptor PeripheralComponentInterconnectController::GetDeviceDescriptor(Types::uint16_t Bus, Types::uint16_t Device, Types::uint16_t Function){
			PeripheralComponentInterconnectDeviceDescriptor Result;

			Result.Bus = Bus;
			Result.Device = Device;
			Result.Function = Function;

			Result.Vendor_ID = Read(Bus, Device, Function, 0x00);
			Result.Device_ID = Read(Bus, Device, Function, 0x02);

			Result.Class_ID = Read(Bus, Device, Function, 0x0b);
			Result.Subclass_ID = Read(Bus, Device, Function, 0x0a);
			Result.Interface_ID = Read(Bus, Device, Function, 0x09);

			Result.Revision = Read(Bus, Device, Function, 0x08);
			Result.Interrupt = Read(Bus, Device, Function, 0x3c);

			return Result;
		}

		PeripheralComponentInterconnectDeviceDescriptor::PeripheralComponentInterconnectDeviceDescriptor(){

		}
		PeripheralComponentInterconnectDeviceDescriptor::~PeripheralComponentInterconnectDeviceDescriptor(){

		}
	}
}