#ifndef WEATHERAPP_MAINTABLES_H
#define WEATHERAPP_MAINTABLES_H

#include <QStandardItemModel>
#include <QTableView>
#include <QVBoxLayout>

class MainTables {
public:
    MainTables(QVBoxLayout* mainWindowLayout);

    ~MainTables();

    void init();
    void update();
    void changeTable();

private:

    QVBoxLayout* mainWindowLayout_;

    QStandardItemModel *model24h_{nullptr};
    QStandardItemModel *model7d_{nullptr};
    QTableView *tableview_{nullptr};

    void init24hTable();
    void init7dTable();

    void update24hTable();
    void update7dTable();
};


#endif //WEATHERAPP_MAINTABLES_H