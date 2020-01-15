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

int ParkedVehicle::generic_price_calc(Time total_time, int first_hour, int next_hours, bool handicapped, bool ticket){
    int total_price = 0;
    if(total_time.toHours() == 0) return 0;
    if(ticket) total_price += FINE_AMOUNT;
    if(handicapped){
        return total_price + PAYMENT_FOR_HANDICAPPED;
    }
    if(total_time.toHours() == 1) return first_hour;
    if(total_time.toHours() >= MAXIMUM_PARKING_TIME_IN_HOURS){
      total_price += (first_hour + (MAXIMUM_PARKING_TIME_IN_HOURS - 1)*next_hours);
    }
    else{
        total_price += first_hour + (total_time.toHours()-1)*next_hours;
    }
    return total_price;
}
ParkingSpot ParkedVehicle::getParkingSpot() const {
    return parking_spot;
}