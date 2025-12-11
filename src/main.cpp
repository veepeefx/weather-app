#include "Controller/Controller.h"
#include "Model/DataHandler.h"
#include "View/mainwindow.h"

#include <QApplication>


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QCoreApplication::setApplicationName("Weather App");

    DataHandler model;

    MainWindow view(&model);
    view.setWindowFlags(Qt::Window);
    view.show();

    Controller controller(view, model);
    // if user has history loads it back and loads latest search
    controller.makeLatestSearch();

    return QApplication::exec();
}
