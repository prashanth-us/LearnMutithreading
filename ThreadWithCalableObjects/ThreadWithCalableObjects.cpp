#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

class App
{
    int count = 0;
    std::mutex mtx;

public:
    void operator()()
    {
        for (size_t i = 0; i < 1E6; i++)
        {
            std::unique_lock<std::mutex> guard(mtx);
            ++count;
        }
    }
    int getCount()
    {
        return count;
    }
};

int main()
{
    App app;
    std::thread t1(std::ref(app));
    std::thread t2(std::ref(app));

    t1.join();
    t2.join();
    std::cout << "count: " << app.getCount() << std::endl;

    return 0;
}