#include "DataHandler.h"
#include "json.hpp"
#include "OpenMeteoAPI.h"

DataHandler::DataHandler()
{
    weather_ = new ForecastData();
}

DataHandler::~DataHandler()
{
    delete weather_;
}

bool DataHandler::updateData(const std::string& search)
{
    OpenMeteoAPI meteoApi;

    const njson data = meteoApi.getWeatherData(search);

    // don't make search if search term was not valid or api call has some problems
    if (data.empty()) {
        return false;
    }

    saveData(data);
    return true;
}

ForecastData* DataHandler::getData() const
{
    return weather_;
}

void DataHandler::saveData(const njson &data)
{
    weather_->clearData();

    weather_->cityName= data.at("city");

    njson current = data.at("current");
    njson hourly = data.at("hourly");
    njson daily = data.at("daily");

    weather_->currentTemp = current.at("temperature_2m");
    weather_->currentRain = current.at("precipitation");

    njson temp = hourly.at("temperature_2m");
    njson rain = hourly.at("precipitation");
    njson rainProbability = hourly.at("precipitation_probability");

    for (int i = 0; i < temp.size(); i++) {
        weather_->tempHourly.push_back(temp.at(i));
        weather_->rainHourly.push_back(rain.at(i));
        weather_->rainProbabilityHourly.push_back(rainProbability.at(i));
    }

    njson tempMax = daily.at("temperature_2m_max");
    njson tempMin = daily.at("temperature_2m_min");
    rain = daily.at("precipitation_sum");
    rainProbability = daily.at("precipitation_probability_max");

    for (int i = 0; i < tempMax.size(); i++) {
        weather_->maxTempDaily.push_back(tempMax.at(i));
        weather_->minTempDaily.push_back(tempMin.at(i));
        weather_->rainDaily.push_back(rain.at(i));
        weather_->rainProbabilityDailyMax.push_back(rainProbability.at(i));
    }
}
