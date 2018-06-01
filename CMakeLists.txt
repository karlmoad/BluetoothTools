cmake_minimum_required(VERSION 3.10)
project(BluetoothTools)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

message("QT CMAKE DIR....")
message("$ENV{QT_DIR}")
set(CMAKE_PREFIX_PATH $ENV{QT_DIR})

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Core Widgets Bluetooth REQUIRED)

add_executable(BluetoothTools MACOSX_BUNDLE main.cpp
                                resources.qrc
                                MainWindow.cpp MainWindow.h
                                BluetoothToolsApplication.h
                                Forms/BlueToothScanForm.cpp Forms/BlueToothScanForm.h
                                Utility.cpp Utility.h DeviceListItem.cpp DeviceListItem.h)

target_link_libraries(BluetoothTools Qt5::Core Qt5::Widgets Qt5::Bluetooth)

