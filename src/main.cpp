#include <QApplication>

#include "Controller.h"
#include "View/mainwindow.h"
#include "WeatherData.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QCoreApplication::setApplicationName("Weather App");

    MainWindow w;
    w.setWindowFlags(Qt::Window);
    w.show();

    OpenMeteoAPI api;

    WeatherData::initVectorReserve();
    Controller controller(w, api);

    return QApplication::exec();
}
