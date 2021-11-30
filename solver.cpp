#include "solver.hpp"

template<class T, index_t hsize, index_t tsize>
simpleSolver<T, hsize, tsize>::simpleSolver(T m_h, T m_tau, T (*init) (T, T), T m_v) :
    h(m_h),
    tau(m_tau),
    v(m_v),
    sigma(m_tau / m_h * m_v)
{
   this -> elems = new T[hsize * tsize];
   this -> arr = reinterpret_cast<T(*)[hsize]>(elems);

   for (index_t i = 1; i < hsize - 1; ++i) {
       arr[0][i] = init(0, h * i);
   }
   if (v > 0) {
       arr[0][0] = 0;
       arr[0][hsize - 1] = init(0, h * (hsize - 1));
   }
   else {
       arr[0][hsize - 1] = 0;
       arr[0][0] = init(0, 0);
   }
}

template<class T, index_t hsize, index_t tsize>
void simpleSolver<T, hsize, tsize>::solve()
{
    if (this -> v < 0) {
        for (index_t i = 1; i < tsize; ++i) {
            for (index_t j = 0; j < hsize - 1; ++j) {
                arr[i][j] = -sigma * (arr[i - 1][j + 1] - arr[i - 1][j]) + arr[i - 1][j];
            }
        }
    } else {
        for (index_t i = 1; i < tsize; ++i) {
            for (index_t j = 0; j < hsize - 1; ++j) {
                arr[i][j] = -sigma * (arr[i - 1][j + 1] - arr[i - 1][j]) + arr[i - 1][j];
            }
        }
    }
}

    template<class T, index_t hsize, index_t tsize>
simpleSolver<T, hsize, tsize>::~simpleSolver()
{
    delete[] this -> elems;
}

    template<class T, index_t hsize, index_t tsize>
T** simpleSolver<T, hsize, tsize>::getSolved()
{
    return arr;
}
