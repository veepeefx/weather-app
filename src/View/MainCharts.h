#ifndef WEATHERAPP_MAINCHARTS_H
#define WEATHERAPP_MAINCHARTS_H

#include <QBarSeries>
#include <QChartView>
#include <QLineSeries>
#include <QValueAxis>
#include <QVBoxLayout>

class MainCharts {
public:
    MainCharts(QVBoxLayout* mainWindowLayout);

    ~MainCharts();

    void init();
    void update();
    void changeChart();

private:

    QVBoxLayout* mainWindowLayout_;

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

    void update24hChart();
    void update7dChart();

    void setYAxisRange();
};


#endif //WEATHERAPP_MAINCHARTS_H