#include <iostream>
#include <vector>
#include <memory>
#include <string>

class WeatherObserver {
public:
    virtual ~WeatherObserver() = default;
    virtual void update(float temperature, float humidity, float pressure) = 0;
};

class WeatherSubject {
public:
    virtual ~WeatherSubject() = default;
    virtual void addObserver(std::shared_ptr<WeatherObserver> observer) = 0;
    virtual void removeObserver(std::shared_ptr<WeatherObserver> observer) = 0;
    virtual void notifyObservers() = 0;
};

class WeatherStation : public WeatherSubject {
public:
    void addObserver(std::shared_ptr<WeatherObserver> observer) override {
        observers.push_back(observer);
    }

    void removeObserver(std::shared_ptr<WeatherObserver> observer) override {
        observers.erase(
            std::remove(observers.begin(), observers.end(), observer),
            observers.end()
        );
    }

    void notifyObservers() override {
        for (const auto& observer : observers) {
            observer->update(temperature, humidity, pressure);
        }
    }

    void setWeatherData(float temp, float hum, float pres) {
        temperature = temp;
        humidity = hum;
        pressure = pres;
        notifyObservers();
    }

private:
    std::vector<std::shared_ptr<WeatherObserver>> observers;
    float temperature = 0.0f;
    float humidity = 0.0f;
    float pressure = 0.0f;
};

class CurrentConditionsDisplay : public WeatherObserver {
public:
    void update(float temperature, float humidity, float pressure) override {
        std::cout << "Current Conditions:\n"
                  << "Temperature: " << temperature << "°C\n"
                  << "Humidity: " << humidity << "%\n"
                  << "Pressure: " << pressure << " hPa\n";
    }
};

class StatisticsDisplay : public WeatherObserver {
public:
    void update(float temperature, float humidity, float pressure) override {
        totalTemperature += temperature;
        totalUpdates++;
        std::cout << "Statistics:"
                  << "Average Temperature: " << totalTemperature / totalUpdates << "°C\n";
    }

private:
    float totalTemperature = 0.0f;
    int totalUpdates = 0;
};

class ForecastDisplay : public WeatherObserver {
public:
    void update(float temperature, float humidity, float pressure) override {
        std::cout << "Forecast:\n";
        if (pressure < 1000.0f) {
            std::cout << "Rain likely\n";
        } else if (pressure < 1020.0f) {
            std::cout << "Cloudy weather expected\n";
        } else {
            std::cout << "Clear skies ahead\n";
        }
    }
};

int main() {
    auto weatherStation = std::make_shared<WeatherStation>();

    auto currentConditions = std::make_shared<CurrentConditionsDisplay>();
    auto statisticsDisplay = std::make_shared<StatisticsDisplay>();
    auto forecastDisplay = std::make_shared<ForecastDisplay>();

    weatherStation->addObserver(currentConditions);
    weatherStation->addObserver(statisticsDisplay);
    weatherStation->addObserver(forecastDisplay);

    std::cout << "Updating weather data...\n";
    weatherStation->setWeatherData(25.3f, 65.0f, 1015.0f);

    std::cout << "Updating weather data...\n";
    weatherStation->setWeatherData(22.1f, 70.0f, 995.0f);

    return 0;
}
