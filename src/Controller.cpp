#include "Controller.h"

#include <iostream>

#include "mainwindow.h"

#include <QObject>
#include <QLineEdit>
#include <QPushButton>


Controller::Controller(MainWindow &window, OpenMeteoAPI &api) : openMeteo_(api), mainWindow_(window)
{
    // init push actions to ui
    connect(mainWindow_.getSearchBox()->lineEdit(), &QLineEdit::returnPressed,
            this, &Controller::makeSearch);
    connect(mainWindow_.getSearchButton(), &QPushButton::clicked,
            this, &Controller::makeSearch);
}

Controller::~Controller() {}

void Controller::makeSearch()
{
    std::string search = mainWindow_.getSearchBox()->lineEdit()->text().toStdString();

    if (search.empty()) {
        return;
    }

    data_ = openMeteo_.getWeatherData(search);

    // don't make search if search term was not valid
    if (data_.empty()) {
        mainWindow_.getCityLabel()->setText("[Search not found!]");
        return;
    }

    saveData();
    updateUI();
}

void Controller::saveData()
{
    tempHourly_.clear();
    rainHourly_.clear();
    maxTempDaily_.clear();
    minTempDaily_.clear();
    rainDaily_.clear();

    njson hourly = data_.at("hourly");
    njson daily = data_.at("daily");

    njson temp = hourly.at("temperature_2m");
    njson rain = hourly.at("precipitation");

    for (int i = 0; i < temp.size(); i++) {
        tempHourly_.push_back(temp.at(i));
        rainHourly_.push_back(rain.at(i));
    }

    njson tempMax = daily.at("temperature_2m_max");
    njson tempMin = daily.at("temperature_2m_min");
    rain = daily.at("precipitation_sum");

    for (int i = 0; i < tempMax.size(); i++) {
        maxTempDaily_.push_back(tempMax.at(i));
        minTempDaily_.push_back(tempMin.at(i));
        rainDaily_.push_back(rain.at(i));
    }
}

void Controller::updateUI()
{
    // adding resulted city to history and clearing searchBox
    QString resCity = QString::fromStdString(data_.at("city"));
    mainWindow_.getSearchBox()->addItem(resCity);
    mainWindow_.getSearchBox()->lineEdit()->setText("");

    // updating view
    mainWindow_.getCityLabel()->setText(resCity);
    mainWindow_.update24hChart(tempHourly_, rainHourly_);
    mainWindow_.update7dChart(tempHourly_, rainDaily_);
}