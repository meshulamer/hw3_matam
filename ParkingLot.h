#ifndef MTMPARKINGLOT_PARKINGLOT_H
#define MTMPARKINGLOT_PARKINGLOT_H

#include "ParkingLotTypes.h"
#include "Time.h"
#include "UniqueArray.h"
#include <string.h>
#include "ParkedVehicle.h"
#define NUMBER_OF_UNIQUE_CARS 3
#define FINE_AMOUNT 250

typedef UniqueArray <ParkedVehicle, std::equal_to<ParkedVehicle>> ParkingArray;
namespace MtmParkingLot {

    using namespace ParkingLotUtils;
    using std::ostream;
    class ParkingLot {
    private:
        int parking_spots[NUMBER_OF_UNIQUE_CARS] ;
        ParkingArray parking_array;

    public:
        ParkingLot(unsigned int parkingBlockSizes[]);
        ~ParkingLot();
        ParkingResult enterParking(VehicleType vehicleType, LicensePlate licensePlate, Time entranceTime);
        ParkingResult exitParking(LicensePlate licensePlate, Time exitTime);
        ParkingResult getParkingSpot(LicensePlate licensePlate, ParkingSpot& parkingSpot) const;
        void inspectParkingLot(Time inspectionTime);
        friend ostream& operator<<(ostream& os, const ParkingLot& parkingLot);
        static unsigned int total_parking_spots(unsigned int array[]);
        static bool CarAlreadyParked(ParkedVehicle vehicle, ParkingArray array);
        static ParkedVehicle& buildVehicle(VehicleType vehicleType, LicensePlate licensePlate, Time entranceTime);
    };

}

#endif //MTMPARKINGLOT_PARKINGLOT_H
