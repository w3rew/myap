#include "solver.hpp"
#include <cmath>
#include <fstream>
#include <iostream>
typedef double double_t_t;

const index_t hsize = 1000;
const index_t tsize = 1000;

const double_t h = 10.0 / hsize;
const double_t tau = 10.0 / tsize;


int main()
{
    std::ofstream of;
    double_t *ns = new double_t[hsize];
    for (index_t i = 0; i < hsize; ++i)
        ns[i] = 0.0;
    simpleSolver<double_t, hsize, tsize> *s;
    auto f = [](double_t x, double_t v){return exp(-x*x - v * v);};
    for (int v = -5; v <= 5; ++v) if (v != 0) {
        s = new simpleSolver<double_t, hsize, tsize> (h, tau, f, v);
        s -> solve();
        double_t (*cur_ns)[hsize] = reinterpret_cast<double_t (*)[hsize]>(s -> getSolved());
        for (index_t i = 0; i < hsize; ++i)
            ns[i] += cur_ns[tsize - 1][i];
        delete s;
    }
    of.open("n.txt", std::ios::out | std::ios::trunc);
    for (index_t i = 0; i < hsize; ++i)
        of << ns[i] << std::endl;

    return 0;
}
