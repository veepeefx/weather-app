#ifndef WEATHERAPP_DATAHANDLER_H
#define WEATHERAPP_DATAHANDLER_H

#include "ForecastData.h"
#include "json.hpp"

#include <QStringList>

using njson = nlohmann::json;

class DataHandler {
public:
    DataHandler();

    ~DataHandler();

    bool updateData(const std::string& search);
    [[nodiscard]] ForecastData* getData() const;
    [[nodiscard]] const QStringList& getHistory() const;

private:
    ForecastData *weather_;
    QStringList history_;

    void saveData(const njson &data);
    void addHistoryEntry(const std::string &entry);
    void saveCache();
    void loadCache();
};


#endif //WEATHERAPP_DATAHANDLER_H