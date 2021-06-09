#pragma once

#include "port.h"
#include "../Common/types.h"
#include "../Drivers/driver.h"
#include "interrupts.h"
namespace Drishti{
	namespace HComms{

		class PeripheralComponentInterconnectDeviceDescriptor{
			public:
				Types::uint32_t PortBase;
				Types::uint32_t Interrupt;

				Types::uint16_t Bus;
				Types::uint16_t Device;
				Types::uint16_t Function;

				Types::uint16_t Vendor_ID;
				Types::uint16_t Device_ID;

				Types::uint8_t Class_ID;
				Types::uint8_t Subclass_ID;
				Types::uint8_t Interface_ID;

				Types::uint8_t Revision;

				PeripheralComponentInterconnectDeviceDescriptor();
				~PeripheralComponentInterconnectDeviceDescriptor();
		};

		class PeripheralComponentInterconnectController{
			private:
				Port32Bit dataPort;
				Port32Bit commandPort;
			public:
				PeripheralComponentInterconnectController();
				~PeripheralComponentInterconnectController();

				Types::uint32_t Read(Types::uint16_t Bus, Types::uint16_t Device, Types::uint16_t Function, Types::uint32_t RegisterOffset);
				void Write(Types::uint16_t Bus, Types::uint16_t Device, Types::uint16_t Function, Types::uint32_t RegisterOffset, Types::uint32_t Value);
				bool DeviceHasFunctions(Types::uint16_t Bus, Types::uint16_t Device);

				void SelectDrivers(Drivers::DriverManager* Manager);

				PeripheralComponentInterconnectDeviceDescriptor GetDeviceDescriptor(Types::uint16_t Bus, Types::uint16_t Device, Types::uint16_t Function);
		};
	}
}