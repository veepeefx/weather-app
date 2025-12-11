#ifndef WEATHERAPP_CONTROLLER_H
#define WEATHERAPP_CONTROLLER_H
#include "../View/mainwindow.h"
#include "../Model/DataHandler.h"


class Controller : public QObject {
    Q_OBJECT
public:
    Controller(MainWindow &window, DataHandler &handler);
    ~Controller();

    void makeLatestSearch();

private:
    MainWindow &mainWindow_;
    DataHandler &dataHandler_;

private slots:
    void makeSearch();
};


#endif //WEATHERAPP_CONTROLLER_H