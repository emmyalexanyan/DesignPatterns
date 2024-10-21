//Prototype
#include <iostream>
#include <memory>
#include <string>

class Document{
    public:
        virtual std::unique_ptr<Document> clone() const = 0;
        virtual void show() const = 0;
        virtual void setTitle(const std::string& title) = 0;
        virtual ~Document() = default;
};

class Report : public Document{
    public:
        Report(const std::string& title, const std::string& content) : title(title), content(content){
            std::cout << "Creating Report:" << title <<std::endl;
        }
        std::unique_ptr<Document> clone() const override{
            return std::make_unique<Report>(*this);
        }
        void show() const override{
            std::cout <<"Report Title:" <<title<<std::endl;
            std::cout<<"Content:"<<content<<std::endl;
        }
        void setTitle(const std::string& newTitle) override{
            title = newTitle;
        }
    private:
        std::string title;
        std::string content;

};

class Letter : public Document{
    public:
        Letter(const std::string& title, const std::string& reciever, const std::string& text) : title(title), reciever(reciever), text(text){
            std::cout<<"Creating Letter:"<<title<<std::endl;
        }
        std::unique_ptr<Document> clone() const override{
            return std::make_unique<Letter>(*this);
        }
        void show() const override{
            std::cout<<"Letter Title:"<<title<<std::endl;
            std::cout<<"To:"<<reciever<<std::endl;
            std::cout<<"Text:"<<text<<std::endl;
        }
        void setTitle(const std::string& newTitle) override{
            title = newTitle;
        }
    private:
        std::string title;
        std::string reciever;
        std::string text;

};

int main(){
    std::unique_ptr<Document> reportPrototype = std::make_unique<Report>("The Report","The content of report");
    std::unique_ptr<Document> letterPrototype = std::make_unique<Letter>("Ivitation","Anna","We are inviting you to the event");

    auto clonedReport = reportPrototype->clone();
    clonedReport ->setTitle("Cloned report");
    auto clonedLetter = reportPrototype->clone();
    clonedLetter->setTitle("Cloned letter");
    reportPrototype->show();
    clonedReport->show();
    
    letterPrototype->show();
    clonedLetter->show();

    return 0;

}