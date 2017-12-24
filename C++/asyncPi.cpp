// Compile with the flags "-O3 -std=c++11"
// might need -pthread

#include <iostream>
#include <future>
#include <random>
#include <chrono>

using namespace std;

bool monteCarloPi(double x, double y)
{
    if (x*x + y*y < 1.0)
        return true;

    else return false;
}

long int piThread(long int reps)
{
    long int count = 0;

    unsigned int seed = (unsigned int)chrono::system_clock::now().time_since_epoch().count();
    default_random_engine engine(seed);
    uniform_real_distribution<double> rand(0, 1);

    for (long int i = 0; i < reps; i++)
    {
        if (monteCarloPi(rand(engine), rand(engine)))
            count++;
    }

    return count;
}

int main (int argc, char** argv)
{
    auto cores = thread::hardware_concurrency();
    cout << "cores: " << cores << endl;

    long int samples = 0;

    if (argc > 1)
        samples = atoll(argv[1]);

    cout << "samples: " << samples << endl;

    vector<future<long int>> results;

    auto start = chrono::steady_clock::now();

    for (unsigned i = 0; i < cores; i++)
        results.push_back(async(launch::async, piThread, samples/cores));

    long int total = 0;
    for (auto& result: results)
        total += result.get();

    double pi = ((double)total / double(samples)) * 4.0;

    auto duration = chrono::duration<double, milli>(chrono::steady_clock::now() - start);

    cout << "pi: " << pi << endl;
    cout << "runtime: " << duration.count() / 1000 << "s" << endl;
}
