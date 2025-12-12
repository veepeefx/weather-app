#include "MainCharts.h"

#include <QBarCategoryAxis>
#include <QBarSet>
#include <QDateTimeAxis>
#include <QVBoxLayout>
#include <QDateTime>


MainCharts::MainCharts(QVBoxLayout* mainWindowLayout, QWidget* parent)
{
    init24hChart();
    init7dChart();

    // by default 24h chart is displayed
    chartView_ = new QChartView(parent);
    chartView_->setChart(chart24h_);
    chartView_->setRenderHint(QPainter::Antialiasing);

    mainWindowLayout->addWidget(chartView_);
}

MainCharts::~MainCharts()
{
    delete chart24h_;
    delete chart7d_;
}

void MainCharts::updateChart(const ForecastData* data)
{
    update24hChart(data);
    update7dChart(data);

    setYAxisRange(data);
}

void MainCharts::changeChart()
{
    if (chartView_->chart() == chart24h_) {
        chartView_->setChart(chart7d_);
    } else {
        chartView_->setChart(chart24h_);
    }
}

void MainCharts::init24hChart()
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

    // base values used only when there is no data
    tempYAxis24h_ = new QValueAxis();
    tempYAxis24h_->setRange(-20, 20);
    rainYAxis24h_ = new QValueAxis();
    rainYAxis24h_->setRange(0, 20);

    tempYAxis24h_->setTitleText("Temperature (°C)");
    rainYAxis24h_->setTitleText("Preciptation (mm)");

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

void MainCharts::init7dChart()
{
    chart7d_ = new QChart();

    QBarCategoryAxis *rainXAxis = new QBarCategoryAxis();
    rainXAxis->setVisible(false);
    rainXAxis->setCategories({"1", "2", "3", "4", "5", "6", "7"});

    QDateTimeAxis *tempXAxis = new QDateTimeAxis();
    tempXAxis->setFormat("ddd dd.MM");

    // time starts from the beginning of the day
    QDateTime start = QDateTime(QDate::currentDate(), QTime(0,0,0));
    QDateTime end = start.addDays(7);

    tempXAxis->setRange(start, end);
    tempXAxis->setTickCount(8);

    tempSeries7d_ = new QLineSeries();
    rainSeries7d_ = new QBarSeries();

    // base values used only when there is no data
    tempYAxis7d_ = new QValueAxis();
    tempYAxis7d_->setRange(-20, 20);
    rainYAxis7d_ = new QValueAxis();
    rainYAxis7d_->setRange(0, 20);

    tempYAxis7d_->setTitleText("Temperature (°C)");
    rainYAxis7d_->setTitleText("Preciptation (mm)");

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

void MainCharts::update24hChart(const ForecastData* data)
{
    tempSeries24h_->clear();
    rainSeries24h_->clear();

    QBarSet *rainSet = new QBarSet("mm");
    QDateTime now = QDateTime::currentDateTime();
    QDateTime startHour(QDate(now.date()), QTime(now.time().hour(), 0, 0, 0));

    int hour = now.time().hour();

    for (int i = 0; i <= 24; ++i) {
        QDateTime dt = startHour.addSecs(i * 3600);
        // QVector temp and rain starts from 0:00 so we need to leave out hours before current time
        // hour and then + i to go forward as loop goes through
        tempSeries24h_->append(dt.toMSecsSinceEpoch(), data->tempHourly[hour + i]);
        *rainSet << data->rainHourly[hour + i];
    }
    rainSeries24h_->append(rainSet);
    tempSeries24h_->setName("°C");
}

void MainCharts::update7dChart(const ForecastData *data)
{
    tempSeries7d_->clear();
    rainSeries7d_->clear();

    QBarSet *rainSet = new QBarSet("mm");
    QDateTime now = QDateTime::currentDateTime();

    for (int i = 0; i < 7; ++i) {
        *rainSet << data->rainDaily[i];
        for (int j = 0; j < 24; ++j) {
            QDateTime dt(QDate(now.date()).addDays(i), QTime(j, 0, 0));
            tempSeries7d_->append(dt.toMSecsSinceEpoch(), data->tempHourly[i * 24 + j]);
        }
    }
    rainSeries7d_->append(rainSet);
    tempSeries7d_->setName("°C");
}

void MainCharts::setYAxisRange(const ForecastData* data)
{
    int hour = QDateTime::currentDateTime().time().hour();

    // 24h
    // temp axis
    auto tempRange = std::minmax_element(
    data->tempHourly.begin() + hour,
    data->tempHourly.begin() + hour + 25
    );

    tempYAxis24h_->setRange(*tempRange.first - 5, *tempRange.second + 5);
    tempYAxis24h_->applyNiceNumbers();
    tempYAxis24h_->setTickCount(5);

    // rain axis
    auto maxRain = std::max_element(
        data->rainHourly.begin() + hour,
        data->rainHourly.begin() + hour + 25);

    float upLimit = 4;
    if (*maxRain >= 3) {
        upLimit = *maxRain + 1;
    }
    rainYAxis24h_->setRange(0, upLimit);
    rainYAxis24h_->applyNiceNumbers();
    rainYAxis24h_->setTickCount(5);

    // 7d
    // temp axis
    auto maxWeeklyTemp = std::ranges::max_element(data->maxTempDaily);
    auto minWeeklyTemp = std::ranges::min_element(data->minTempDaily);
    tempYAxis7d_->setRange(*minWeeklyTemp - 5, *maxWeeklyTemp + 5);
    tempYAxis7d_->applyNiceNumbers();
    tempYAxis7d_->setTickCount(5);

    // rain axis
    auto maxDaily = std::ranges::max_element(data->rainDaily);

    upLimit = 4;
    if (*maxDaily >= 3) {
        upLimit = *maxDaily + 1;
    }

    rainYAxis7d_->setRange(0, upLimit);
    rainYAxis7d_->applyNiceNumbers();
    rainYAxis7d_->setTickCount(5);
}