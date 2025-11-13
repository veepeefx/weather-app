# Simple weather app (C++/Qt)

## Description
Simple weather graphical desktop application. This app uses the [Open-Meteo API](https://open-meteo.com/) for forecasts and geocoordinates.

## Dependencies
All libraries are included in the project, so **no external installation is required**:
- [cpp-httplib](https://github.com/yhirose/cpp-httplib) – HTTP client (header-only, `include/httplib.h`)
- [nlohmann/json](https://github.com/nlohmann/json) – JSON parser (header-only, `include/json.hpp`)
- C++ 20, CMake, Qt6