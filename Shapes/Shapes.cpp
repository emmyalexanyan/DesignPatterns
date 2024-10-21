//Factory
#include <iostream>
#include <memory>

class Shape{
    public:
        virtual void draw() = 0;
        virtual ~Shape() = default;
};

class  Circle : public Shape{
    public:
        void draw() override{
            std::cout<<"Circle"<<std::endl;
        }
};

class Square : public Shape{
    public:
        void draw() override{
            std::cout<<"Square"<<std::endl;
        }
};

class Triangle : public Shape{
    public:
        void draw() override{
            std::cout<<"Triangle"<<std::endl;
        }
};

class Rectangle : public Shape {
    public:
        void draw() override{
            std::cout<<"Rectangle"<<std::endl;
        }
};

class ShapeFactory {
    public:
        virtual std::unique_ptr<Shape> factoryMethod() = 0;
        virtual ~ShapeFactory() = default;

        void drawShape(){
            auto shape = factoryMethod();
            shape->draw();
        }
};

class CircleFactory : public ShapeFactory{
    public:
        std::unique_ptr<Shape> factoryMethod() override{
            return std::make_unique<Circle>();
        }
};

class SquareFactory : public ShapeFactory{
    public:
        std::unique_ptr<Shape> factoryMethod() override{
            return std::make_unique<Square>();
        }
};

class TriangleFactory : public ShapeFactory{
    public:
        std::unique_ptr<Shape> factoryMethod() override{
            return std::make_unique<Triangle>();
        }
};

class RectangleFactory : public ShapeFactory{
    public:
        std::unique_ptr<Shape> factoryMethod() override{
            return std::make_unique<Rectangle>();
        }
};

int main() {
    std::unique_ptr<ShapeFactory> factories[] = {
        std::make_unique<CircleFactory>(),
        std::make_unique<SquareFactory>(),
        std::make_unique<TriangleFactory>(),
        std::make_unique<RectangleFactory>()
    };

    int i =  0;
    while(i < 4){
        factories[i]->drawShape();
        i++;
    }
    return 0;
}