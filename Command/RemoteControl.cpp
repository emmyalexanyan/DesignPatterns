#include <iostream>
#include <memory>
#include <vector>
#include <string>

class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
};

class Light {
public:
    void turnOn() {
        std::cout << "Light is ON" << std::endl;
    }

    void turnOff() {
        std::cout << "Light is OFF" << std::endl;
    }
};

class Conditioner {
public:
    void turnOn() {
        std::cout << "Conditioner is ON" << std::endl;
    }

    void turnOff() {
        std::cout << "Conditioner is OFF" << std::endl;
    }
};

class LightOnCommand : public Command {
public:
    explicit LightOnCommand(std::shared_ptr<Light> light) : light(std::move(light)) {}

    void execute() override {
        light->turnOn();
    }

    void undo() override {
        light->turnOff();
    }

private:
    std::shared_ptr<Light> light;
};

class LightOffCommand : public Command {
public:
    explicit LightOffCommand(std::shared_ptr<Light> light) : light(std::move(light)) {}

    void execute() override {
        light->turnOff();
    }

    void undo() override {
        light->turnOn();
    }

private:
    std::shared_ptr<Light> light;
};

class ConditionerOnCommand : public Command {
public:
    explicit ConditionerOnCommand(std::shared_ptr<Conditioner> conditioner) : conditioner(std::move(conditioner)) {}

    void execute() override {
        conditioner->turnOn();
    }

    void undo() override {
        conditioner->turnOff();
    }

private:
    std::shared_ptr<Conditioner> conditioner;
};

class ConditionerOffCommand : public Command {
public:
    explicit ConditionerOffCommand(std::shared_ptr<Conditioner> conditioner) : conditioner(std::move(conditioner)) {}

    void execute() override {
        conditioner->turnOff();
    }

    void undo() override {
        conditioner->turnOn();
    }

private:
    std::shared_ptr<Conditioner> conditioner;
};

class RemoteControl {
public:
    void setCommand(const std::shared_ptr<Command>& command) {
        this->command = command;
    }

    void pressButton() {
        if (command) {
            command->execute();
            commandHistory.push_back(command);
        }
    }

    void pressUndo() {
        if (!commandHistory.empty()) {
            commandHistory.back()->undo();
            commandHistory.pop_back();
        }
    }

private:
    std::shared_ptr<Command> command;
    std::vector<std::shared_ptr<Command>> commandHistory;
};

int main() {
    auto light = std::make_shared<Light>();
    auto conditioner = std::make_shared<Conditioner>();

    auto lightOn = std::make_shared<LightOnCommand>(light);
    auto lightOff = std::make_shared<LightOffCommand>(light);
    auto conditionerOn = std::make_shared<ConditionerOnCommand>(conditioner);
    auto conditionerOff = std::make_shared<ConditionerOffCommand>(conditioner);

    RemoteControl remote;

    remote.setCommand(lightOn);
    remote.pressButton();
    remote.pressUndo();

    remote.setCommand(lightOff);
    remote.pressButton();
    remote.pressUndo();

    remote.setCommand(conditionerOn);
    remote.pressButton();
    remote.pressUndo();

    remote.setCommand(conditionerOff);
    remote.pressButton();
    remote.pressUndo();

    return 0;
}
