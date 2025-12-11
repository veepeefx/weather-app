#include "mainwindow.h"
#include "MainCharts.h"
#include "MainTables.h"

#include <QVBoxLayout>
#include <QChartView>
#include <QString>
#include <QTime>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>

#include "../Model/DataHandler.h"


MainWindow::MainWindow(DataHandler* model, QWidget *parent) : QMainWindow(parent), dataHandler_(model)
{
    QWidget *centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    mainLayout_ = new QVBoxLayout(centralWidget);
    QLocale::setDefault(QLocale(QLocale::English, QLocale::UnitedStates));

    initTopMenu();

    charts_ = new MainCharts(mainLayout_, this);
    tables_ = new MainTables(mainLayout_, this);

    this->resize(800,900);
}

MainWindow::~MainWindow()
{
    delete charts_;
    delete tables_;
}

void MainWindow::changePeriod()
{
    charts_->changeChart();
    tables_->changeTable();
}

void MainWindow::updateMainWindow(bool searchSuccessful)
{
    if (!searchSuccessful) {
        cityLabel_->setText("[Search not found!]");
        return;
    }

    const ForecastData* data = dataHandler_->getData();
    updateCurrentWeather(data);
    charts_->updateChart(data);
    tables_->updateTable(data);
}

QComboBox *MainWindow::getSearchBox() const { return searchBox_; }
QPushButton *MainWindow::getSearchButton() const { return searchButton_; }
QPushButton *MainWindow::getChangePeriodButton() const { return changePeriodButton_; }

void MainWindow::initTopMenu()
{
    initSearchMenu();
    initCurrentWeather();
}

void MainWindow::initSearchMenu()
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
}


void MainWindow::initCurrentWeather()
{
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

void MainWindow::updateCurrentWeather(const ForecastData* data)
{
    const QString resCity = QString::fromStdString(data->cityName);
    searchBox_->addItem(resCity);
    searchBox_->lineEdit()->setText("");

    cityLabel_->setText(resCity);
    currentTempLabel_->setText(
        QString::number(data->currentTemp, 'f', 1) + " °C");
    currentRainLabel_->setText(
        QString::number(data->currentRain, 'f', 1) + " mm");
}

// sets focus to window itself
void MainWindow::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);
    this->setFocus();
}