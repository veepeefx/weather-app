#include "Controller.h"

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

    njson data = openMeteo_.getWeatherData(search);

    // don't make search if search term was not valid
    if (data.empty()) {
        mainWindow_.getCityLabel()->setText("[Search not found!]");
        return;
    }

    // adding resulted city to history and clearing searchBox
    QString resCity = QString::fromStdString(data.at("city"));
    mainWindow_.getSearchBox()->addItem(resCity);
    mainWindow_.getSearchBox()->lineEdit()->setText("");

    // updating view
    mainWindow_.getCityLabel()->setText(resCity);
}