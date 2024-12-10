cmake_minimum_required(VERSION 3.29)
project(EFInfoProject)

set(CMAKE_CXX_STANDARD 20)

add_executable(EFInfoProject main.cpp
        family.cpp
        shop.cpp
        random_events.h
        random_events.cpp
        time_management.cpp
        Job.h
        UniversalStuff.h
        UniversalStuff.cpp)