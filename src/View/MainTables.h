#ifndef WEATHERAPP_MAINTABLES_H
#define WEATHERAPP_MAINTABLES_H

#include <QStandardItemModel>
#include <QTableView>
#include <QVBoxLayout>

class MainTables : public QWidget {

    Q_OBJECT

public:

    MainTables(QVBoxLayout* mainWindowLayout, QWidget* parent = nullptr);
    ~MainTables();

    void updateTable();
    void changeTable();

private:

    QStandardItemModel *model24h_{nullptr};
    QStandardItemModel *model7d_{nullptr};
    QTableView *tableview_{nullptr};

    void init24hTable();
    void init7dTable();

    void update24hTable();
    void update7dTable();
};


#endif //WEATHERAPP_MAINTABLES_H