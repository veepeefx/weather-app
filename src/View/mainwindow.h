#ifndef WEATHERAPP_MAINWINDOW_H
#define WEATHERAPP_MAINWINDOW_H

#include <QComboBox>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>

#include "MainCharts.h"
#include "MainTables.h"


class DataHandler;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(DataHandler* model, QWidget *parent = nullptr);

    ~MainWindow() override;

    void changePeriod();
    void updateMainWindow(bool searchSuccessful);

    // getters
    [[nodiscard]] QComboBox* getSearchBox() const;
    [[nodiscard]] QPushButton* getSearchButton() const;
    [[nodiscard]] QPushButton* getChangePeriodButton() const;

private:

    DataHandler *dataHandler_;
    MainCharts *charts_;
    MainTables *tables_;

    QVBoxLayout *mainLayout_;

    // Qt widgets
    QComboBox *searchBox_{nullptr};
    QPushButton *searchButton_{nullptr};
    QPushButton *changePeriodButton_{nullptr};
    QLabel *cityLabel_{nullptr};
    QLabel *currentTempLabel_{nullptr};
    QLabel *currentRainLabel_{nullptr};

    void initTopMenu();
    void initSearchMenu();
    void initCurrentWeather();
    void updateCurrentWeather(const ForecastData *data);

    void showEvent(QShowEvent *event) override;

private
    slots:
};


#endif //WEATHERAPP_MAINWINDOW_H