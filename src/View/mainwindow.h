#ifndef WEATHERAPP_MAINWINDOW_H
#define WEATHERAPP_MAINWINDOW_H

#include "MainCharts.h"
#include "MainTables.h"
#include "../Model/DataHandler.h"

#include <QComboBox>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>


class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(DataHandler* model, QWidget *parent = nullptr);

    ~MainWindow() override;

    // changes all views UI components period from 24h -> 7d or vice versa
    void changePeriod();

    // updates all views UI components from dataHandler_.getData() if searchSuccessful = true
    // else only infos the user about the un successful search and doesn't update anything else
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

    // sets focus to window itself
    void showEvent(QShowEvent *event) override;

};


#endif //WEATHERAPP_MAINWINDOW_H