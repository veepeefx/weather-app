#ifndef WEATHERAPP_MAINWINDOW_H
#define WEATHERAPP_MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

private:
    QVBoxLayout *mainLayout_;

private
    slots:
};


#endif //WEATHERAPP_MAINWINDOW_H