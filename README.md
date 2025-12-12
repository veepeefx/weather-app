# Weather App with GUI (C++/Qt)

## Description
Simple graphical desktop weather application. The GUI displays the current search and current
weather, as well as a chart showing precipitation and temperature, along with a table presenting
the data numerically. Weather forecasts can be viewed for either the next 24 hours or the next 7
days. This project uses data from [Open-Meteo API](https://open-meteo.com/) without API key for
forecasts and geocoordinates. Please review their Terms of Service and attribution requirements. 

## Features
- Weather forecast for next 24 hours or 7 days for any location
- Saves last five unique searches locally
- Simple and intuitive GUI

## Usage
- Enter city on the search bar
- Press enter key or click "search" to fetch the weather
- Change shown time period from the "24h / 7d" button
- Recent searches will appear to search bars drop down menu

## Installation / Build
1. Clone this repo
   ```
   git clone https://github.com/veepeefx/weather-app
   cd weather-app
   ```
   
2. Create a build directory and run CMake
    ```
    mkdir build
    cd build
    cmake ..
    cmake --build .
    ```
   
3. Run the executable
    ```
    ./weather-app
    ```

## Dependencies
All libraries are included in the project, so **no external installation is required**:
- [cpp-httplib](https://github.com/yhirose/cpp-httplib) – HTTP client (header-only, `include/httplib.h`)
- [nlohmann/json](https://github.com/nlohmann/json) – JSON parser (header-only, `include/json.hpp`)
- C++ 20 compatible compiler
- **CMake ≥ 3.21** (required for Qt6 projects)
- Qt6 with the following required modules: 
  - Core
  - Gui
  - Widgets
  - Charts

## License
This project uses data from [Open-Meteo API](https://open-meteo.com/). Ensure you follow their
Terms of Service.  
Licensed under MIT License.