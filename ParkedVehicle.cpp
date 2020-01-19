#include "ParkedVehicle.h"

using namespace ParkingLotUtils;
bool ParkedVehicle::operator==(const ParkedVehicle& vehicle) const{
    return this->plate_num == vehicle.plate_num;
}

ParkedVehicle::ParkedVehicle(VehicleType vehicleType, LicensePlate licensePlate, Time entranceTime):
    type(vehicleType), plate_num(licensePlate), start_time(entranceTime){
    fined = false;
}
ParkedVehicle::ParkedVehicle(LicensePlate licensePlate): type(FIRST), plate_num(licensePlate),  start_time() {
    fined = false;
}

void ParkedVehicle::setParkingSpot(const VehicleType parking_spot_type, const unsigned int index){
    ParkingSpot spot(parking_spot_type , index);
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

        case CAR:{
            payment_for_first_hour = ONE_HOUR_PAYMENT_PRIVATE_CAR;
            payment_per_hour = ABOVE_ONE_HOUR_PAYMENT_PRIVATE_CAR;
            break;
        }
        case MOTORBIKE:{
            payment_for_first_hour = ONE_HOUR_PAYMENT_MOTORBIKE;
            payment_per_hour = ABOVE_ONE_HOUR_PAYMENT_MOTORBIKE;
            break;
        }
        case HANDICAPPED:{
            break;
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

void ParkedVehicle::giveTicket(){
    fined = true;
}
bool ParkedVehicle::isFined() const{
    return fined;
}

bool operator< (const ParkedVehicle& vehicle1, const ParkedVehicle& vehicle2){
    return (vehicle1.parking_spot < vehicle2.parking_spot);
}

ParkedVehicle& ParkedVehicle::operator=(const ParkedVehicle& vehicle){
    setParkingSpot(vehicle.parking_spot.getParkingBlock(),vehicle.parking_spot.getParkingNumber());
    fined = vehicle.fined;
    return *this;
}
