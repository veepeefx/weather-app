#ifndef WEATHERAPP_MAINWINDOW_H
#define WEATHERAPP_MAINWINDOW_H

#include <QBarSeries>
#include <QChartView>
#include <QComboBox>
#include <QLineSeries>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

    // getters
    QComboBox* getSearchBox();
    QPushButton* getSearchButton();
    QLabel* getCityLabel();

private:
    // layouts
    QVBoxLayout *mainLayout_;

    // widgets
    QComboBox *searchBox_;
    QPushButton *searchButton_;
    QLabel *cityLabel_;

    // chart items
    QChart *chart24h_ = new QChart();
    QLineSeries *tempSeries24h_ = new QLineSeries();
    QBarSeries *rainSeries24h_ = new QBarSeries();

    QChart *chart7d_ = new QChart();
    QLineSeries *tempSeries7d_ = new QLineSeries();
    QBarSeries *rainSeries7d_ = new QBarSeries();

    QChartView *chartView_ = new QChartView();

    void initTopMenu();
    void initCharts();

    void init24hChart();
    void init7dChart();

    void update24hChart();
    void update7dChart();

    void showEvent(QShowEvent *event) override;

    // for testing fake data
    QVector<float> getTemperature();
    QVector<float> getRain();

private
    slots:
};


#endif //WEATHERAPP_MAINWINDOW_H