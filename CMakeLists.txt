cmake_minimum_required(VERSION 3.15)
project(hw3_matam)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -Werror -pedantic-errors")
add_executable(hw3_matam ParkingLot.cpp ParkingLot.h ParkingLotPrinter.cpp ParkingLotPrinter.h ParkedVehicle.h ParkedVehicle.cpp
        ParkingSpot.cpp ParkingSpot.h ParkingLotTypes.h MtmParkingLot.cpp Time.h Time.cpp UniqueArrayImp.h UniqueArray.h)