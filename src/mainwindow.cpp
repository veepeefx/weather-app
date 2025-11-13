#include "mainwindow.h"
#include <QVBoxLayout>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    mainLayout_ = new QVBoxLayout(this);
}

MainWindow::~MainWindow()
{
    delete mainLayout_;
}