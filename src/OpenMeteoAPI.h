#ifndef WEATHERAPP_OPENMETEOAPI_H
#define WEATHERAPP_OPENMETEOAPI_H
#include <string>

#include "json.hpp"
using njson = nlohmann::json;

class OpenMeteoAPI {
public:
    OpenMeteoAPI();

    ~OpenMeteoAPI();

    njson getWeatherData(const std::string& search);

private:
    // error values when search term is invalid etc
    std::pair<std::pair<float, float>, std::string> ERROR_COORDS = {{1000, 1000}, ""};
    std::string TIME_ZONE = "Europe/Helsinki";

    // basic request for api returns full json which was requested
    njson apiRequest(const std::string& baseUrl, const std::string& searchUrl);

    // returns coordinates latitude, longitude
    std::pair<std::pair<float, float>, std::string> getCoordinates(const std::string& search);
};

#endif //WEATHERAPP_OPENMETEOAPI_H