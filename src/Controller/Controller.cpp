#include "Controller.h"
#include "../View/mainwindow.h"
#include "../Model/DataHandler.h"

#include <QObject>
#include <QLineEdit>
#include <QPushButton>


Controller::Controller(MainWindow &window, DataHandler &handler)
: dataHandler_(handler), mainWindow_(window)
{
    // init push/press actions to ui
    connect(mainWindow_.getSearchBox()->lineEdit(), &QLineEdit::returnPressed,
            this, &Controller::makeSearch);
    connect(mainWindow_.getSearchButton(), &QPushButton::clicked,
            this, &Controller::makeSearch);
    connect(mainWindow_.getChangePeriodButton(), &QPushButton::clicked,
            this, [this] () { mainWindow_.changePeriod(); });

    // if user has previous search history loads it back and makes latest search again
    makeLatestSearch();
}

Controller::~Controller() = default;

void Controller::makeLatestSearch()
{
    const QStringList& history = dataHandler_.getHistory();
    if (!history.isEmpty()) {
        bool update = dataHandler_.updateData(history.at(0).toStdString());
        mainWindow_.updateMainWindow(update);
    }
}

void Controller::makeSearch()
{
    std::string search = mainWindow_.getSearchBox()->lineEdit()->text().toStdString();

    if (search.empty()) {
        return;
    }

    // full update to mainwindow is only done if dataHandlers_ search/update was successful
    bool update = dataHandler_.updateData(search);
    mainWindow_.updateMainWindow(update);
}