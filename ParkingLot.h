#ifndef MTMPARKINGLOT_PARKINGLOT_H
#define MTMPARKINGLOT_PARKINGLOT_H

#include "ParkingLotTypes.h"
#include "Time.h"
#include "UniqueArray.h"
#include <string.h>
#include "ParkedVehicle.h"
#include "ParkingLotPrinter.h"
#include <vector>
#include <algorithm>

#define DAY 24

typedef std::vector<ParkedVehicle> VehicleVector;
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
        void park_the_vehicle(ParkedVehicle& new_parked_car, VehicleType park_here);
        void exit_car(ParkedVehicle about_to_exit);
        const ParkedVehicle* getVehiclePointer(ParkedVehicle vehicle);
        void printEntry(const ParkedVehicle& vehicle ,ParkingResult result);
    };

    int blockInspection(ParkingArray block_array, Time inspectionTime);
    const ParkedVehicle* vehicleExists(const ParkedVehicle* motorbike_parking, const ParkedVehicle* handicapped_parking,
                      const ParkedVehicle* private_car_parking);
    /*VehicleVector addArraysToVector(VehicleVector& print_array, ParkingArray& motorbike_array, ParkingArray& handicapped_array,
                           ParkingArray& private_car_array);*/
    }



#endif //MTMPARKINGLOT_PARKINGLOT_H
