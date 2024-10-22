#include <iostream>
#include <memory>

class Slide{
    public:
        virtual void display() = 0;
        virtual ~Slide() {};
};

class TextBox{
    public:
        virtual void type() = 0;
        virtual ~TextBox() {};
};

class Image{
    public:
        virtual void insert() = 0;
        virtual ~Image() {};
};

class Shape{
    public:
        virtual void draw() = 0;
        virtual ~Shape() {};
};

class CorporateSlide : public Slide{
    public:
        void display() override{
            std::cout<<"Corporate slide"<<std::endl;
        }
};

class CorporateTextBox : public TextBox{
    public:
        void type() override{
            std::cout<<"Corporate textbox"<<std::endl;
        }
};

class CorporateImage  :  public Image{
    public:
        void insert() override{
            std::cout<<"Corporate image"<<std::endl;
        }
};

class CorporateShape : public Shape{
    public:
        void draw() override{
            std::cout<<"Corporate shape"<<std::endl;
        }
};

class CreativeSlide : public Slide{
    public:
        void display() override{
            std::cout<<"Creative slide"<<std::endl;
        }
};

class CreativeTextBox : public TextBox{
    public:
        void type() override{
            std::cout<<"Creative textbox"<<std::endl;
        }
};

class CreativeImage  :  public Image{
    public:
        void insert() override{
            std::cout<<"Creative image"<<std::endl;
        }
};

class CreativeShape : public Shape{
    public:
        void draw() override{
            std::cout<<"Creative shape"<<std::endl;
        }
};

class PresentationFactory{
    public:
        virtual std::unique_ptr<Slide> createSlide() = 0;
        virtual std::unique_ptr<TextBox> createTextBox() = 0;
        virtual std::unique_ptr<Image> createImage() = 0;
        virtual std::unique_ptr<Shape> createShape() = 0;
        virtual ~PresentationFactory()  = default;
};

class CorporateFactory : public PresentationFactory{
    public:
        std::unique_ptr<Slide> createSlide() override{
            return std::make_unique<CorporateSlide>();
        }
        std::unique_ptr<TextBox> createTextBox() override{
            return std::make_unique<CorporateTextBox>();
        }
        std::unique_ptr<Image> createImage() override{
            return std::make_unique<CorporateImage>();
        }
        std::unique_ptr<Shape> createShape() override{
            return std::make_unique<CorporateShape>();
        };
};

class CreativeFactory : public PresentationFactory{
    public:
        std::unique_ptr<Slide> createSlide() override{
            return std::make_unique<CreativeSlide>();
        }
        std::unique_ptr<TextBox> createTextBox() override{
            return std::make_unique<CreativeTextBox>();
        }
        std::unique_ptr<Image> createImage() override{
            return std::make_unique<CreativeImage>();
        }
        std::unique_ptr<Shape> createShape() override{
            return std::make_unique<CreativeShape>();
        };
};

void clientCode(PresentationFactory* factory){
    auto slide = factory->createSlide();
    auto textbox  = factory->createTextBox();
    auto  image = factory->createImage();
    auto shape = factory->createShape();

    slide->display();
    textbox->type();
    image->insert();
    shape->draw();
}

int main(){
    std::unique_ptr<PresentationFactory> factory = std::make_unique<CorporateFactory>();
    clientCode(factory.get());

    factory = std::make_unique<CreativeFactory>();
    clientCode(factory.get());

    return 0; 
}