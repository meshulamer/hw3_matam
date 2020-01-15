#include "ParkingLot.h"
#include "UniqueArray.h"
#include "ParkedVehicle.h"
#include "ParkingLotPrinter.h"

using namespace MtmParkingLot;

/*class giveTickets : public UniqueArray::forEach {
public:
    virtual void operator() (ParkedVehicle &vehicle, Time inspection_time) const override {
        if()
    }
};
*/
ParkingLot::ParkingLot(unsigned int parkingBlockSizes[]):parking_array(total_parking_spots(parkingBlockSizes)){
    for(int i=0; i<NUMBER_OF_UNIQUE_CARS; i++){
        parking_spots[i] = parkingBlockSizes[i];
    }
}
ParkingLot::~ParkingLot() = default;

ParkingResult ParkingLot::enterParking(VehicleType vehicleType, LicensePlate licensePlate, Time entranceTime){
            bool has_spot = true;
            ParkedVehicle new_parked_car(vehicleType, licensePlate, entranceTime);
            if (CarAlreadyParked(new_parked_car, parking_array)) {
                ParkingLotPrinter::printEntryFailureAlreadyParked(std::cout,
                                                                  (*(parking_array[new_parked_car])).getParkingSpot());
                return VEHICLE_ALREADY_PARKED;
            }
            VehicleType park_here = HANDICAPPED;
            if (vehicleType == HANDICAPPED) {
                if (parking_spots[HANDICAPPED] == 0 && parking_spots[CAR] > 0) {
                    park_here = CAR;
                } else if (parking_spots[HANDICAPPED] == 0) has_spot = false;
            } else if (parking_spots[vehicleType] == 0) has_spot = false;
            else {
                park_here = vehicleType;
            }
            if (!has_spot) {
                ParkingLotPrinter::printEntryFailureNoSpot(std::cout);
                return NO_EMPTY_SPOT;
            }
            new_parked_car.setParkingSpot(park_here, parking_spots[park_here]);
            parking_array.insert(new_parked_car);
            parking_spots[park_here]--;
            ParkingLotPrinter::printVehicle(new_parked_car.type, new_parked_car.plate_num, new_parked_car.start_time);
            ParkingLotPrinter::printEntrySuccess(std::cout, new_parked_car.parking_spot);
    }
    return SUCCESS;
}

ParkingResult ParkingLot::exitParking(LicensePlate licensePlate, Time exitTime){
    ParkedVehicle *exitingVehicle = ParkingArray[licensePlateToVehicle(licensePlate)];
    if(exitingVehicle == nullptr) {
        ParkingLotPrinter::printExitFailure(cout, licensePlate);
        return VEHICLE_NOT_FOUND;
    }
    Time total_time = exitTime - (*exitingVehicle)->start_time;
    int total_payment = (*exitingVehicle).calc_payment(exitTime);
    ParkedVehicle about_to_exit = *exitingVehicle;
    parking_array.remove(*exitingVehicle);
    parking_spots[about_to_exit.parking_spot.getParkingBlock()]++;
    ParkingLotPrinter::printVehicle(cout, about_to_exit.type, about_to_exit.plate_num,
            about_to_exit.start_time);
    ParkingLotPrinter::printExitSuccess(cout, about_to_exit.parking_spot , exitTime , total_payment);
    return EXIT_SUCCESS
}

ParkingResult ParkingLot::getParkingSpot(LicensePlate licensePlate, ParkingSpot &parkingSpot) const{
    ParkedVehicle *vehicle = ParkingArray[licensePlateToVehicle(licensePlate)];
    if(vehicle == nullptr) return VEHICLE_NOT_FOUND;
    parkingSpot = (*vehicle).parking_spot;
    return SUCCESS;
}

/*void ParkingLot::inspectParkingLot(Time inspectionTime) {
    ParkedVehicle test_vehicle(CAR,"TestCar", inspectionTime);
    ParkedVehicle* car_to_fine;
    car_to_fine = parking_array[test_vehicle];
    while(car_to_fine!= nullptr){
        test_vehicle(wtfisthisthing);


    }
}*/

friend ostream ParkingLot::&operator<<(ostream &os, const ParkingLot &parkingLot);

static unsigned int ParkingLot::total_parking_spots(unsigned int array[]) {
    return (array[0] + array[1] + array[2]);
}
static bool CarAlreadyParked(ParkedVehicle vehicle, ParkingArray array){
    unsigned int index = -1;
    array.getIndex(vehicle,index);
    if (index == -1) return false;
    return true;
}

/*ParkedVehicle licensePlateToVehicle(LicensePlate licensePlate) {
    ParkedVehicle newVehicle(licensePlate);
    return newVehicle;
}
*/
//friend ostream& operator<<(ostream& os, const ParkingLot& parkingLot);