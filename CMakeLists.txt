cmake_minimum_required(VERSION 3.20)

project(QtForbotCourse VERSION 1.0 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_COLOR_DIAGNOSTICS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(MSVC)
    add_compile_options(-W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Wno-unused-function -Werror)
endif()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets SerialPort Bluetooth Quick)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets SerialPort Bluetooth Quick)

add_subdirectory(part-1-about-qt)
add_subdirectory(part-2-serial-communication)
add_subdirectory(part-4-bluetooth-communication)
add_subdirectory(part-5-about-qml)
add_subdirectory(part-6-cpp-qml-integration)
add_subdirectory(part-7-freezing-ui)
add_subdirectory(part-8-multithreading)
add_subdirectory(part-9-multitasking)
