cmake_minimum_required(VERSION 3.29)
project(EFInfoProjektRevision1)
#e
set(CMAKE_CXX_STANDARD 20)

add_executable(EFInfoProjektRevision1 main.cpp
        UniversalStuff/TimeStuff.h
        UniversalStuff/TimeStuff.cpp
        UniversalStuff/RandomStuff.h
        UniversalStuff/RandomStuff.cpp
        UniversalStuff/ConsoleStuff.h
        UniversalStuff/ConsoleStuff.cpp
        GameStuff/GameOverStuff.h
        GameStuff/GameOverStuff.cpp
        PlayerStuff/Money/JobStuff.h
        PlayerStuff/PlayerStuff.h
        PlayerStuff/PlayerStuff.cpp
        PlayerStuff/Money/JobStuff.cpp
        PlayerStuff/Money/CriminalStuff.cpp
        PlayerStuff/Money/CriminalStuff.h
        GameStuff/ShopStuff.cpp
        GameStuff/ShopStuff.h
)
