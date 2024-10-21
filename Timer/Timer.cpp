//Singleton
#include <iostream>
#include <memory>
#include <ctime>

class Timer{
    public:
        static std::shared_ptr<Timer> getInstance() {
            if(!instance){
                instance = std::shared_ptr<Timer>(new Timer());
            }
            return instance;
        }

        double elapsedTime(){
            clock_t endTime = clock();
            return (double)(endTime - startTime) / CLOCKS_PER_SEC;
        }
    private:
        Timer(){
            std::cout<<"Timer created\n";
            startTime = clock();
        }

        Timer(const Timer&) = delete;
        Timer& operator=(const Timer&) = delete;

        Timer(Timer&&) = delete;
        Timer& operator=(Timer&&) = delete;

        static std::shared_ptr<Timer> instance;
        clock_t startTime;


};
std::shared_ptr<Timer> Timer::instance = nullptr;

int main(){
    std::shared_ptr<Timer> timer = Timer::getInstance();
    int s = 0;
    for(int i = 0; i < 100; i++){
        s += i;
    }
    std::cout<<"S="<<s<<std::endl;
    std::cout<<"ElapsedTime:"<<timer->elapsedTime()<<"seconds"<<std::endl;
    return 0;
}