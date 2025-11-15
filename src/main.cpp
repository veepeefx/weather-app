#include <QApplication>

#include "Controller.h"
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QCoreApplication::setApplicationName("Weather App");

    MainWindow w;
    w.setWindowFlags(Qt::Window);
    w.show();

    OpenMeteoAPI api;

    Controller controller(w, api);

    return QApplication::exec();
}
