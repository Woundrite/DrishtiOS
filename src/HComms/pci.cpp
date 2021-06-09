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
		void PeripheralComponentInterconnectController::SelectDrivers(Drivers::DriverManager* DManager, InterruptManager* IManager){
			for(int bus = 0; bus < 8; bus++){
				for(int device = 0; device < 32; device++){

					int numFunctions = DeviceHasFunctions(bus, device) ? 8 : 1;
					for(int function = 0; function < numFunctions; function++){
						PeripheralComponentInterconnectDeviceDescriptor dev = GetDeviceDescriptor(bus, device, function);

						if(dev.Vendor_ID == 0x0000 || dev.Vendor_ID == 0xFFFF)
							continue;

						for(int BARNum = 0; BARNum < 6; BARNum++){
							BaseAddressRegister BAR = GetBaseAddressRegister(bus, device, function, BARNum);
							if(BAR.Address && (BAR.Type == InputOutput))
								dev.PortBase = (Types::uint32_t)BAR.Address;
							
							Drivers::Driver* driver = GetDriver(dev, IManager);

							if(driver != 0)
								DManager->AddDriver(driver);
						}
						
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

		BaseAddressRegister PeripheralComponentInterconnectController::GetBaseAddressRegister(Types::uint16_t Bus, Types::uint16_t Device, Types::uint16_t Function, Types::uint16_t BAR){
			BaseAddressRegister Result;

			Types::uint32_t HeaderType = Read(Bus, Device, Function, 0x0E) & 0x7F;
			int maxBARs = 6 - (4*HeaderType);

			if(BAR >= maxBARs)
				return Result;
			
			Types::uint32_t Bar_Value = Read(Bus, Device, Function, 0x10 + 4*BAR);
			
			Result.Type = (Bar_Value & 0x1) ? InputOutput : MemoryMapping;

			Types::uint32_t temp;

			if(Result.Type = MemoryMapping){
				switch((Bar_Value >> 1) & 0x3){
					case 0: //32 bit mode
					case 1: //20bit mode
					case 2: //64bit mode
						break;
				}
			}else {
				Result.Address = (Types::uint8_t*)(Bar_Value & ~0x3);
				Result.Prefetchable = ((Bar_Value >> 3) & 0x1) == 0x1;
			}

			return Result;
		}

		Drivers::Driver* PeripheralComponentInterconnectController::GetDriver(PeripheralComponentInterconnectDeviceDescriptor Descriptor, InterruptManager* IManager){
			
			switch(Descriptor.Vendor_ID){
				case 0x1022: // AMD
					switch(Descriptor.Device_ID){
						case 0x2000: //mn79c973
							break;
					}
					break;
				case 0x8086:
					break;			
			}

			switch(Descriptor.Class_ID){
				case 0x03: // Graphics Device
					switch(Descriptor.Subclass_ID){
						case 0x00: // VGA
							break;
					}
			}

			return 0;
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

/**
 * pci_config_writed(addr,barOffset,0xFFFFFFF0); // with a loud 1s override
 const uint32_t Bar_Value = pci_config_readd(addr,barOffset) & 0xFFFFFFF0; // and back again-read
 if (barValue == 0) // there must be at least one address bit 1 (i.e. writable) 
{
 if (ptext != ptext_nopr) // unused BARs must be set to 0 (the Prefetchable Bit must not be set)
 { printf("ERROR : 32-bit Memory BAR, %u is not writable contains an address to bits!\n",bar); return; }

 // BAR-info output :
 printf("BAR %u is not used.\n",bar);
}
else
{
 const uint lowestBit = get_number_of_lowest_set_bit(barValue);
 // it must be a valid 32-bit address :
 if ( (get_number_of_highest_set_bit(barValue) != 31) || (lowestBit > 31) || (lowestBit < 4) )
 { printf("ERROR : 32-bit Memory BAR %u contains invalid writable address bits!\n",bar); return; }

 // BAR-info output :
 printf("BAR %u contains a %s 32Bit-Memory-resource with a size of 2^%u Bytes.\n",bar,ptext,lowestBit);
}
}
break;
*/