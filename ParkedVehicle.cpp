#include "ParkedVehicle.h"
using namespace ParkingLotUtils;

bool operator<(const ParkedVehicle &vehicle1, const ParkedVehicle &vehicle2) {
    return (vehicle1.spot < vehicle2.spot);
}

bool ParkedVehicle::operator==(const ParkedVehicle &vehicle) const {
    return this->plate_num == vehicle.plate_num;
}

ParkedVehicle::ParkedVehicle(VehicleType vehicleType, LicensePlate licensePlate, Time entranceTime) :
        type(vehicleType), plate_num(licensePlate), start_time(entranceTime), spot() {
    fined = false;
}

ParkedVehicle::ParkedVehicle(LicensePlate licensePlate) : type(FIRST), plate_num(licensePlate), start_time() {
    fined = false;
}

VehicleType ParkedVehicle::getVehicleType() const {
    return type;
}

string ParkedVehicle::getPlateNumber() const {
    return plate_num;
}

Time ParkedVehicle::getTime() const {
    return start_time;
}

int ParkedVehicle::priceCalculation(Time exit_time) const {
    int total_price = 0;
    Time total_time = (exit_time - start_time);
    int payment_per_hour = 0;
    int payment_for_first_hour = 0;
    switch (type) {

        case CAR: {
            payment_for_first_hour = ONE_HOUR_PAYMENT_PRIVATE_CAR;
            payment_per_hour = ABOVE_ONE_HOUR_PAYMENT_PRIVATE_CAR;
            break;
        }
        case MOTORBIKE: {
            payment_for_first_hour = ONE_HOUR_PAYMENT_MOTORBIKE;
            payment_per_hour = ABOVE_ONE_HOUR_PAYMENT_MOTORBIKE;
            break;
        }
        case HANDICAPPED: {
            break;
        }
    }
    if (total_time.toHours() == 0) return 0;
    if (fined) total_price += FINE_AMOUNT;
    if (type == HANDICAPPED) {
        return (total_price + PAYMENT_FOR_HANDICAPPED);
    }
    if (total_time.toHours() == 1) return payment_for_first_hour;
    if (total_time.toHours() >= MAXIMUM_PARKING_TIME_IN_HOURS) {
        total_price += (payment_for_first_hour + (MAXIMUM_PARKING_TIME_IN_HOURS - 1) * payment_per_hour);
    } else {
        total_price += (payment_for_first_hour + (int) (total_time.toHours() - 1) * payment_per_hour);
    }
    return total_price;
}

void ParkedVehicle::giveTicket() {
    this->fined = true;
}

bool ParkedVehicle::isFined() const {
    return fined;
}

ParkedVehicle &ParkedVehicle::operator=(const ParkedVehicle &vehicle) {
    spot = vehicle.spot;
    plate_num = vehicle.plate_num;
    fined = vehicle.fined;
    start_time = vehicle.start_time;
    type = vehicle.type;
    return *this;
}

void ParkedVehicle::setParkingSpot(VehicleType parkingBlock, unsigned int index) {
    ParkingSpot new_spot(parkingBlock, index);
    spot = new_spot;
}

ParkingSpot ParkedVehicle::getSpot() const {
    return spot;
}

