#include "ParkingLot.h"

namespace MtmParkingLot {

    ParkingLot::ParkingLot(unsigned int parkingBlockSizes[]) :
            total_num_of_motorbike_spots(parkingBlockSizes[MOTORBIKE]),
            total_num_of_car_spots(parkingBlockSizes[CAR]),
            total_num_of_handicapped_spots(parkingBlockSizes[HANDICAPPED]),
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
        ParkingLotPrinter::printVehicle(std::cout, new_parked_car.getVehicleType(), new_parked_car.getPlateNum(),
                                        new_parked_car.getTime());
        ParkingLotPrinter::printEntrySuccess(std::cout, new_parked_car.getParkingSpot());
        return SUCCESS;
    }

    ParkingResult ParkingLot::exitParking(LicensePlate licensePlate, Time exitTime) {
        ParkedVehicle const *exitingVehicle = parking_array[licensePlateToVehicle(licensePlate)];
        if (exitingVehicle == nullptr) {
            ParkingLotPrinter::printExitFailure(std::cout, licensePlate);
            return VEHICLE_NOT_FOUND;
        }
        Time total_time = exitTime - (*exitingVehicle).getTime();
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
        for (int i = 0; i < parking_array.getSize(); i++) {
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
        ParkedVehicle *print_array[parkingLot.parking_array.getSize()];
        for (int i = 0; i < (parkingLot.parking_array.getSize()); i++) {
            ParkedVehicle *const vehicle = parkingLot.parking_array[i];
            if (vehicle == nullptr) {
                print_array[i] = nullptr;
                continue;
            }
            switch (vehicle->getParkingSpot().getParkingBlock()) {
                case MOTORBIKE: {
                    print_array[vehicle->getParkingSpot().getParkingNumber() -1] = vehicle;
                }
                case HANDICAPPED: {
                    unsigned int index_shift = (parkingLot.total_num_of_motorbike_spots);
                    print_array[(vehicle->getParkingSpot().getParkingNumber() + index_shift -1)]= vehicle;
                }
                case CAR: {
                    unsigned int index_shift = (parkingLot.total_num_of_motorbike_spots +
                                       parkingLot.total_num_of_handicapped_spots -1);
                    print_array[vehicle->getParkingSpot().getParkingNumber() + index_shift]= vehicle;
                }
            }
        }
        for (int i = 0; i < (parkingLot.parking_array.getSize()); i++) {
            if (print_array[i] == nullptr) continue;
            ParkingLotPrinter::printVehicle(os, (*print_array[i]).getVehicleType(), (*print_array[i]).getPlateNum(),
                                            (*print_array[i]).getTime());
            ParkingLotPrinter::printParkingSpot(os, (*print_array[i]).getParkingSpot());

        }
        return os;

    }
}