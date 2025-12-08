#include "mainwindow.h"
#include "WeatherData.h"

#include <iostream>
#include <QVBoxLayout>
#include <QLineSeries>
#include <QBarSet>
#include <QBarSeries>
#include <QChartView>
#include <QBarCategoryAxis>
#include <QString>
#include <QDateTimeAxis>
#include <QRandomGenerator>
#include <QTime>
#include <QValueAxis>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QHeaderView>
#include <QStandardItemModel>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    mainLayout_ = new QVBoxLayout(centralWidget);
    QLocale::setDefault(QLocale(QLocale::English, QLocale::UnitedStates));

    initTopMenu();
    initCharts();
    initTables();

    this->resize(800,900);
}

MainWindow::~MainWindow()
{
    // only one of them is allocated with parent (chartView_)
    delete chart24h_;
    delete chart7d_;

    delete model24h_;
    delete model7d_;

    delete mainLayout_;
}

void MainWindow::initTopMenu()
{
    searchBox_ = new QComboBox();
    searchBox_->setEditable(true);
    searchBox_->setInsertPolicy(QComboBox::NoInsert);
    searchBox_->setLineEdit(new QLineEdit);
    searchBox_->lineEdit()->setPlaceholderText("Write here");

    searchButton_ = new QPushButton("Search");
    changePeriodButton_ = new QPushButton("24 h / 7 d");

    QHBoxLayout *searchLayout = new QHBoxLayout();
    searchLayout->addWidget(searchBox_);
    searchLayout->addWidget(searchButton_);
    searchLayout->addWidget(changePeriodButton_);

    mainLayout_->addLayout(searchLayout);

    cityLabel_ = new QLabel("[Search for results]");
    cityLabel_->setStyleSheet("font-size: 24px; font-weight: bold;");

    currentTempLabel_ = new QLabel("");
    currentTempLabel_->setStyleSheet("font-size: 24px;");
    currentRainLabel_ = new QLabel("");
    currentRainLabel_->setStyleSheet("font-size: 24px;");

    QHBoxLayout *infoLayout = new QHBoxLayout();
    infoLayout->addWidget(currentTempLabel_);
    infoLayout->addWidget(currentRainLabel_);
    infoLayout->setAlignment(Qt::AlignLeft);
    infoLayout->setSpacing(10);

    mainLayout_->addWidget(cityLabel_);
    mainLayout_->addLayout(infoLayout);
}

void MainWindow::initCharts()
{
    init24hChart();
    init7dChart();

    // by default 24h chart is displayed
    chartView_ = new QChartView();
    chartView_->setChart(chart24h_);
    chartView_->setRenderHint(QPainter::Antialiasing);

    mainLayout_->addWidget(chartView_);
}

void MainWindow::initTables()
{
    tableview_ = new QTableView();
    tableview_->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    init24hTable();
    init7dTable();

    tableview_->setModel(model24h_);
    mainLayout_->addWidget(tableview_);
}

void MainWindow::init24hChart()
{
    chart24h_ = new QChart();

    // rainAxis needs specific category axis as we want to hide it to not interfere with tempSeries
    // QDateTimeAxis
    QBarCategoryAxis *rainXAxis = new QBarCategoryAxis();

    QStringList categories;
    categories.reserve(24);
    for (int i = 0; i < 24; ++i) {
        categories << QString::number(i);
    }
    rainXAxis->setVisible(false);
    rainXAxis->setCategories(categories);

    QDateTimeAxis *tempXAxis = new QDateTimeAxis();
    tempXAxis->setFormat("hh:mm");

    QDateTime start = QDateTime(QDate::currentDate(), QTime(QTime::currentTime().hour(), 0));
    QDateTime end = start.addSecs(24 * 3600);

    tempXAxis->setRange(start, end);
    tempXAxis->setTickCount(7);

    tempSeries24h_ = new QLineSeries();
    rainSeries24h_ = new QBarSeries();

    // base values
    tempYAxis24h_ = new QValueAxis();
    tempYAxis24h_->setRange(-20, 20);
    rainYAxis24h_ = new QValueAxis();
    rainYAxis24h_->setRange(0, 20);

    chart24h_->addSeries(rainSeries24h_);
    chart24h_->addSeries(tempSeries24h_);

    chart24h_->addAxis(tempYAxis24h_, Qt::AlignLeft);
    tempSeries24h_->attachAxis(tempYAxis24h_);
    chart24h_->addAxis(rainYAxis24h_, Qt::AlignRight);
    rainSeries24h_->attachAxis(rainYAxis24h_);

    chart24h_->addAxis(tempXAxis, Qt::AlignBottom);
    tempSeries24h_->attachAxis(tempXAxis);
    chart24h_->addAxis(rainXAxis, Qt::AlignBottom);
    rainSeries24h_->attachAxis(rainXAxis);
}

void MainWindow::init7dChart()
{
    chart7d_ = new QChart();

    QBarCategoryAxis *rainXAxis = new QBarCategoryAxis();
    rainXAxis->setVisible(false);
    rainXAxis->setCategories({"0", "1", "2", "3", "4", "5", "6", "7"});

    QDateTimeAxis *tempXAxis = new QDateTimeAxis();
    tempXAxis->setFormat("ddd dd.MM");

    // time starts from the beginning of the day
    QDateTime start = QDateTime(QDate::currentDate(), QTime(0,0,0));
    QDateTime end = start.addDays(7);

    tempXAxis->setRange(start, end);
    tempXAxis->setTickCount(8);

    tempSeries7d_ = new QLineSeries();
    rainSeries7d_ = new QBarSeries();

    // base values
    tempYAxis7d_ = new QValueAxis();
    tempYAxis7d_->setRange(-20, 20);
    rainYAxis7d_ = new QValueAxis();
    rainYAxis7d_->setRange(0, 20);

    chart7d_->addSeries(rainSeries7d_);
    chart7d_->addSeries(tempSeries7d_);

    chart7d_->addAxis(tempYAxis7d_, Qt::AlignLeft);
    tempSeries7d_->attachAxis(tempYAxis7d_);
    chart7d_->addAxis(rainYAxis7d_, Qt::AlignRight);
    rainSeries7d_->attachAxis(rainYAxis7d_);

    chart7d_->addAxis(tempXAxis, Qt::AlignBottom);
    tempSeries7d_->attachAxis(tempXAxis);
    chart7d_->addAxis(rainXAxis, Qt::AlignBottom);
    rainSeries7d_->attachAxis(rainXAxis);
}

void MainWindow::update24hChart()
{
    tempSeries24h_->clear();
    rainSeries24h_->clear();

    QBarSet *rainSet = new QBarSet("Rain");
    QDateTime now = QDateTime::currentDateTime();
    QDateTime startHour(QDate(now.date()), QTime(now.time().hour(), 0, 0, 0));

    int hour = now.time().hour();

    for (int i = 0; i <= 24; ++i) {
        QDateTime dt = startHour.addSecs(i * 3600);
        // QVector temp and rain starts from 0:00 so we need to leave out hours before current time
        // hour and then + i to go forward as loop goes through
        tempSeries24h_->append(dt.toMSecsSinceEpoch(), WeatherData::tempHourly[hour + i]);
        *rainSet << WeatherData::rainHourly[hour + i];
    }
    rainSeries24h_->append(rainSet);
}

void MainWindow::update7dChart()
{
    tempSeries7d_->clear();
    rainSeries7d_->clear();

    QBarSet *rainSet = new QBarSet("Rain");
    QDateTime now = QDateTime::currentDateTime();

    for (int i = 0; i < 7; ++i) {
        *rainSet << WeatherData::rainDaily[i];
        for (int j = 0; j < 24; ++j) {
            QDateTime dt(QDate(now.date()).addDays(i), QTime(j, 0, 0));
            tempSeries7d_->append(dt.toMSecsSinceEpoch(), WeatherData::tempHourly[i * 24 + j]);
        }
    }

    rainSeries7d_->append(rainSet);
}

// ranges y-axis so it is easy to read
void MainWindow::setYAxisRange()
{
    int hour = QDateTime::currentDateTime().time().hour();

    // 24h
    // temp axis
    auto tempRange = std::minmax_element(
    WeatherData::tempHourly.begin() + hour,
    WeatherData::tempHourly.begin() + hour + 25
    );

    tempYAxis24h_->setRange(*tempRange.first - 5, *tempRange.second + 5);
    tempYAxis24h_->applyNiceNumbers();
    tempYAxis24h_->setTickCount(5);

    // rain axis
    auto maxRain = std::max_element(
        WeatherData::rainHourly.begin() + hour,
        WeatherData::rainHourly.begin() + hour + 25);

    float upLimit = 4;
    if (*maxRain >= 3) {
        upLimit = *maxRain + 1;
    }
    rainYAxis24h_->setRange(0, upLimit);
    rainYAxis24h_->applyNiceNumbers();
    rainYAxis24h_->setTickCount(5);

    // 7d
    // temp axis
    auto maxWeeklyTemp = std::ranges::max_element(WeatherData::maxTempDaily);
    auto minWeeklyTemp = std::ranges::min_element(WeatherData::minTempDaily);
    tempYAxis7d_->setRange(*minWeeklyTemp - 5, *maxWeeklyTemp + 5);
    tempYAxis7d_->applyNiceNumbers();
    tempYAxis7d_->setTickCount(5);

    // rain axis
    auto maxDaily = std::ranges::max_element(WeatherData::rainDaily);

    upLimit = 4;
    if (*maxDaily >= 3) {
        upLimit = *maxDaily + 1;
    }

    rainYAxis7d_->setRange(0, upLimit);
    rainYAxis7d_->applyNiceNumbers();
    rainYAxis7d_->setTickCount(5);
}

void MainWindow::changePeriod()
{
    if (chartView_->chart() == chart24h_) {
        chartView_->setChart(chart7d_);
        tableview_->setModel(model7d_);
    } else {
        chartView_->setChart(chart24h_);
        tableview_->setModel(model24h_);
    }
}

void MainWindow::init24hTable()
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

void MainWindow::init7dTable()
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

void MainWindow::update24hTable()
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

void MainWindow::update7dTable()
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

void MainWindow::updateMainWindow()
{
    // updating charts
    update24hChart();
    update7dChart();
    setYAxisRange();

    // updating table
    update24hTable();
    update7dTable();
}

QComboBox *MainWindow::getSearchBox() const { return searchBox_; }
QPushButton *MainWindow::getSearchButton() const { return searchButton_; }
QPushButton *MainWindow::getChangePeriodButton() const { return changePeriodButton_; }
QLabel *MainWindow::getCityLabel() const { return cityLabel_; }
QLabel *MainWindow::getCurrentTempLabel() const { return currentTempLabel_; }
QLabel *MainWindow::getCurrentRainLabel() const { return currentRainLabel_; }


// sets focus to window itself
void MainWindow::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);
    this->setFocus();
}