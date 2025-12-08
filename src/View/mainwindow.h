#ifndef WEATHERAPP_MAINWINDOW_H
#define WEATHERAPP_MAINWINDOW_H

#include <QComboBox>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>

#include "MainCharts.h"
#include "MainTables.h"


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

    void updateMainWindow();
    void changePeriod();

private:
    QVBoxLayout *mainLayout_;

    // Qt widgets
    QComboBox *searchBox_;
    QPushButton *searchButton_;
    QPushButton *changePeriodButton_;
    QLabel *cityLabel_;
    QLabel *currentTempLabel_;
    QLabel *currentRainLabel_;

    MainCharts *charts_;
    MainTables *tables_;

    void initTopMenu();
    void showEvent(QShowEvent *event) override;

private
    slots:
};


#endif //WEATHERAPP_MAINWINDOW_H