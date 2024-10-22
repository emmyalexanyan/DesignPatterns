#include <iostream>
#include <memory>
#include <string>

class IFileReader{
    public:
        virtual ~IFileReader() = default;
        virtual void readfile() = 0;
        virtual void displayContent() = 0;

};

class CSVFileReader{
    public:
        void loadCSVFile(){
            std::cout<<"CSV file loaded"<<std::endl;

        }
        void  showCSVContent(){
            std::cout<<"Display CSV"<<std::endl;
        }
};

class JSONFileReader{
    public:
        void loadJSONFile()
        {
            std::cout<<"JSON file loaded"<<std::endl;
        }
        void showJSONContent(){
            std::cout<<"Display JSON"<<std::endl;
        }

};

class CSVFileAdapter : public IFileReader{
    public:
        CSVFileAdapter(){
           CSVReader = std::make_unique<CSVFileReader>();
        }
        void readfile() override{
            CSVReader->loadCSVFile();
        }
        void displayContent() override{
            CSVReader->showCSVContent();
        }
        
    private:
        std::unique_ptr<CSVFileReader> CSVReader;

};

class JSONFileAdapter : public IFileReader{
    public:
        JSONFileAdapter(){
           JSONReader = std::make_unique<JSONFileReader>();
        }
        void readfile() override{
            JSONReader->loadJSONFile();
        }
        void displayContent() override{
            JSONReader->showJSONContent();
        }
        
    private:
        std::unique_ptr<JSONFileReader> JSONReader;

};

class  FileReaderClient{
    public:
        void setFileReader(IFileReader* reader){
            fileReader = reader;
        }
        void load_display(){
            fileReader->readfile();
            fileReader->displayContent();
        }
    private:
        IFileReader* fileReader;
};

int main(){
    FileReaderClient client;
    CSVFileAdapter csvAdapter;
    client.setFileReader(&csvAdapter);
    client.load_display();
    JSONFileAdapter jsonAdapter;
    client.setFileReader(&jsonAdapter);
    client.load_display();

    return 0;
}