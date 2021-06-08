#pragma once

namespace Drishti{
    namespace Drivers{
        class Driver{
            public:
                Driver();
                ~Driver();

                virtual void Activate();
                virtual int Reset();
                virtual void Deactivate();
        };

        class DriverManager{
            private:
                Driver* drivers[255];
                int NumDrivers;
            
            public:
                DriverManager();
                ~DriverManager();
                void AddDriver(Driver* drv);
                void ActivateAll();
        };
    }
}