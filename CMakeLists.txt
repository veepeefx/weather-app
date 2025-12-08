cmake_minimum_required(VERSION 4.0)
project(weatherApp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 REQUIRED COMPONENTS
        Core
        Gui
        Widgets
        Charts)


add_executable(weatherApp src/main.cpp
        src/View/mainwindow.cpp
        src/View/mainwindow.h
        src/OpenMeteoAPI.cpp
        src/OpenMeteoAPI.h
        src/Controller.cpp
        src/Controller.h
        src/WeatherData.h
        src/View/MainCharts.cpp
        src/View/MainCharts.h
        src/View/MainTables.cpp
        src/View/MainTables.h)

target_link_libraries(weatherApp
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Charts)

include_directories(include)

