#include "ParkingLot.h"


namespace MtmParkingLot {
    ParkingLot::ParkingLot(unsigned int parkingBlockSizes[]) : Motorbike_Parking(parkingBlockSizes[0]),
                                                               Handicapped_Parking(parkingBlockSizes[1]),
                                                               Private_Car_Parking(parkingBlockSizes[2]) {}

    ParkingLot::~ParkingLot() = default;

    ParkingResult ParkingLot::enterParking(VehicleType vehicleType, LicensePlate licensePlate, Time entranceTime) {
        bool has_spot = true;
        ParkedVehicle new_parked_car(vehicleType, licensePlate, entranceTime);
        if (vehicleExists(Motorbike_Parking[new_parked_car],
                          Handicapped_Parking[new_parked_car],
                          Private_Car_Parking[new_parked_car])!= nullptr) {
            printEntry(new_parked_car, VEHICLE_ALREADY_PARKED);
            return VEHICLE_ALREADY_PARKED;
        }
        VehicleType park_here = HANDICAPPED;
        if (vehicleType == HANDICAPPED) {
            if (Handicapped_Parking.getCount() == Handicapped_Parking.getSize() &&
                Private_Car_Parking.getSize() > Private_Car_Parking.getCount()) {
                park_here = CAR;
            } else if (Handicapped_Parking.getCount() == Handicapped_Parking.getSize()) has_spot = false;
        } else if (((vehicleType == MOTORBIKE) && (Motorbike_Parking.getCount() == Motorbike_Parking.getSize())) ||
                   ((vehicleType == CAR) && (Private_Car_Parking.getCount() == (Private_Car_Parking.getSize())))) {
            has_spot = false;
        } else {
            park_here = vehicleType;
        }
        if (!has_spot) {
            printEntry(new_parked_car, NO_EMPTY_SPOT);
            return NO_EMPTY_SPOT;
        }
        parkTheVehicle(new_parked_car, park_here);
        return SUCCESS;
    }

    ParkingResult ParkingLot::exitParking(const LicensePlate &licensePlate, Time exitTime) {
        ParkedVehicle car_searched(licensePlate);
        const ParkedVehicle* exitingVehicle = vehicleExists(Motorbike_Parking[car_searched],
                                       Handicapped_Parking[car_searched],
                                       Private_Car_Parking[car_searched]);
        if (exitingVehicle == nullptr) {
            ParkingLotPrinter::printExitFailure(std::cout, licensePlate);
            return VEHICLE_NOT_FOUND;
        }
        int total_payment = (*exitingVehicle).priceCalculation(exitTime);
        ParkedVehicle about_to_exit(*exitingVehicle);
        exitCar(*exitingVehicle);
        ParkingLotPrinter::printVehicle(std::cout, about_to_exit.getVehicleType(), about_to_exit.getPlateNumber(),
                                        about_to_exit.getTime());
        ParkingLotPrinter::printExitSuccess(std::cout, about_to_exit.getSpot(), exitTime, total_payment);
        return SUCCESS;
    }

    ParkingResult ParkingLot::getParkingSpot(LicensePlate licensePlate, ParkingSpot &parkingSpot) const {
        ParkedVehicle vehicle(licensePlate);
        const ParkedVehicle* check_vehicle = vehicleExists(Motorbike_Parking[vehicle],
                                       Handicapped_Parking[vehicle],
                                       Private_Car_Parking[vehicle]);
        if (check_vehicle == nullptr) return VEHICLE_NOT_FOUND;
        parkingSpot = (*check_vehicle).getSpot();
        return SUCCESS;
    }

    void ParkingLot::inspectParkingLot(Time inspectionTime) {
        int ticketed_cars = 0;
        ticketed_cars += blockInspection(Motorbike_Parking, inspectionTime);
        ticketed_cars += blockInspection(Handicapped_Parking, inspectionTime);
        ticketed_cars += blockInspection(Private_Car_Parking, inspectionTime);
        ParkingLotPrinter::printInspectionResult(std::cout, inspectionTime, ticketed_cars);

    }

    ostream &operator<<(ostream &os, const ParkingLot &parkingLot) {
        ParkingLotPrinter::printParkingLotTitle(os);
        VehicleVector print_array;
        addArraysToVector(print_array, parkingLot.Motorbike_Parking , parkingLot.Handicapped_Parking,
                          parkingLot.Private_Car_Parking);
        sort(print_array.begin(),print_array.end());
        for (ParkedVehicle &car : print_array) {
            ParkingLotPrinter::printVehicle(os, car.getVehicleType(), car.getPlateNumber(),
                                            car.getTime());
            ParkingLotPrinter::printParkingSpot(os, car.getSpot());
        }
        return os;
    }

    void ParkingLot::printEntry(ParkedVehicle vehicle, ParkingResult result) {

        switch (result) {
            case SUCCESS: {
                ParkingLotPrinter::printVehicle(std::cout, vehicle.getVehicleType(), vehicle.getPlateNumber(),
                                                vehicle.getTime());
                ParkingLotPrinter::printEntrySuccess(std::cout, vehicle.getSpot());
                break;
            }
            case NO_EMPTY_SPOT: {
                ParkingLotPrinter::printVehicle(std::cout, vehicle.getVehicleType(), vehicle.getPlateNumber(),
                                                vehicle.getTime());
                ParkingLotPrinter::printEntryFailureNoSpot(std::cout);
                break;
            }
            case VEHICLE_ALREADY_PARKED: {
                ParkingLotPrinter::printVehicle(std::cout, (*(getVehiclePointer(vehicle))).getVehicleType(),
                        (*(getVehiclePointer(vehicle))).getPlateNumber(),
                                                (*(getVehiclePointer(vehicle))).getTime());
                ParkingLotPrinter::printEntryFailureAlreadyParked(std::cout,
                                                                  (*(getVehiclePointer(vehicle))).getSpot());
                break;
            }
            case VEHICLE_NOT_FOUND: {
                break;
            }
        }
    }

    void ParkingLot::parkTheVehicle(ParkedVehicle &new_parked_car, VehicleType park_here) {
        unsigned int index = -1;
        switch (park_here) {
            case (MOTORBIKE): {
                Motorbike_Parking.insert(new_parked_car);
                Motorbike_Parking.getIndex(new_parked_car, index);
                (*Motorbike_Parking.getPointerByIndex(index)).setParkingSpot(park_here,index);
                printEntry(*Motorbike_Parking.getPointerByIndex(index), SUCCESS);
                break;
            }
            case (HANDICAPPED): {
                Handicapped_Parking.insert(new_parked_car);
                Handicapped_Parking.getIndex(new_parked_car, index);
                (*Handicapped_Parking.getPointerByIndex(index)).setParkingSpot(park_here,index);
                printEntry(*Handicapped_Parking.getPointerByIndex(index), SUCCESS);
                break;
            }
            case (CAR): {
                Private_Car_Parking.insert(new_parked_car);
                Private_Car_Parking.getIndex(new_parked_car, index);
                (*Private_Car_Parking.getPointerByIndex(index)).setParkingSpot(park_here,index);
                printEntry(*Private_Car_Parking.getPointerByIndex(index), SUCCESS);
                break;
            }
        }
    }

    void ParkingLot::exitCar(ParkedVehicle about_to_exit) {
        switch (about_to_exit.getSpot().getParkingBlock()) {
            case (MOTORBIKE): {
                Motorbike_Parking.remove(about_to_exit);
                break;
            }
            case (HANDICAPPED): {
                Handicapped_Parking.remove(about_to_exit);
                break;
            }
            case (CAR): {
                Private_Car_Parking.remove(about_to_exit);
                break;
            }
        }
    }

    const ParkedVehicle* vehicleExists(const ParkedVehicle *motorbike_parking, const ParkedVehicle *handicapped_parking,
                       const ParkedVehicle *private_car_parking) {
        if (motorbike_parking != nullptr) {
            return motorbike_parking;
        } else if (handicapped_parking != nullptr) {
            return handicapped_parking;
        } else if (private_car_parking != nullptr) {
            return private_car_parking;
        }
        return nullptr;
    }

    int blockInspection(ParkingArray& block_array, Time inspectionTime) {
        int ticketed_cars = 0;
        for (unsigned int i = 0; i < block_array.getSize(); i++) {
            if (block_array.getPointerByIndex(i) == nullptr) continue;
            ParkedVehicle& inspected_car = *(block_array.getPointerByIndex(i));
            Time total_parking_time = inspectionTime - (inspected_car).getTime();
            if ((!(inspected_car).isFined()) && ((total_parking_time).toHours() > MAXIMUM_PARKING_HOURS)) {
                inspected_car.giveTicket();
                ticketed_cars++;
            }
        }
        return ticketed_cars;
    }

    const ParkedVehicle* ParkingLot::getVehiclePointer(ParkedVehicle vehicle) {
        const ParkedVehicle* vehicle_pointer = nullptr;
        if((vehicle_pointer = Motorbike_Parking[vehicle]) != nullptr) return vehicle_pointer;
        if((vehicle_pointer = Handicapped_Parking[vehicle]) != nullptr) return vehicle_pointer;
        if((vehicle_pointer = Private_Car_Parking[vehicle]) != nullptr) return vehicle_pointer;
        return nullptr;
    }

    void addArraysToVector(VehicleVector& print_array,const ParkingArray& motorbike_array,const ParkingArray& handicapped_array,
                                   const ParkingArray& private_car_array){
        for (unsigned int i = 0; i < private_car_array.getSize(); i++) {
            if (private_car_array.getPointerByIndex(i)== nullptr) continue;
            print_array.push_back(*(private_car_array.getPointerByIndex(i)));
        }
        for (unsigned int i = 0; i < motorbike_array.getSize(); i++) {
            if (motorbike_array.getPointerByIndex(i) == nullptr) continue;
            print_array.push_back(*(motorbike_array.getPointerByIndex(i)));
        }
        for (unsigned int i = 0; i < handicapped_array.getSize(); i++) {
            if (handicapped_array.getPointerByIndex(i) == nullptr) continue;
            print_array.push_back(*(handicapped_array.getPointerByIndex(i)));
        }
    }
};

