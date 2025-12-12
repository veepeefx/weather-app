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

    // updates weather_ and history_
    bool updateData(const std::string& search);

    [[nodiscard]] ForecastData* getData() const;
    [[nodiscard]] const QStringList& getHistory() const;

private:

    ForecastData *weather_;
    QStringList history_;

    // saves weather to ForecastData weather_ for UI to use
    void saveData(const njson &data);

    // adds entry to history_ from latest to oldest
    void addHistoryEntry(const std::string &entry);

    // saves history to cache for next use. only saves up to 5 latest searches
    void saveCache();

    // loads history from cache
    void loadCache();

};


#endif //WEATHERAPP_DATAHANDLER_H