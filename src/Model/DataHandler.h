#ifndef WEATHERAPP_DATAHANDLER_H
#define WEATHERAPP_DATAHANDLER_H
#include "ForecastData.h"
#include "json.hpp"

using njson = nlohmann::json;

class DataHandler {
public:
    DataHandler();

    ~DataHandler();

    bool updateData(const std::string& search);
    [[nodiscard]] ForecastData* getData() const;

private:
    ForecastData *weather_;

    void saveData(const njson &data);
};


#endif //WEATHERAPP_DATAHANDLER_H