#ifndef WEATHERAPP_MAINWINDOW_H
#define WEATHERAPP_MAINWINDOW_H

#include <QBarSeries>
#include <QChartView>
#include <QLineSeries>
#include <QMainWindow>
#include <QVBoxLayout>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

private:
    QVBoxLayout *mainLayout_;

    QChart *chart24h_ = new QChart();
    QLineSeries *tempSeries24h_ = new QLineSeries();
    QBarSeries *rainSeries24h_ = new QBarSeries();

    QChart *chart7d_ = new QChart();
    QLineSeries *tempSeries7d_ = new QLineSeries();
    QBarSeries *rainSeries7d_ = new QBarSeries();

    QChartView *chartView_ = new QChartView();

    void initCharts();
    void init24hChart();
    void init7dChart();

    void update24hChart();
    void update7dChart();

    // for testing fake data
    QVector<float> getTemperature();
    QVector<float> getRain();

private
    slots:
};


#endif //WEATHERAPP_MAINWINDOW_H