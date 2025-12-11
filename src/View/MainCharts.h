#ifndef WEATHERAPP_MAINCHARTS_H
#define WEATHERAPP_MAINCHARTS_H

#include "../Model/ForecastData.h"

#include <QBarSeries>
#include <QChartView>
#include <QLineSeries>
#include <QValueAxis>
#include <QVBoxLayout>

class MainCharts : public QWidget {

    Q_OBJECT

public:

    MainCharts(QVBoxLayout* mainWindowLayout, QWidget* parent = nullptr);
    ~MainCharts();

    void updateChart(const ForecastData* data);
    void changeChart();

private:

    // chart items
    QChart *chart24h_{nullptr};
    QLineSeries *tempSeries24h_{nullptr};
    QBarSeries *rainSeries24h_{nullptr};
    QValueAxis *tempYAxis24h_{nullptr};
    QValueAxis *rainYAxis24h_{nullptr};

    QChart *chart7d_{nullptr};
    QLineSeries *tempSeries7d_{nullptr};
    QBarSeries *rainSeries7d_{nullptr};
    QValueAxis *tempYAxis7d_{nullptr};
    QValueAxis *rainYAxis7d_{nullptr};

    QChartView *chartView_{nullptr};

    void init24hChart();
    void init7dChart();

    void update24hChart(const ForecastData* data);
    void update7dChart(const ForecastData* data);

    void setYAxisRange(const ForecastData* data);
};


#endif //WEATHERAPP_MAINCHARTS_H