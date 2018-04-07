#include <pybind11/pybind11.h>

#include <iostream>
#include <future>
#include <random>
#include <chrono>

using namespace std;

bool inUnitCircle(double x, double y)
{
    if (x*x + y*y < 1.0)
        return true;

    else return false;
}

double monteCarloPi(long int reps)
{
    long int count = 0;

    unsigned int seed = (unsigned int)chrono::system_clock::now().time_since_epoch().count();
    default_random_engine engine(seed);
    uniform_real_distribution<double> rand(0, 1);

    for (long int i = 0; i < reps; i++)
    {
        if (inUnitCircle(rand(engine), rand(engine)))
            count++;
    }

    return (double(count) / double(reps)) * 4.0;
}

PYBIND11_MODULE(MonteCarloPi, m) {
    m.doc() = "MonteCarloPi pybind11 plugin"; // optional module docstring

    m.def("pi", &monteCarloPi, "Estimates PI using the MonteCarlo method the input number of times");
}