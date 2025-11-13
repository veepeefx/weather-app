#include "OpenMeteoAPI.h"

#include "httplib.h"
#include "json.hpp"

#include <format>

using njson = nlohmann::json;

OpenMeteoAPI::OpenMeteoAPI() {}

OpenMeteoAPI::~OpenMeteoAPI() {}

njson OpenMeteoAPI::apiRequest(const std::string& baseUrl, const std::string& searchUrl)
{
    httplib::Client cli(baseUrl);

    // check that res is valid
    if (auto res = cli.Get(searchUrl)) {
        if (res->status == 200) {
            try {
                njson jsonData = njson::parse(res->body);
                // printing json for testing
                std::cout << jsonData.dump(4) << std::endl;
                return jsonData;
            } catch (njson::parse_error& e) {
                std::cerr << "JSON parse error: " << e.what() << std::endl;
            } catch (std::exception& e) {
                std::cerr << "Error during parse (not JSON): " << e.what() << std::endl;
            }
        } else {
            std::cerr << "HTTP error: " << res->status << std::endl;
        }
    } else {
        std::cerr << "Request failed" << std::endl;
    }
    return {};
}

std::pair<float, float> OpenMeteoAPI::getCoordinates(const std::string& search)
{
    std::string baseUrl = "http://geocoding-api.open-meteo.com";
    std::string searchUrl = "/v1/search?name=" + search + "&count=1&language=en&format=json";

    njson jsonData = apiRequest(baseUrl, searchUrl);

    // if jsonData is non valid returns (0,0)
    float lat = 0;
    float lng = 0;
    if (!jsonData.empty()) {
        lat = jsonData["results"][0]["latitude"].get<float>();
        lng = jsonData["results"][0]["longitude"].get<float>();
    }

    // for testing
    std::cout << lat << " " << lng << std::endl;
    return {lat, lng};
}

bool OpenMeteoAPI::getWeatherData(const std::string& search)
{
    std::pair<float, float> coords = getCoordinates(search);
    float latitude = coords.first;
    float longitude = coords.second;

    std::string baseUrl = "http://api.open-meteo.com";
    std::string searchUrl = "/v1/forecast?latitude=" + std::format("{:.6f}", latitude)
                        + "&longitude=" + std::format("{:.6f}", longitude)
                        + "&daily=temperature_2m_max,temperature_2m_min"
                        + "&hourly=temperature_2m,precipitation_probability,precipitation"
                        + "&timezone=" + TIME_ZONE + "&wind_speed_unit=ms";

    njson jsonData = apiRequest(baseUrl, searchUrl);

    // HANDLE DATA

    // return type most likely changes
    return true;
}
