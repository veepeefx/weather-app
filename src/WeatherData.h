#ifndef WEATHERAPP_WEATHERDATA_H
#define WEATHERAPP_WEATHERDATA_H

#include <vector>

namespace WeatherData {

    inline std::string cityName{};
    inline float currentTemp{0.0f};
    inline float currentRain{0.0f};
    inline std::vector<float> tempHourly{};
    inline std::vector<float> rainHourly{};
    inline std::vector<float> rainProbabilityHourly{};

    inline std::vector<float> maxTempDaily{};
    inline std::vector<float> minTempDaily{};
    inline std::vector<float> rainDaily{};
    inline std::vector<float> rainProbabilityDailyMax{};

    inline void initVectorReserve()
    {
        const int hourlyVecSize = 24 * 7;
        tempHourly.reserve(hourlyVecSize);
        rainHourly.reserve(hourlyVecSize);
        rainProbabilityHourly.reserve(hourlyVecSize);

        const int weeklyVecSize = 7;
        maxTempDaily.reserve(weeklyVecSize);
        minTempDaily.reserve(weeklyVecSize);
        rainDaily.reserve(weeklyVecSize);
        rainProbabilityDailyMax.reserve(weeklyVecSize);
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