#include "Controller.h"

#include <iostream>

#include "../View/mainwindow.h"

#include <QObject>
#include <QLineEdit>
#include <QPushButton>

#include "../Model/DataHandler.h"

Controller::Controller(MainWindow &window, DataHandler &handler)
: dataHandler_(handler), mainWindow_(window)
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

// searches the place which was done before closing the application
void Controller::makeLatestSearch()
{
    const QStringList& history = dataHandler_.getHistory();
    if (!history.isEmpty()) {
        bool update = dataHandler_.updateData(history.at(0).toStdString());
        mainWindow_.updateMainWindow(update);
    }
}

// searches place
void Controller::makeSearch()
{
    std::string search = mainWindow_.getSearchBox()->lineEdit()->text().toStdString();

    if (search.empty()) {
        return;
    }

    bool update = dataHandler_.updateData(search);
    mainWindow_.updateMainWindow(update);
}