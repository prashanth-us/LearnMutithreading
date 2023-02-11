#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

int main()
{
    int count = 0;
    const int INTERATIONS = 1E6;
    std::mutex mtx;
    auto func = [&]()
    {
                       for (size_t i = 0; i < INTERATIONS; i++)
                       {
                           mtx.lock();
                           /* code */
                           ++count;
                           mtx.unlock();
                       } };

    std::thread t1(func);
    std::thread t2(func);

    t1.join();
    t2.join();

    std::cout << "count: " << count << std::endl;
    return 0;
}