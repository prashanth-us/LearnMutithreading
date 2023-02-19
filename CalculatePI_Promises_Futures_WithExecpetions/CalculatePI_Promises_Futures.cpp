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
    promise<double> prms;
    future<double> ftr = prms.get_future();

    auto do_calculation = [&](int terms)
    {
        try
        {

            auto result = calculate_pi(terms);
            prms.set_value(result);
        }
        catch (const std::exception &e)
        {
            // std::cerr << e.what() << '\n';
            prms.set_exception(current_exception());
        }
    };
    thread t1(do_calculation, 1E6);

    try
    {
        cout << "PI: " << setprecision(15) << ftr.get() << endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    t1.join();
    return 0;
}
