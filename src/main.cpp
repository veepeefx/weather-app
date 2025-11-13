#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QCoreApplication::setApplicationName("Weather App");

    MainWindow w;
    w.setWindowFlags(Qt::Window);
    w.show();

    return QApplication::exec();
}
