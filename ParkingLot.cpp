#include "ParkingLot.h"
#include "UniqueArray.h"
using namespace MtmParkingLot;
static unsigned int total_parking_spots(unsigned int array[]);
ParkingLot::ParkingLot(unsigned int parkingBlockSizes[]) : parking_array(total_parking_spots(parkingBlockSizes)){

}
















static unsigned int total_parking_spots(unsigned int array[]){
    return (array[0] + array[1] + array[2]);
}