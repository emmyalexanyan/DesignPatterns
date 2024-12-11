#include <iostream>
#include <memory>
#include <string>

class TrafficLightContext;

class TrafficLightState {
public:
    virtual ~TrafficLightState() = default;
    virtual void handle(TrafficLightContext& context) = 0;
    virtual std::string getStateName() const = 0;
};

class TrafficLightContext {
public:
    explicit TrafficLightContext(std::shared_ptr<TrafficLightState> initialState) : state(std::move(initialState)) {}

    void setState(const std::shared_ptr<TrafficLightState>& newState) {
        state = newState;
    }

    void request() {
        state->handle(*this);
    }

    std::string getStateName() const {
        return state->getStateName();
    }

private:
    std::shared_ptr<TrafficLightState> state;
};

class RedState : public TrafficLightState {
public:
    void handle(TrafficLightContext& context) override {
        std::cout << "Switching from Red to Green." << std::endl;
        context.setState(std::make_shared<GreenState>());
    }

    std::string getStateName() const override {
        return "Red";
    }
};

class GreenState : public TrafficLightState {
public:
    void handle(TrafficLightContext& context) override {
        std::cout << "Switching from Green to Yellow." << std::endl;
        context.setState(std::make_shared<YellowState>());
    }

    std::string getStateName() const override {
        return "Green";
    }
};

class YellowState : public TrafficLightState {
public:
    void handle(TrafficLightContext& context) override {
        std::cout << "Switching from Yellow to Red." << std::endl;
        context.setState(std::make_shared<RedState>());
    }

    std::string getStateName() const override {
        return "Yellow";
    }
};

int main() {
    auto redState = std::make_shared<RedState>();
    TrafficLightContext trafficLight(redState);

    for (int i = 0; i < 6; ++i) {
        std::cout << "Current State: " << trafficLight.getStateName() << std::endl;
        trafficLight.request();
    }

    return 0;
}
