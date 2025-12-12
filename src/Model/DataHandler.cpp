#include "DataHandler.h"
#include "OpenMeteoAPI.h"
#include "json.hpp"

#include <fstream>
#include <iostream>


DataHandler::DataHandler()
{
    weather_ = new ForecastData();
    loadCache();
}

DataHandler::~DataHandler()
{
    saveCache();
    delete weather_;
}

bool DataHandler::updateData(const std::string& search)
{
    OpenMeteoAPI meteoApi;
    const njson data = meteoApi.getWeatherData(search);

    // don't make search if search term was not valid
    if (data.empty()) {
        return false;
    }

    saveData(data);
    addHistoryEntry(weather_->cityName);

    return true;
}

ForecastData* DataHandler::getData() const { return weather_; }
const QStringList& DataHandler::getHistory() const { return history_; }

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

void DataHandler::addHistoryEntry(const std::string &entry)
{
    QString qEntry = QString::fromStdString(entry);
    history_.removeAll(qEntry);
    history_.push_front(qEntry);
}

void DataHandler::saveCache()
{
    njson cache;
    int i = 0;

    // saving history to cache
    for (const QString& city : history_) {
        if (i >= 5) {
            break;
        }

        cache["history"].push_back(city.toStdString());
        i++;
    }

    // writing it to json file
    std::ofstream file("history_cache.json");
    if (file.is_open()) {
        file << cache.dump(4);
        file.close();
    }
}

void DataHandler::loadCache()
{
    std::ifstream file("history_cache.json");

    // checking if file is opened and fiel isn't empty
    if (!file.is_open() ||
        file.peek() == std::ifstream::traits_type::eof()) {
        return;
    }

    // loads file to json format
    njson cache;
    try {
        file >> cache;
    } catch (njson::parse_error& e) {
        std::cerr << "JSON parse error loading cache: " << e.what() << std::endl;
    }

    file.close();

    // rebuilding history from the cache
    if (cache.contains("history")) {
        for (int i = cache["history"].size() - 1; i >= 0; i--) {
            addHistoryEntry(cache["history"].at(i));
        }
    }
}

