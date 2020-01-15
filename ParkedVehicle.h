#ifndef MTM_PARKED_VEHICLE_H
#define MTM_PARKED_VEHICLE_H

#include "ParkingSpot.h"
#include "ParkingLotTypes.h"

#define ONE_HOUR_PAYMENT_PRIVATE_CAR 20
#define ONE_HOUR_PAYMENT_MOTORBIKE 10
#define PAYMENT_FOR_HANDICAPPED 15
#define ABOVE_ONE_HOUR_PAYMENT_PRIVATE_CAR 10
#define ABOVE_ONE_HOUR_PAYMENT_MOTORBIKE 5
#define MAXIMUM_PARKING_TIME_IN_HOURS 6
#define DAY 24

class ParkedVehicle{
    friend class ParkingLot;
protected:
    const VehicleType type;
    const string plate_num;
    const Time start_time;
    bool fined;
    ParkingSpot parking_spot;
    virtual int calc_payment(const Time exit_time) const = 0;
public:
    ParkedVehicle(VehicleType vehicleType, LicensePlate licensePlate, Time entranceTime);
    ParkedVehicle(LicensePlate licensePlate);
    bool operator==(const ParkedVehicle& vehicle) const;
    void setParkingSpot(const VehicleType type, const unsigned int index);
};
class Motorbike : public ParkedVehicle{
private:
    int calc_payment(const Time exit_time) const override;

};
class Handicapped : public ParkedVehicle{
private:
    int calc_payment(const Time exit_time) const override;

};
class PrivateCar : public ParkedVehicle{
private:
    int calc_payment(const Time exit_time) const override;

};

int generic_price_calc(Time total_time, int first_hour, int next_hours, bool handicapped, bool ticket);

#endif //MTM_PARKED_VEHICLE_H