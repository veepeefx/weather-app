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
    QChart *chart24h_;
    QLineSeries *tempSeries24h_;
    QBarSeries *rainSeries24h_;
    QValueAxis *tempYAxis24h_;
    QValueAxis *rainYAxis24h_;

    QChart *chart7d_;
    QLineSeries *tempSeries7d_;
    QBarSeries *rainSeries7d_;
    QValueAxis *tempYAxis7d_;
    QValueAxis *rainYAxis7d_;

    QChartView *chartView_;

    void init24hChart();
    void init7dChart();

    void update24hChart();
    void update7dChart();

    void setYAxisRange();
};


#endif //WEATHERAPP_MAINCHARTS_H