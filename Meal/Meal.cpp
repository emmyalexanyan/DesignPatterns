//Builder
#include<iostream>
#include<memory>
#include<string>
#include<vector>

class Meal{
    public:
        std::string mainDish;
        std::string drink;
        std::string dessert;

        void specifications(){
            std::cout << "Meal specifications:\n"<<"Main Dish:"<<mainDish<<"\n"<<"Drink:"<<drink<<"\n"<<"Dessert:"<<dessert<<std::endl;
        }
};

class MealBuilder{
    public:
        virtual ~MealBuilder() = default;
        virtual void buildMainDish() = 0;
        virtual void buildDrink() = 0;
        virtual void buildDessert() = 0;
        virtual std::unique_ptr<Meal> getMeal() = 0;
};

class VegetarianMealBuilder : public MealBuilder{
    public:
        VegetarianMealBuilder(){
            meal = std::make_unique<Meal>();
        }
        void buildMainDish() override{
            meal->mainDish = "Vegetarian dish";
        }
        void buildDrink() override{
            meal->drink = "Lemonade";
        }
        void buildDessert() override{
            meal->dessert = "Chocolate cake";
        }
        std::unique_ptr<Meal> getMeal() override{
            return std::move(meal);
        }
    private:
        std::unique_ptr<Meal> meal;
};

class NonVegetarianMealBuilder : public MealBuilder{
    public:
        NonVegetarianMealBuilder(){
            meal = std::make_unique<Meal>();
        }
        void buildMainDish() override{
            meal->mainDish = "Pepperoni pizza";
        }
        void buildDrink() override{
            meal->drink = "Martini";
        }
        void buildDessert() override{
            meal->dessert = "Honey cake";
        }
        std::unique_ptr<Meal> getMeal() override{
            return std::move(meal);
        }
    private:
        std::unique_ptr<Meal> meal;
};

class MealDirector{
    public:
        void setBuilder(MealBuilder* b){
            builder = b;
        }
        std::unique_ptr<Meal> constructMeal(){
            builder->buildMainDish();
            builder->buildDrink();
            builder->buildDessert();
            return builder->getMeal();
        }
    private:
        MealBuilder* builder;
};

int main(){
    MealDirector director;
    VegetarianMealBuilder vegetarianBuilder;
    NonVegetarianMealBuilder nonVegetarianBuilder;

    director.setBuilder(&vegetarianBuilder);
    auto vegetarianMeal = director.constructMeal();
    vegetarianMeal->specifications();
    director.setBuilder(&nonVegetarianBuilder);
    auto nonVegeterianMeal = director.constructMeal();
    nonVegeterianMeal->specifications();

    return 0;

}