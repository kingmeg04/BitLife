cmake_minimum_required(VERSION 3.29)
project(EFInfoProjektRevision1)

set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc -static-libstdc++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")
set(CMAKE_CXX_STANDARD 23)

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
        GameStuff/MarketStuff.cpp
        GameStuff/MarketStuff.h
        GameStuff/RandomEventStuff.cpp
        GameStuff/RandomEventStuff.h
        UI/UIManager.cpp
        UI/UIManager.h
        UniversalStuff/NamingStuff.cpp
        UniversalStuff/NamingStuff.h
)
