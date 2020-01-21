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
    ParkingSpot spot;
public:
    ParkedVehicle(VehicleType vehicleType, LicensePlate licensePlate, Time entranceTime);
    explicit ParkedVehicle(LicensePlate licensePlate);
    ~ParkedVehicle() = default;
    bool operator==(const ParkedVehicle& vehicle) const;
    int price_calc(Time exit_time) const;
    VehicleType getVehicleType() const;
    string getPlateNum() const;
    Time getTime() const;
    void giveTicket();
    bool isFined() const;
    ParkedVehicle operator=(const ParkedVehicle& vehicle);
    void setParkingSpot(VehicleType parkingBlock, unsigned int index);
    ParkingSpot getSpot() const;
};

ParkedVehicle licensePlateToVehicle(LicensePlate licensePlate);
#endif //MTM_PARKED_VEHICLE_H