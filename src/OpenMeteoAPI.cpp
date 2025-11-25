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
                return njson::parse(res->body);

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

std::pair<std::pair<float, float>, std::string> OpenMeteoAPI::getCoordinates(const std::string& search)
{
    std::string baseUrl = "http://geocoding-api.open-meteo.com";
    std::string searchUrl = "/v1/search?name=" + search + "&count=1&language=en&format=json";

    njson jsonData = apiRequest(baseUrl, searchUrl);

    float lat;
    float lng;
    std::string name;
    try {
        lat = jsonData.at("results").at(0).at("latitude").get<float>();
        lng = jsonData.at("results").at(0).at("longitude").get<float>();
        name = jsonData.at("results").at(0).at("name").get<std::string>();
    } catch (...) {
        return ERROR_COORDS;
    }
    return {{lat, lng}, name};
}

njson OpenMeteoAPI::getWeatherData(const std::string& search)
{
    std::pair<std::pair<float, float>, std::string> res = getCoordinates(search);
    std::pair<float, float> coords = res.first;
    std::string name = res.second;

    // if getCoorinates returned error values (search term was invalid) return empty json
    if (coords == ERROR_COORDS.first) {
        return njson::object();;
    }

    float latitude = coords.first;
    float longitude = coords.second;

    std::string baseUrl = "http://api.open-meteo.com";
    std::string searchUrl = "/v1/forecast?latitude=" + std::format("{:.6f}", latitude)
                        + "&longitude=" + std::format("{:.6f}", longitude)
                        + "&daily=temperature_2m_max,temperature_2m_min,precipitation_sum,precipitation_probability_max"
                        + "&hourly=temperature_2m,precipitation_probability,precipitation"
                        + "&current=temperature_2m,precipitation"
                        + "&timezone=" + TIME_ZONE + "&wind_speed_unit=ms";
    // example search for easier access:
    // https://api.open-meteo.com/v1/forecast?latitude=51&longitude=51&daily=temperature_2m_max,temperature_2m_min,precipitation_sum,precipitation_probability_max&hourly=temperature_2m,precipitation_probability,precipitation&current=temperature_2m,precipitation&timezone=Europe/Helsinki&wind_speed_unit=ms

    njson jsonData = apiRequest(baseUrl, searchUrl);

    // adding city name from geocoordinates to json with key "city"
    jsonData["city"] = name;

    return jsonData;
}