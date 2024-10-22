#include <iostream>
#include <vector>
#include <memory>
#include <string>

class MenuComponent{
    public:
        virtual ~MenuComponent() = default;
        virtual void display() const = 0;

};

class MenuItem : public MenuComponent{
    public:
        MenuItem(std::string name) : name(std::move(name)){}
        void display() const override{
            std::cout<<"Menu Item"<<std::endl;
        }
    private:
        std::string name;
};

class Menu : public MenuComponent{
    public:
        Menu(std::string name):name(std::move(name)){}

        void add (std::unique_ptr<MenuComponent>  component){
            components.push_back(std::move(component));
        }

        void display() const override{
            std::cout<<"Menu:"<<name<<std::endl;
            for (const auto& component : components){
                component->display();}
        }
    private:
        std::string name;
        std::vector<std::unique_ptr<MenuComponent>> components;
};

int main(){
    auto mainMenu = std::make_unique<Menu>("Main Menu");
    auto fileMenu  = std::make_unique<Menu>("File Menu");
    auto editMenu = std::make_unique<Menu>("Edit Menu");
    fileMenu->add(std::make_unique<MenuItem>("New Filw"));
    fileMenu->add(std::make_unique<MenuItem>("Open File"));
    editMenu->add(std::make_unique<MenuItem>("Copy"));
    editMenu->add(std::make_unique<MenuItem>("Paste"));

    mainMenu->add(std::move(fileMenu));
    mainMenu->add(std::move(editMenu));
    mainMenu->display();

    return 0;
}