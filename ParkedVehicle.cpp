#include "ParkedVehicle.h"
#include "ParkingSpot.h"
#include "ParkingLot.h"

using namespace ParkingLotUtils;
bool ParkedVehicle::operator==(const ParkedVehicle& vehicle) const{
    if(this->plate_num == vehicle.plate_num) return true;
    return false;
}

bool ParkedVehicle::operator==(const class ParkedVehicle & vehicle, Time inspection_time) const{
    if(fined == vehicle.fined && (inspection_time-start_time).toHours() > DAY) return true;
    return false;
}
ParkedVehicle::ParkingVehicle(VehicleType vehicleType, LicensePlate licensePlate, Time entranceTime):
    type(vehicleType), plate_num(LicensePlate), start_time(entranceTime){
    fined = false;
}
ParkedVehicle::ParkedVehicle(LicensePlate licensePlate): licensePlate(licensePlate) {}

void ParkedVehicle::setParkingSpot(const VehicleType type, const unsigned int index){
    Parkingspot spot(type , index);
    parking_spot = spot;
}

int PrivateCar::calc_payment(const Time exit_time) const override {
    return generic_price_calc(exit_time-start_time, ONE_HOUR_PAYMENT_PRIVATE_CAR,
            ABOVE_ONE_HOUR_PAYMENT_PRIVATE_CAR, false, fined);
}

int Handicapped::calc_payment(const Time exit_time) const override {
    return generic_price_calc(exit_time-start_time, PAYMENT_FOR_HANDICAPPED,
                              PAYMENT_FOR_HANDICAPPED, true, fined);
}

int Motorbike::calc_payment(const Time exit_time) const override {
    return generic_price_calc(exit_time-start_time, ONE_HOUR_PAYMENT_MOTORBIKE,
                              ABOVE_ONE_HOUR_PAYMENT_MOTORBIKE, false, fined);
}

int generic_price_calc(Time total_time, int first_hour, int next_hours, bool handicapped, bool ticket){
    int total_price = 0;
    Time total_time = exit_time - start_time;
    if(total_time.toHours() == 0) return 0;
    if(ticket) total_price += FINE_AMOUNT;
    if(handicapped){
        return total_price + PAYMENT_FOR_HANDICAPPED;
    }
    if(total_time.toHours() == 1) return first_hour;
    if(total_time.toHours() >= MAXIMUM_PARKING_TIME_IN_HOURS){
      total_price += first_hour + (MAXIMUM_PARKING_TIME_IN_HOURS - 1)*next_hours);
    }
    else{
        total_price += first_hour + (total_time.toHours()-1)*next_hours;
    }
    return total_price;
}