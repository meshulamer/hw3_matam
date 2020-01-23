#ifndef MTM_PARKED_VEHICLE_H
#define MTM_PARKED_VEHICLE_H

#include "ParkingSpot.h"
#include "ParkingLotTypes.h"
#include "Time.h"


/**
* @brief Defines Payment Methods for different ParkedVehicles
* Defines maximum time a vehicle can park
*/
#define ONE_HOUR_PAYMENT_PRIVATE_CAR 20
#define ONE_HOUR_PAYMENT_MOTORBIKE 10
#define PAYMENT_FOR_HANDICAPPED 15
#define ABOVE_ONE_HOUR_PAYMENT_PRIVATE_CAR 10
#define ABOVE_ONE_HOUR_PAYMENT_MOTORBIKE 5
#define MAXIMUM_PARKING_TIME_IN_HOURS 6
#define FINE_AMOUNT 250
#define MAXIMUM_PARKING_HOURS 24

using namespace ParkingLotUtils;
    /**
    * @brief Represents a Vehicle object that is a parking lots's customer.
    * Holds its type, plate number, if it got a fine, the place it is parked in
    * and when it started parking.
    * The module allows calculation of the price the vehicles have to pay when exiting.
    */
        class ParkedVehicle {
        private:
            VehicleType type;
            string plate_num;
            Time start_time;
            bool fined;
            ParkingSpot spot;
        public:
            /**
           * @brief Constructs a new ParkedVehicle object.
           * @Parameters:the vehicle's type: VehicleType , the vehicles plate number in a string: LicensePlate,
           * vehicles entrance time to the parking lot: Time
           *Returns a ParkedVehicle Objects.
           */
            ParkedVehicle(VehicleType vehicleType, LicensePlate licensePlate, Time entranceTime);

            /**
          * @brief Constructs a new ParkedVehicle Object with only its license plate.
          * mainly used for comparison.
          */
            explicit ParkedVehicle(LicensePlate licensePlate);

            /**
          * @brief Destructor for a ParkedVehicle object.
          *
          */
            ~ParkedVehicle() = default;

            /**
          * @brief Compares license plates to check if two vehicles are equal.
          * @Returns true if LicensePlates equal, false otherwise.
          *
          */
            bool operator==(const ParkedVehicle &vehicle) const;

            /**
          * @brief Comparison of two vehicles by their parking spots.
          * @Returns boolean result of operator < for ParkingSpots of the two vehicles.
          */
            friend bool operator<(const ParkedVehicle &vehicle1, const ParkedVehicle &vehicle2);

            /**
            * @brief Calculates the price that a vehicle has to pay when finishing a parking.
            * @Returns int Price that the Vehicle has to pay to exit
            */
            int priceCalculation(Time exit_time) const;

            /**
          * @brief Returns a Vehicle's type.
          */
            VehicleType getVehicleType() const;

            /**
           * @brief Returns a Vehicle's Plate Number.
           *
           */
            string getPlateNumber() const;

            /**
          * @brief Returns a Vehicle's time of entrance to the Lot.
          *
          */
            Time getTime() const;

            /**
          * @brief Gives the Vehicle a Fine.
          *
          */
            void giveTicket();

            /**
          * @brief Returns true if a ParkedVehicle has a ticket, false otherwise.
          *
          */
            bool isFined() const;

            /**
          * @brief Overloaded = operator.
          * copies each field.
          */
            ParkedVehicle &operator=(const ParkedVehicle &vehicle);

            /**
          * @brief Changes a ParkingSpot of a ParkedVehicle.
          *
          */
            void setParkingSpot(VehicleType parkingBlock, unsigned int index);

            /**
          * @brief Returns the ParkingSpot of a ParkedVehicle.
          *
          */
            ParkingSpot getSpot() const;

        };
#endif //MTM_PARKED_VEHICLE_H