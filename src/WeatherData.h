#ifndef WEATHERAPP_WEATHERDATA_H
#define WEATHERAPP_WEATHERDATA_H

#include <vector>

namespace WeatherData {

    inline std::vector<float> tempHourly;
    inline std::vector<float> rainHourly;
    inline std::vector<float> maxTempDaily;
    inline std::vector<float> minTempDaily;
    inline std::vector<float> rainDaily;

    inline void initVectorReserve()
    {
        int hourlyVecSize = 24 * 7;
        tempHourly.reserve(hourlyVecSize);
        rainHourly.reserve(hourlyVecSize);
        maxTempDaily.reserve(7);
        minTempDaily.reserve(7);
        rainDaily.reserve(7);
    }

    inline void clearData()
    {
        tempHourly.clear();
        rainHourly.clear();
        maxTempDaily.clear();
        minTempDaily.clear();
        rainDaily.clear();
    }
}

#endif //WEATHERAPP_WEATHERDATA_H