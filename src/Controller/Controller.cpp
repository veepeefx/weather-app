#include "Controller.h"

#include "../View/mainwindow.h"

#include <QObject>
#include <QLineEdit>
#include <QPushButton>

#include "../Model/WeatherData.h"


Controller::Controller(MainWindow &window, OpenMeteoAPI &api)
: openMeteo_(api), mainWindow_(window)
{
    // init push actions to ui
    connect(mainWindow_.getSearchBox()->lineEdit(), &QLineEdit::returnPressed,
            this, &Controller::makeSearch);
    connect(mainWindow_.getSearchButton(), &QPushButton::clicked,
            this, &Controller::makeSearch);
    connect(mainWindow_.getChangePeriodButton(), &QPushButton::clicked,
            this, [this] () { mainWindow_.changePeriod(); });
}

Controller::~Controller() = default;

void Controller::makeSearch()
{
    std::string search = mainWindow_.getSearchBox()->lineEdit()->text().toStdString();

    if (search.empty()) {
        return;
    }

    njson data = openMeteo_.getWeatherData(search);

    // don't make search if search term was not valid
    if (data.empty()) {
        mainWindow_.updateMainWindow(false);
        return;
    }

    saveData(data);
    mainWindow_.updateMainWindow();
}

void Controller::saveData(const njson &data)
{
    WeatherData::clearData();
    WeatherData::cityName = data.at("city");

    njson current = data.at("current");
    njson hourly = data.at("hourly");
    njson daily = data.at("daily");

    WeatherData::currentTemp = current.at("temperature_2m");
    WeatherData::currentRain = current.at("precipitation");

    njson temp = hourly.at("temperature_2m");
    njson rain = hourly.at("precipitation");
    njson rainProbability = hourly.at("precipitation_probability");

    for (int i = 0; i < temp.size(); i++) {
        WeatherData::tempHourly.push_back(temp.at(i));
        WeatherData::rainHourly.push_back(rain.at(i));
        WeatherData::rainProbabilityHourly.push_back(rainProbability.at(i));
    }

    njson tempMax = daily.at("temperature_2m_max");
    njson tempMin = daily.at("temperature_2m_min");
    rain = daily.at("precipitation_sum");
    rainProbability = daily.at("precipitation_probability_max");

    for (int i = 0; i < tempMax.size(); i++) {
        WeatherData::maxTempDaily.push_back(tempMax.at(i));
        WeatherData::minTempDaily.push_back(tempMin.at(i));
        WeatherData::rainDaily.push_back(rain.at(i));
        WeatherData::rainProbabilityDailyMax.push_back(rainProbability.at(i));
    }
}