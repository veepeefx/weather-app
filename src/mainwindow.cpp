#include "mainwindow.h"

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

#include "WeatherData.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    mainLayout_ = new QVBoxLayout(centralWidget);

    initTopMenu();
    initCharts();

    this->resize(800,900);
}

MainWindow::~MainWindow()
{
    // only one of them is allocated with parent (chartView_)
    delete chart24h_;
    delete chart7d_;

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

    QHBoxLayout *searchLayout = new QHBoxLayout();
    searchLayout->addWidget(searchBox_);
    searchLayout->addWidget(searchButton_);

    mainLayout_->addLayout(searchLayout);

    cityLabel_ = new QLabel("[Search for results]");
    cityLabel_->setStyleSheet("font-size: 24px; font-weight: bold;");

    mainLayout_->addWidget(cityLabel_);
}

void MainWindow::initCharts()
{
    init24hChart();
    init7dChart();

    // by default 24h chart is displayed
    chartView_->setChart(chart24h_);
    chartView_->setRenderHint(QPainter::Antialiasing);

    mainLayout_->addWidget(chartView_);
}

void MainWindow::init24hChart()
{
    chart24h_ = new QChart();

    // rainAxis needs specific category axis as we want to hide it to not interfere with tempSeries
    // QDateTimeAxis
    QBarCategoryAxis *rainXAxis = new QBarCategoryAxis();

    QStringList categories;
    for (int i = 0; i < 24; ++i) {
        categories << QString::number(i);
    }
    rainXAxis->setVisible(false);
    rainXAxis->setCategories(categories);

    QDateTimeAxis *tempXAxis = new QDateTimeAxis();
    tempXAxis->setFormat("hh:mm");

    QDateTime now = QDateTime::currentDateTime();
    QDateTime startHour = QDateTime(QDate(now.date()), QTime(now.time().hour(), 0));
    tempXAxis->setRange(startHour, startHour.addSecs(24 * 3600));
    tempXAxis->setTickCount(7);

    QValueAxis *tempYAxis = new QValueAxis();
    tempYAxis->setRange(-40,40);
    QValueAxis *rainYAxis = new QValueAxis();
    rainYAxis->setRange(0,40);

    tempSeries24h_ = new QLineSeries();
    rainSeries24h_ = new QBarSeries();

    chart24h_->addSeries(rainSeries24h_);
    chart24h_->addSeries(tempSeries24h_);

    chart24h_->setAxisY(rainYAxis, rainSeries24h_);
    chart24h_->setAxisY(tempYAxis, tempSeries24h_);
    chart24h_->setAxisX(rainXAxis, rainSeries24h_);
    chart24h_->setAxisX(tempXAxis, tempSeries24h_);
}

void MainWindow::init7dChart()
{
    chart7d_ = new QChart();

    QBarCategoryAxis *rainXAxis = new QBarCategoryAxis();

    QStringList categories;
    for (int i = 0; i < 7; ++i) {
        categories << QString::number(i);
    }

    rainXAxis->setVisible(false);
    rainXAxis->setCategories(categories);

    QDateTimeAxis *tempXAxis = new QDateTimeAxis();
    tempXAxis->setFormat("ddd dd.MM");

    // time starts from the beginning of the day
    QDateTime now = QDateTime::currentDateTime();
    now.setTime(QTime(0,0,0));
    tempXAxis->setRange(now, now.addDays(7).addSecs(-1));
    tempXAxis->setTickCount(8);

    QValueAxis *tempYAxis = new QValueAxis();
    tempYAxis->setRange(-40,40);
    QValueAxis *rainYAxis = new QValueAxis();
    rainYAxis->setRange(0,40);

    tempSeries7d_ = new QLineSeries();
    rainSeries7d_ = new QBarSeries();

    chart7d_->addSeries(rainSeries7d_);
    chart7d_->addSeries(tempSeries7d_);

    chart7d_->setAxisY(rainYAxis, rainSeries7d_);
    chart7d_->setAxisY(tempYAxis, tempSeries7d_);
    chart7d_->setAxisX(rainXAxis, rainSeries7d_);
    chart7d_->setAxisX(tempXAxis, tempSeries7d_);
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

QComboBox *MainWindow::getSearchBox() const { return searchBox_; }
QPushButton *MainWindow::getSearchButton() const { return searchButton_; }
QLabel *MainWindow::getCityLabel() const { return cityLabel_; }


// sets focus to window itself
void MainWindow::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);
    this->setFocus();
}