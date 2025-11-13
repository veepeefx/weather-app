#ifndef WEATHERAPP_OPENMETEOAPI_H
#define WEATHERAPP_OPENMETEOAPI_H
#include <string>

#include "json.hpp"
using njson = nlohmann::json;

class OpenMeteoAPI {
public:
    OpenMeteoAPI();

    ~OpenMeteoAPI();

    bool getWeatherData(const std::string& search);

private:
    std::string TIME_ZONE = "Europe/Helsinki";
    njson apiRequest(const std::string& baseUrl, const std::string& searchUrl);

    // returns coordinates latitude, longitude
    std::pair<float, float> getCoordinates(const std::string& search);
};


#endif //WEATHERAPP_OPENMETEOAPI_H