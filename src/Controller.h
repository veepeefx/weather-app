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

private slots:
    void makeSearch();
};


#endif //WEATHERAPP_CONTROLLER_H