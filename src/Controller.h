#ifndef WEATHERAPP_CONTROLLER_H
#define WEATHERAPP_CONTROLLER_H
#include "mainwindow.h"
#include "OpenMeteoAPI.h"

class Controller : public QObject {
    Q_OBJECT
public:
    Controller(MainWindow &window, OpenMeteoAPI &api);

    ~Controller();

private:
    MainWindow &mainWindow_;
    OpenMeteoAPI &openMeteo_;

    njson data_;

    // ALL DATA STARTS FROM 0:00 DAY OF THE REQUEST AND 168h FORWARD!

    // data every 1 hour for 7d (24 x 7 = 168 index)
    std::vector<float> tempHourly_;
    std::vector<float> rainHourly_;

    // data every 24 hour for 7d (7 index)
    std::vector<float> maxTempDaily_;
    std::vector<float> minTempDaily_;
    std::vector<float> rainDaily_;

    void saveData();
    void updateUI();

private slots:
    void makeSearch();
};


#endif //WEATHERAPP_CONTROLLER_H