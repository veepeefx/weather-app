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
#include <QValueAxis>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

    // getters
    [[nodiscard]] QComboBox* getSearchBox() const;
    [[nodiscard]] QPushButton* getSearchButton() const;
    [[nodiscard]] QPushButton* getChangePeriodButton() const;
    [[nodiscard]] QLabel* getCityLabel() const;
    [[nodiscard]] QLabel* getCurrentTempLabel() const;
    [[nodiscard]] QLabel* getCurrentRainLabel() const;

    void updateCharts();
    void changePeriod();

private:
    // layouts
    QVBoxLayout *mainLayout_;

    // widgets
    QComboBox *searchBox_;
    QPushButton *searchButton_;
    QPushButton *changePeriodButton_;
    QLabel *cityLabel_;
    QLabel *currentTempLabel_;
    QLabel *currentRainLabel_;

    QValueAxis *tempYAxis24h_;
    QValueAxis *rainYAxis24h_;

    QValueAxis *tempYAxis7d_;
    QValueAxis *rainYAxis7d_;

    // chart items
    QChart *chart24h_;
    QLineSeries *tempSeries24h_;
    QBarSeries *rainSeries24h_;

    QChart *chart7d_;
    QLineSeries *tempSeries7d_;
    QBarSeries *rainSeries7d_;

    QChartView *chartView_;

    void initTopMenu();
    void initCharts();

    void init24hChart();
    void init7dChart();

    void update24hChart();
    void update7dChart();

    void setYAxisRange();

    void showEvent(QShowEvent *event) override;

private
    slots:
};


#endif //WEATHERAPP_MAINWINDOW_H