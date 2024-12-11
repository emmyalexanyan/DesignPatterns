#include <iostream>
#include <string>
#include <memory>

class Lights {
public:
    void turnOn() {
        std::cout << "Lights are turned ON." << std::endl;
    }
    void turnOff() {
        std::cout << "Lights are turned OFF." << std::endl;
    }
};

class Thermostat {
public:
    void setTemperature(int temp) {
        std::cout << "Thermostat set to " << temp << " degrees." << std::endl;
    }
};

class SecuritySystem {
public:
    void arm() {
        std::cout << "Security system is ARMED." << std::endl;
    }
    void disarm() {
        std::cout << "Security system is DISARMED." << std::endl;
    }
};

class SprinklerSystem {
public:
    void activate() {
        std::cout << "Sprinklers are ACTIVATED." << std::endl;
    }
    void deactivate() {
        std::cout << "Sprinklers are DEACTIVATED." << std::endl;
    }
};

class SmartHomeController {
public:
    SmartHomeController()
        : lights(std::make_shared<Lights>()),
          thermostat(std::make_shared<Thermostat>()),
          securitySystem(std::make_shared<SecuritySystem>()),
          sprinklerSystem(std::make_shared<SprinklerSystem>()) {}

    void activateMorningMode() {
        std::cout << "Activating Morning Mode..." << std::endl;
        lights->turnOn();
        thermostat->setTemperature(22);
        securitySystem->disarm();
    }

    void activateNightMode() {
        std::cout << "Activating Night Mode..." << std::endl;
        lights->turnOff();
        thermostat->setTemperature(18);
        securitySystem->arm();
    }

    void activateVacationMode() {
        std::cout << "Activating Vacation Mode..." << std::endl;
        lights->turnOff();
        securitySystem->arm();
        sprinklerSystem->activate();
    }

private:
    std::shared_ptr<Lights> lights;
    std::shared_ptr<Thermostat> thermostat;
    std::shared_ptr<SecuritySystem> securitySystem;
    std::shared_ptr<SprinklerSystem> sprinklerSystem;
};

int main() {
    SmartHomeController smartHome;

    std::cout << "Morning Routine --" << std::endl;
    smartHome.activateMorningMode();

    std::cout << "Night Routine --" << std::endl;
    smartHome.activateNightMode();

    std::cout << "Vacation Routine --" << std::endl;
    smartHome.activateVacationMode();

    return 0;
}
