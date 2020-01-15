#ifndef MTMPARKINGLOT_PARKINGLOT_H
#define MTMPARKINGLOT_PARKINGLOT_H

#include "ParkingLotTypes.h"
#include "Time.h"
#include "UniqueArray.h"
#include <string.h>
#include "ParkedVehicle.h"
#define NUMBER_OF_UNIQUE_CARS 3
#define FINE_AMOUNT 250

typedef UniqueArray <ParkedVehicle, ParkedVehicle::operator==(const ParkedVehicle& vehicle) const> ParkingArray;
namespace MtmParkingLot {

    using namespace ParkingLotUtils;
    using std::ostream;
    class ParkingLot {
    private:
        int[NUMBER_OF_UNIQUE_CARS] parking_spots;
        const int[NUMBER_OF_UNIQUE_CARS] ;
        ParkingArray parking_array;

    public:
        ParkingLot(unsigned int parkingBlockSizes[]);
        ~ParkingLot();
        ParkingResult enterParking(VehicleType vehicleType, LicensePlate licensePlate, Time entranceTime);
        ParkingResult exitParking(LicensePlate licensePlate, Time exitTime);
        ParkingResult getParkingSpot(LicensePlate licensePlate, ParkingSpot& parkingSpot) const;
        void inspectParkingLot(Time inspectionTime);
        friend ostream& operator<<(ostream& os, const ParkingLot& parkingLot);
        ParkingArray filterFinedVehicles(ParkingArray parking_array);

    };

}

#endif //MTMPARKINGLOT_PARKINGLOT_H
