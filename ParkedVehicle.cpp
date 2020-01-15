#include "ParkedVehicle.h"
#include "ParkingSpot.h"
#include "ParkingLot.h"

using namespace ParkingLotUtils;
bool ParkedVehicle::operator==(const ParkedVehicle& vehicle) const{
    if(this->plate_num == vehicle.plate_num) return true;
    return false;
}

/*bool ParkedVehicle::operator==(const class ParkedVehicle & vehicle) const{
    if(fined == vehicle.fined && (inspection_time-start_time).toHours() > DAY) return true;
    return false;
}*/
ParkedVehicle::ParkedVehicle(VehicleType vehicleType, LicensePlate licensePlate, Time entranceTime):
    type(vehicleType), plate_num(licensePlate), start_time(entranceTime){
    fined = false;
}
ParkedVehicle::ParkedVehicle(LicensePlate licensePlate): plate_num(licensePlate), type(FIRST), start_time() {}

void ParkedVehicle::setParkingSpot(const VehicleType type, const unsigned int index){
    ParkingSpot spot(type , index);
    parking_spot = spot;
}
ParkingSpot ParkedVehicle::getParkingSpot() const {
    return parking_spot;
}
const VehicleType ParkedVehicle::getVehicleType() const{
    return type;
}
const string ParkedVehicle::getPlateNum() const{
    return plate_num;
}
const Time ParkedVehicle::getTime() const{
    return start_time;
}
ParkedVehicle licensePlateToVehicle(LicensePlate licensePlate) {
    ParkedVehicle vehicle(FIRST,licensePlate,Time());
    return vehicle;
}
int ParkedVehicle::price_calc(Time exit_time) const {
    int total_price = 0;
    Time total_time = (exit_time - start_time);
    int payment_per_hour = 0;
    int payment_for_first_hour =0;
    switch(type){
        case MOTORBIKE:{
            payment_for_first_hour = ONE_HOUR_PAYMENT_MOTORBIKE;
            payment_per_hour = ABOVE_ONE_HOUR_PAYMENT_MOTORBIKE;
        }
        case CAR:{
            payment_for_first_hour = ONE_HOUR_PAYMENT_PRIVATE_CAR;
            payment_per_hour = ABOVE_ONE_HOUR_PAYMENT_PRIVATE_CAR;
        }
    }
    if(total_time.toHours() == 0) return 0;
    if(fined) total_price += FINE_AMOUNT;
    if(type == HANDICAPPED){
        return total_price + PAYMENT_FOR_HANDICAPPED;
    }
    if(total_time.toHours() == 1) return payment_for_first_hour;
    if(total_time.toHours() >= MAXIMUM_PARKING_TIME_IN_HOURS){
        total_price += (payment_for_first_hour + (MAXIMUM_PARKING_TIME_IN_HOURS - 1)*payment_per_hour);
    }
    else{
        total_price += payment_for_first_hour + (total_time.toHours()-1)*payment_per_hour;
    }
    return total_price;
}