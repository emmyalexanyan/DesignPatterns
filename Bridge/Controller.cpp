#include <iostream>
#include <memory>
#include <string>

class DeviceManager {
public:
    virtual ~DeviceManager() = default;
    virtual void powerOn() = 0;
    virtual void powerOff() = 0;
    virtual void checkStatus() = 0;
};

class Device {
public:
    virtual ~Device() = default;
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    virtual std::string getStatus() = 0;
};

class Printer : public Device {
public:
    void turnOn() override {
        std::cout << "Printer is powering on." << std::endl;
    }
    void turnOff() override {
        std::cout << "Printer is powering off." << std::endl;
    }
    std::string getStatus() override {
        return "Printer is ready.";
    }
};

class Router : public Device {
public:
    void turnOn() override {
        std::cout << "Router is starting up." << std::endl;
    }
    void turnOff() override {
        std::cout << "Router is shutting down." << std::endl;
    }
    std::string getStatus() override {
        return "Router is connected.";
    }
};

class PrinterManager : public DeviceManager {
public:
    PrinterManager(std::unique_ptr<Device> device) : device(std::move(device)) {}
    void powerOn() override {
        device->turnOn();
    }
    void powerOff() override {
        device->turnOff();
    }
    void checkStatus() override {
        std::cout << device->getStatus() << std::endl;
    }
private:
    std::unique_ptr<Device> device;
};

class RouterManager : public DeviceManager {
public:
    RouterManager(std::unique_ptr<Device> device) : device(std::move(device)) {}
    void powerOn() override {
        device->turnOn();
    }
    void powerOff() override {
        device->turnOff();
    }
    void checkStatus() override {
        std::cout << device->getStatus() << std::endl;
    }
private:
    std::unique_ptr<Device> device;
};

int main() {
    auto printer = std::make_unique<Printer>();
    PrinterManager printerManager(std::move(printer));

    std::cout << "Managing Printer:" << std::endl;
    printerManager.powerOn();
    printerManager.checkStatus();
    printerManager.powerOff();

    std::cout << "Managing Router:" << std::endl;
    auto router = std::make_unique<Router>();
    RouterManager routerManager(std::move(router));
    routerManager.powerOn();
    routerManager.checkStatus();
    routerManager.powerOff();

    return 0;
}
