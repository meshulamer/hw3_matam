#ifndef MTM_PARKED_VEHICLE_H
#define MTM_PARKED_VEHICLE_H

#include "ParkingSpot.h"
#include "ParkingLotTypes.h"
#include "Time.h"

#define ONE_HOUR_PAYMENT_PRIVATE_CAR 20
#define ONE_HOUR_PAYMENT_MOTORBIKE 10
#define PAYMENT_FOR_HANDICAPPED 15
#define ABOVE_ONE_HOUR_PAYMENT_PRIVATE_CAR 10
#define ABOVE_ONE_HOUR_PAYMENT_MOTORBIKE 5
#define MAXIMUM_PARKING_TIME_IN_HOURS 6
#define FINE_AMOUNT 250
#define DAY 24

using namespace ParkingLotUtils;
class ParkedVehicle{
private:
    const VehicleType type;
    const string plate_num;
    const Time start_time;
    bool fined;
    ParkingSpot parking_spot;
public:
    ParkedVehicle(VehicleType vehicleType, LicensePlate licensePlate, Time entranceTime);
    ParkedVehicle(LicensePlate licensePlate);
    bool operator==(const ParkedVehicle& vehicle) const;
    void setParkingSpot(VehicleType parking_spot_type, unsigned int index);
    int price_calc(Time exit_time) const;
    ParkingSpot getParkingSpot() const;
    const VehicleType getVehicleType() const;
    const string getPlateNum() const;
    const Time getTime() const;
    void giveTicket();
    bool isFined() const;
};
bool operator< (const ParkedVehicle& vehicle1, const ParkedVehicle& vehicle2);
ParkedVehicle licensePlateToVehicle(LicensePlate licensePlate);
#endif //MTM_PARKED_VEHICLE_H