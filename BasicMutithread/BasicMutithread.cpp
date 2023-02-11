#include <iostream>
#include <thread>
#include <chrono>

void work()
{
    for (size_t i = 0; i < 10; i++)
    {
        /* code */
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << "loop: " << i << std::endl;
    }
}
int main()
{
    std::thread t1(work);
    std::thread t2(work);
    t1.join();
    t2.join();
    return 0;
}