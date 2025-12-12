#ifndef WEATHERAPP_MAINTABLES_H
#define WEATHERAPP_MAINTABLES_H

#include "../Model/ForecastData.h"

#include <QStandardItemModel>
#include <QTableView>
#include <QVBoxLayout>


class MainTables : public QWidget {

    Q_OBJECT

public:

    MainTables(QVBoxLayout* mainWindowLayout, QWidget* parent = nullptr);
    ~MainTables();

    // updates 24h and 7d tables fully according the given data
    void updateTable(const ForecastData* data);

    // changes from 24h -> 7d table or vice versa
    void changeTable();

private:

    QStandardItemModel *model24h_{nullptr};
    QStandardItemModel *model7d_{nullptr};
    QTableView *tableview_{nullptr};

    void init24hTable();
    void init7dTable();

    void update24hTable(const ForecastData* data);
    void update7dTable(const ForecastData* data);
};


#endif //WEATHERAPP_MAINTABLES_H