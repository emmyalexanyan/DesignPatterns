#include <iostream>
#include <memory>
#include <string>

class Coffee {
public:
    virtual ~Coffee() = default;
    virtual std::string getDescription() const = 0;
    virtual double getCost() const = 0;
};

class BasicCoffee : public Coffee {
public:
    std::string getDescription() const override {
        return "Basic Coffee";
    }
    double getCost() const override {
        return 2.0;
    }
};

class CoffeeDecorator : public Coffee {
public:
    CoffeeDecorator(std::unique_ptr<Coffee> coffee) : wrappedCoffee(std::move(coffee)) {}
    std::string getDescription() const override {
        return wrappedCoffee->getDescription();
    }
    double getCost() const override {
        return wrappedCoffee->getCost();
    }
protected:
    std::unique_ptr<Coffee> wrappedCoffee;
};

class MilkDecorator : public CoffeeDecorator {
public:
    MilkDecorator(std::unique_ptr<Coffee> coffee) : CoffeeDecorator(std::move(coffee)) {}
    std::string getDescription() const override {
        return wrappedCoffee->getDescription() + ", Milk";
    }
    double getCost() const override {
        return wrappedCoffee->getCost() + 0.5;
    }
};

class SugarDecorator : public CoffeeDecorator {
public:
    SugarDecorator(std::unique_ptr<Coffee> coffee) : CoffeeDecorator(std::move(coffee)) {}
    std::string getDescription() const override {
        return wrappedCoffee->getDescription() + ", Sugar";
    }
    double getCost() const override {
        return wrappedCoffee->getCost() + 0.3;
    }
};

class WhippedCreamDecorator : public CoffeeDecorator {
public:
    WhippedCreamDecorator(std::unique_ptr<Coffee> coffee) : CoffeeDecorator(std::move(coffee)) {}
    std::string getDescription() const override {
        return wrappedCoffee->getDescription() + ", Whipped Cream";
    }
    double getCost() const override {
        return wrappedCoffee->getCost() + 0.5;
    }
};

int main() {
    std::unique_ptr<Coffee> myCoffee = std::make_unique<BasicCoffee>();
    myCoffee = std::make_unique<MilkDecorator>(std::move(myCoffee));
    myCoffee = std::make_unique<SugarDecorator>(std::move(myCoffee));
    myCoffee = std::make_unique<WhippedCreamDecorator>(std::move(myCoffee));

    std::cout << "Your coffee: " << myCoffee->getDescription() << std::endl;
    std::cout << "Total cost: " << myCoffee->getCost() << std::endl;

    return 0;
}
