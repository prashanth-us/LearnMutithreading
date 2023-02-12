#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

void work(int &count, std::mutex &mtx)
{
    for (size_t i = 0; i < 1E6; i++)
    {
        mtx.lock();
        /* code */
        ++count;
        mtx.unlock();
    }
}
int main()
{
    int count = 0;
    std::mutex mtx;

    std::thread t1(work, std::ref(count), std::ref(mtx));
    std::thread t2(work, std::ref(count), std::ref(mtx));

    t1.join();
    t2.join();

    std::cout << "count: " << count << std::endl;
    return 0;
}