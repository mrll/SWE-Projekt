cmake_minimum_required(VERSION 3.2)
project(SWE_Projekt)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_AUTOMOC ON)
find_package(Qt4 REQUIRED QtGui QtXml)

set(SOURCE_FILES    src/main.cpp
                    src/Model/LCState.cpp src/Model/LCState.h
                    src/Model/LCLaser.cpp src/Model/LCLaser.h
                    src/Model/LCParser.cpp src/Model/LCParser.h
                    src/Model/LCCoordinate.cpp src/Model/LCCoordinate.h
                    src/View/LCUserInterface.cpp src/View/LCUserInterface.h
                    src/View/LCUI_Base.h
                    #src/Controller/LCController.cpp src/Controller/LCController.h
                    )

add_executable(SWE_Projekt ${SOURCE_FILES})
target_link_libraries(SWE_Projekt Qt4::QtGui Qt4::QtXml)