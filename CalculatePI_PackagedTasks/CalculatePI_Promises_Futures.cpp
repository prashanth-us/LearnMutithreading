
#include <iostream>
#include <cmath>
#include <iomanip>
#include <thread>
#include <future>

using namespace std;

double calculate_pi(int terms)
{
    double sum = 0.0;
    if (terms < 1)
    {
        throw runtime_error("terms cannot be less than 1 ");
    }
    for (int i = 0; i < terms; i++)
    {
        int sign = pow(-1, i);
        double term = 1.0 / (i * 2 + 1);
        sum += sign * term;
    }
    return sum * 4;
}

int main()
{
    std::packaged_task<double(int)> pt(calculate_pi);
    future<double> futurePt = pt.get_future();

    // thread t1(move(pt), 1E6);
    thread t1(move(pt), 0);
    try
    {
        double returnValue = futurePt.get();
        cout << "PI: " << setprecision(15) << returnValue << endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "ERROR!: " << e.what() << '\n';
    }

    t1.join();
    return 0;
}