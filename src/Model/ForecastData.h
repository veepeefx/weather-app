#ifndef WEATHERAPP_FORECASTDATA_H
#define WEATHERAPP_FORECASTDATA_H

#include <string>
#include <vector>

class ForecastData {
public:
    ForecastData();

    ~ForecastData() = default;

    std::string cityName{};
    float currentTemp{0.0f};
    float currentRain{0.0f};
    std::vector<float> tempHourly{};
    std::vector<float> rainHourly{};
    std::vector<float> rainProbabilityHourly{};

    std::vector<float> maxTempDaily{};
    std::vector<float> minTempDaily{};
    std::vector<float> rainDaily{};
    std::vector<float> rainProbabilityDailyMax{};

    void clearData();

private:
    void initVectorReserve();

};

inline ForecastData::ForecastData()
{
    initVectorReserve();
}

inline void ForecastData::clearData()
{
    tempHourly.clear();
    rainHourly.clear();
    rainProbabilityHourly.clear();

    maxTempDaily.clear();
    minTempDaily.clear();
    rainDaily.clear();
    rainProbabilityDailyMax.clear();

    initVectorReserve();
}

inline void ForecastData::initVectorReserve()
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

#endif //WEATHERAPP_FORECASTDATA_H