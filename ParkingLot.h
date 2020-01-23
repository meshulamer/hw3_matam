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


/**
 * @brief Defines a Unique Array and Vector for Parked Vehicle Object, to be used
 * in the parking lot.
 */

typedef std::vector<ParkedVehicle> VehicleVector;
typedef UniqueArray <ParkedVehicle, std::equal_to<ParkedVehicle>> ParkingArray;
/**
 * @brief Namespaces for Managing the parking lot
 */
namespace MtmParkingLot {
    using namespace ParkingLotUtils;
    using std::ostream;
    /**
    * @brief ParkingLot Object that holds 3 Unique ParkingArrays for 3 different kinds of Parked Vehicle.
    * ParkingArray is a UniqueArray for ParkedVehicles.
    */
    class ParkingLot {
        ParkingArray Motorbike_Parking;
        ParkingArray Handicapped_Parking;
        ParkingArray Private_Car_Parking;

    public:
        /**
        * @brief Builds a new ParkingLot object.
        * @Parameters: Unsigned int array parkingBlockSizes - the size of each Vehicle type
        * parking array (total parking spots).
        */
        explicit ParkingLot(unsigned int parkingBlockSizes[]);
        /**
        * @brief Destructor for ParkingLot Object.
        */
        ~ParkingLot();
        /**
        * @brief Inserts a new car to the parking lot in its corresponding parking spot type.
        * @Parameters: Type of the Vehicle (VehicleType) , Vehicle's Plate number in a String (LicensePlate)
        * Vehicle's time of entrance to the lot (Time)
        */
        ParkingResult enterParking(VehicleType vehicleType, LicensePlate licensePlate, Time entranceTime);
        /**
        * @brief Checks out a Vehicle from the parking lot.
        * @Parameters: Vehicle's Plate number in a String (LicensePlate)
        * Current time (time of exit), (Time)
        *@Returns: ParkingResult: NO_EMPTY_SPOT, ALREADY_PARKED
        * SUCCESS
        */
        ParkingResult exitParking(const LicensePlate& licensePlate, Time exitTime);
        /**
        * @brief Gets a Vehicle's parking spot, and inserts it into a reference.
        * @Parameters: license plate of the Vehicle(LicensePlate), ParkingSpot&.
        * @Returns: SUCCESS , VEHICLE_NOT_FOUND
        */
        ParkingResult getParkingSpot(LicensePlate licensePlate, ParkingSpot& parkingSpot) const;
        /**
        * @brief An Inspector visits the lot, and gives tickets to Vehicles parked over the time limit.
        * @Parameters: Time of Inspection.
        *
        */
        void inspectParkingLot(Time inspectionTime);
        /**
        * @brief Print operator for ParkingLot.
        * @Parameters: ostream& to print into, parkingLot& to print.
        *@Returns: os (for chain print)
         */
        friend ostream& operator<<(ostream& os, const ParkingLot& parkingLot);
        /**
        * @brief Help function that parks the Car in the corresponding Block type.
        * @Parameters: ParkedVehicle& car to park, VehicleType Parking block to park the car in.
        */
        void parkTheVehicle(ParkedVehicle& new_parked_car, VehicleType park_here);
        /**
        * @brief Removes a car from a ParkingArray
        * @Parameters: ParkedVehicle object to a ParkedVehicle we want to remove
        * the function considers its License plate.
        */
        void exitCar(ParkedVehicle about_to_exit);
        /**
        * @brief Gets pointer to vehicle that is parked in the lot.
        * Looks for it in all possible Block locations.
        * @Parameters: ParkedVehicle object to a ParkedVehicle we want to find
        * the function considers its License plate.
        * @Returns pointer to the vehicle.
        */
        const ParkedVehicle* getVehiclePointer(ParkedVehicle vehicle);
        /**
        * @brief Prints requested messeges for a Vehicle entering the lot.
        * @Parameters: ParkedVehicle the vehicle that enters, ParkingResult the result of the parking attempt.
        */
        void printEntry(ParkedVehicle vehicle ,ParkingResult result);

    };
    /**
    * @brief Inspects a parking block, and fines the vehicles that are parked too long. returns number of fines cars.
    * @Parameters: ParkingArray& to a parking array to inspect.
    * @Returns number of vehicles that got a ticket.
    */
    int blockInspection(ParkingArray& block_array, Time inspectionTime);
    /**
    * @brief Checks of a Vehicle exists in the lot.
    * @Parameters: ParkedVehicle* to all parking blocks.
    * @Returns: cost ParkedVehicle* to the car if its found, nullptr otherwise.
    */
    const ParkedVehicle* vehicleExists(const ParkedVehicle* motorbike_parking, const ParkedVehicle* handicapped_parking,
                      const ParkedVehicle* private_car_parking);
    /**
    * @brief Adds all vehicles in a ParkingLot to a VehicleVector.
    * @Parameters: VehicleVector& we want to add to,3 ParkingArray references to each block type.
    */
    void addArraysToVector(VehicleVector& print_array,const ParkingArray& motorbike_array,
            const ParkingArray& handicapped_array, const ParkingArray& private_car_array);
    };



#endif //MTMPARKINGLOT_PARKINGLOT_H
