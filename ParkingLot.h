#ifndef MTMPARKINGLOT_PARKINGLOT_H
#define MTMPARKINGLOT_PARKINGLOT_H

#include "ParkingLotTypes.h"
#include "Time.h"
#include "UniqueArray.h"
#include <string.h>
#include "ParkedVehicle.h"
#include "ParkingLotPrinter.h"
#define DAY 24
#define NUMBER_OF_UNIQUE_CARS 3

typedef UniqueArray <ParkedVehicle, std::equal_to<ParkedVehicle>> ParkingArray;
namespace MtmParkingLot {

    using namespace ParkingLotUtils;
    using std::ostream;
    class ParkingLot {
        ParkingArray Motorbike_Parking;
        ParkingArray Handicapped_Parking;
        ParkingArray Private_Car_Parking;

    public:
        explicit ParkingLot(unsigned int parkingBlockSizes[]);
        ~ParkingLot();
        ParkingResult enterParking(VehicleType vehicleType, LicensePlate licensePlate, Time entranceTime);
        ParkingResult exitParking(const LicensePlate& licensePlate, Time exitTime);
        ParkingResult getParkingSpot(LicensePlate licensePlate, ParkingSpot& parkingSpot) const;
        void inspectParkingLot(Time inspectionTime);
        friend ostream& operator<<(ostream& os, const ParkingLot& parkingLot);
        unsigned int pickParkingIndex(VehicleType park_here);
        
    };
    void printEntry(const ParkedVehicle& vehicle ,ParkingResult result);
}



#endif //MTMPARKINGLOT_PARKINGLOT_H
