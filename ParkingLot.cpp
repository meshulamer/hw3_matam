#include "ParkingLot.h"
#include <vector>
#include <algorithm>
namespace MtmParkingLot {

    ParkingLot::ParkingLot(unsigned int parkingBlockSizes[]) :
            total_num_of_motorbike_spots(parkingBlockSizes[MOTORBIKE]),
            total_num_of_handicapped_spots(parkingBlockSizes[HANDICAPPED]),
            total_num_of_car_spots(parkingBlockSizes[CAR]),
            parking_array(parkingBlockSizes[0] + parkingBlockSizes[1] + parkingBlockSizes[2]) {
        for (int i = 0; i < NUMBER_OF_UNIQUE_CARS; i++) {
            parking_spots[i] = parkingBlockSizes[i];
        }
    }

    ParkingLot::~ParkingLot() = default;

    ParkingResult ParkingLot::enterParking(VehicleType vehicleType, LicensePlate licensePlate, Time entranceTime) {
        bool has_spot = true;
        ParkedVehicle new_parked_car(vehicleType, licensePlate, entranceTime);
        if (parking_array[new_parked_car] != nullptr) {
            MtmParkingLot::printEntry(*(parking_array[new_parked_car]), VEHICLE_ALREADY_PARKED);
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
            MtmParkingLot::printEntry(new_parked_car, NO_EMPTY_SPOT);
            return NO_EMPTY_SPOT;
        }
        unsigned int index_shift = this->pickParkingIndex(park_here);
        new_parked_car.setParkingSpot(park_here, (index_shift - parking_spots[park_here]));
        parking_array.insert(new_parked_car);
        parking_spots[park_here]--;
        MtmParkingLot::printEntry(new_parked_car, SUCCESS);
        return SUCCESS;
    }

    ParkingResult ParkingLot::exitParking(const LicensePlate &licensePlate, Time exitTime) {
        ParkedVehicle const *exitingVehicle = parking_array[licensePlateToVehicle(licensePlate)];
        if (exitingVehicle == nullptr) {
            ParkingLotPrinter::printExitFailure(std::cout, licensePlate);
            return VEHICLE_NOT_FOUND;
        }
        int total_payment = (*exitingVehicle).price_calc(exitTime);
        ParkedVehicle about_to_exit = *exitingVehicle;
        parking_array.remove(*exitingVehicle);
        parking_spots[about_to_exit.getParkingSpot().getParkingBlock()]++;
        ParkingLotPrinter::printVehicle(std::cout, about_to_exit.getVehicleType(), about_to_exit.getPlateNum(),
                                        about_to_exit.getTime());
        ParkingLotPrinter::printExitSuccess(std::cout, about_to_exit.getParkingSpot(), exitTime, total_payment);
        return SUCCESS;
    }

    ParkingResult ParkingLot::getParkingSpot(LicensePlate licensePlate, ParkingSpot &parkingSpot) const {
        ParkedVehicle const *vehicle = parking_array[licensePlateToVehicle(licensePlate)];
        if (vehicle == nullptr) return VEHICLE_NOT_FOUND;
        parkingSpot = (*vehicle).getParkingSpot();
        return SUCCESS;
    }

    void ParkingLot::inspectParkingLot(Time inspectionTime) {
        int ticketed_cars = 0;
        for (unsigned int i = 0; i < parking_array.getSize(); i++) {
            if (parking_array[i] == nullptr) continue;
            ParkedVehicle &inspected_car = *(parking_array[i]);
            Time total_parking_time = inspectionTime - inspected_car.getTime();
            if ((!inspected_car.isFined()) && (total_parking_time.toHours() > DAY)) {
                inspected_car.giveTicket();
                ticketed_cars++;
            }
        }
        ParkingLotPrinter::printInspectionResult(std::cout, inspectionTime, ticketed_cars);
    }

    ostream &operator<<(ostream &os, const ParkingLot &parkingLot) {
        ParkingLotPrinter::printParkingLotTitle(os);
        std::vector<ParkedVehicle> print_array;
        for (unsigned int i = 0; i < parkingLot.parking_array.getSize(); i++) {
            if(parkingLot.parking_array[i]== nullptr) continue;
            print_array.push_back(*(parkingLot.parking_array[i]));
        }

        sort(print_array.begin(),print_array.end());
        //reverse(print_array.begin(),print_array.end()-1);
        for (ParkedVehicle& car : print_array)
        {
            ParkingLotPrinter::printVehicle(os, car.getVehicleType(), car.getPlateNum(),
                                            car.getTime());
            ParkingLotPrinter::printParkingSpot(os, car.getParkingSpot());
        }
        return os;


    }

    unsigned int ParkingLot::pickParkingIndex(VehicleType park_here) {
        unsigned int index_shift =0;
        switch (park_here) {
            case CAR: {
                index_shift += total_num_of_car_spots;
                break;
            }
            case HANDICAPPED: {
                index_shift += total_num_of_handicapped_spots;
                break;
            }
            case MOTORBIKE: {
                index_shift += total_num_of_motorbike_spots;
                break;
            }
        }
        return index_shift;

    }

    void printEntry(const ParkedVehicle &vehicle, ParkingResult result) {
        ParkingLotPrinter::printVehicle(std::cout, vehicle.getVehicleType(), vehicle.getPlateNum(),
                                        vehicle.getTime());
        switch (result) {

            case SUCCESS: {
                ParkingLotPrinter::printEntrySuccess(std::cout, vehicle.getParkingSpot());
                break;
            }
            case NO_EMPTY_SPOT: {
                ParkingLotPrinter::printEntryFailureNoSpot(std::cout);
                break;
            }
            case VEHICLE_ALREADY_PARKED: {
                ParkingLotPrinter::printEntryFailureAlreadyParked(std::cout,
                                                                  (vehicle).getParkingSpot());
                break;
            }
            case VEHICLE_NOT_FOUND: {
                break;
            }
        }
    }
}


