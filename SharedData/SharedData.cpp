#include <iostream>
#include <thread>
#include <chrono>

int main()
{
    int count = 0;
    const int INTERATIONS = 1E6;
    std::thread t1([&count]()
                   {
                       for (size_t i = 0; i < INTERATIONS; i++)
                       {
                           /* code */
                           ++count;
                       } });
    std::thread t2([&count]()
                   {
                       for (size_t i = 0; i < INTERATIONS; i++)
                       {
                           /* code */
                           ++count;
                       } });
    t1.join();
    t2.join();

    std::cout << "count: " << count << std::endl;
    return 0;
}