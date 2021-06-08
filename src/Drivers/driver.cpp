#include "../includes/Drivers/driver.h"

namespace Drishti {
    namespace Drivers{
        Driver::Driver(){}

        Driver::~Driver(){}

        void Driver::Activate(){}

        int Driver::Reset(){
            return 0;
        }

        void Driver::Deactivate(){}

        DriverManager::DriverManager(){
            NumDrivers = 0;
        }

        DriverManager::~DriverManager(){}

        void DriverManager::AddDriver(Driver* drv){
            drivers[NumDrivers] = drv;
            NumDrivers++;
        }

        void DriverManager::ActivateAll(){
            for(int i=0; i<NumDrivers; i++)
                drivers[i]->Activate();
        }
    }
}