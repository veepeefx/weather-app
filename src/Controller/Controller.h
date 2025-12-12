#ifndef WEATHERAPP_CONTROLLER_H
#define WEATHERAPP_CONTROLLER_H

#include "../View/mainwindow.h"
#include "../Model/DataHandler.h"


class Controller : public QObject {
    Q_OBJECT
public:
    Controller(MainWindow &window, DataHandler &handler);
    ~Controller();

    // searches the place which was done before closing the application
    void makeLatestSearch();

private:

    MainWindow &mainWindow_;
    DataHandler &dataHandler_;

private slots:

    // uses user given search term from the UI and updates it if search was successful
    void makeSearch();

};


#endif //WEATHERAPP_CONTROLLER_H