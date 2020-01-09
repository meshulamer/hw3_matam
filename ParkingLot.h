#ifndef MTMPARKINGLOT_PARKINGLOT_H
#define MTMPARKINGLOT_PARKINGLOT_H

#include "ParkingLotTypes.h"
#include "Time.h"
#include "ParkingSpot.h"
#include "UniqueArray.h"
#include <string.h>

using namespace ParkingLotUtils;
typedef UniqueArray<ParkingSpot, void> ParkingArray; //Do we need a compare func?
namespace MtmParkingLot {

    using namespace ParkingLotUtils;
    using std::ostream;
    class ParkedCar{
    protected:
        const string plate_num;
        const Time start time;
        bool fined;
        virtual int calc_payment;
    };
    class Motorbike : public Parked_Car{
    private:
        const VehicleType type;
        int calc_payment{};

    };
    class Handicapped : public Parked_Car{
    private:
        const vehicle_type;
        int calc_payment{};

    };
    class PrivateCar : public Parked_Car{
    private:
        const vehicle_type;
        int calc_payment{};

    };
    class ParkingLot {
    private:
        Vec
        ParkingArray parking_array;

    public:

        ParkingLot(unsigned int parkingBlockSizes[]);
        ~ParkingLot();
        ParkingResult enterParking(VehicleType vehicleType, LicensePlate licensePlate, Time entranceTime);
        ParkingResult exitParking(LicensePlate licensePlate, Time exitTime);
        ParkingResult getParkingSpot(LicensePlate licensePlate, ParkingSpot& parkingSpot) const;
        void inspectParkingLot(Time inspectionTime);
        friend ostream& operator<<(ostream& os, const ParkingLot& parkingLot);

    };

}

#endif //MTMPARKINGLOT_PARKINGLOT_H
