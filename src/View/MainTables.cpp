#include "MainTables.h"
#include "../Model/WeatherData.h"

#include <QDateTime>
#include <QHeaderView>


MainTables::MainTables(QVBoxLayout* mainWindowLayout, QWidget* parent)
{
    tableview_ = new QTableView(parent);
    tableview_->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    init24hTable();
    init7dTable();

    tableview_->setModel(model24h_);
    mainWindowLayout->addWidget(tableview_);
}

MainTables::~MainTables()
{
    delete model24h_;
    delete model7d_;
}

void MainTables::updateTable()
{
    update24hTable();
    update7dTable();
}

void MainTables::changeTable()
{
    if (tableview_->model() == model24h_) {
        tableview_->setModel(model7d_);
    } else {
        tableview_->setModel(model24h_);
    }
}

void MainTables::init24hTable()
{
    model24h_ = new QStandardItemModel(24, 3);
    model24h_->setHorizontalHeaderLabels({"°C", "mm", "💧 %"});
    QStringList list;
    list.reserve(24);
    int hour = QDateTime::currentDateTime().time().hour();

    for (int i = 0; i < 24; ++i) {
        list.push_back(QString::number((hour + i) % 24) + ":00");
    }
    model24h_->setVerticalHeaderLabels(list);
}

void MainTables::init7dTable()
{
    model7d_ = new QStandardItemModel(7, 4);
    model7d_->setHorizontalHeaderLabels({"max °C", "min °C", "mm", "💧 %"});
    QStringList list;
    list.reserve(7);
    QDate current = QDate::currentDate();

    for (int i = 0; i < 7; ++i) {
        list.push_back(QLocale().dayName(current.addDays(i).dayOfWeek(), QLocale::ShortFormat));
    }
    model7d_->setVerticalHeaderLabels(list);
}

void MainTables::update24hTable()
{
    int hour = QTime::currentTime().hour();

    for (int i = 0; i < 24; i++) {
        model24h_->setItem(i, 0, new QStandardItem(
            QString::number(WeatherData::tempHourly[i + hour], 'f', 1)));
        model24h_->setItem(i, 1, new QStandardItem(
            QString::number(WeatherData::rainHourly[i + hour], 'f', 1)));
        model24h_->setItem(i, 2, new QStandardItem(
            QString::number(WeatherData::rainProbabilityHourly[i + hour], 'f', 1)));
    }
}

void MainTables::update7dTable()
{
    for (int i = 0; i < 7; i++) {
        model7d_->setItem(i, 0, new QStandardItem(
            QString::number(WeatherData::maxTempDaily[i], 'f', 1)));
        model7d_->setItem(i, 1, new QStandardItem(
            QString::number(WeatherData::minTempDaily[i], 'f', 1)));
        model7d_->setItem(i, 2, new QStandardItem(
            QString::number(WeatherData::rainDaily[i], 'f', 1)));
        model7d_->setItem(i, 3, new QStandardItem(
            QString::number(WeatherData::rainProbabilityDailyMax[i], 'f', 1)));
    }
}