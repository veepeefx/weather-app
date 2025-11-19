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
    [[nodiscard]] QComboBox* getSearchBox() const;
    [[nodiscard]] QPushButton* getSearchButton() const;
    [[nodiscard]] QLabel* getCityLabel() const;

    void update24hChart();
    void update7dChart();

private:
    // layouts
    QVBoxLayout *mainLayout_;

    // widgets
    QComboBox *searchBox_;
    QPushButton *searchButton_;
    QLabel *cityLabel_;

    // chart items
    QChart *chart24h_;
    QLineSeries *tempSeries24h_;
    QBarSeries *rainSeries24h_;

    QChart *chart7d_;
    QLineSeries *tempSeries7d_;
    QBarSeries *rainSeries7d_;

    QChartView *chartView_ = new QChartView();

    void initTopMenu();
    void initCharts();

    void init24hChart();
    void init7dChart();

    void showEvent(QShowEvent *event) override;

private
    slots:
};


#endif //WEATHERAPP_MAINWINDOW_H