#ifndef SOLVER_HPP
#define SOLVER_HPP
typedef unsigned long long index_t;
template<typename T> class Solver {
    private:
        T* elems;
    protected:
        T** arr;
        T h;
        T tau;
        index_t hsize;
        index_t tsize;
    public:
        void solve();
};

template<typename T, index_t hsize, index_t tsize> class simpleSolver : public Solver<T> {
    private:
        T* elems;
    protected:
        T h;
        T tau;
        T v;
        T (*arr)[hsize];
        T sigma;
    public:
        simpleSolver(T h, T tau, T (*init) (T, T), T v);
        simpleSolver(const simpleSolver<T, hsize, tsize>&);
        simpleSolver<T, hsize, tsize>& operator=(const simpleSolver<T, hsize, tsize>&);
        ~simpleSolver();
        void solve();
        T** getSolved();
        T* getConcentrations();
};

template<typename T, index_t hsize, index_t tsize>
simpleSolver<T, hsize, tsize>::simpleSolver(T m_h, T m_tau, T (*init) (T, T), T m_v) :
    elems(new T[hsize * tsize]),
    h(m_h),
    tau(m_tau),
    v(m_v),
    sigma(m_tau / m_h * m_v)
{
    this -> arr = reinterpret_cast<T(*)[hsize]>(elems);

    for (index_t i = 1; i < hsize - 1; ++i) {
        T x = (T)h * i;
        arr[0][i] = init(x, this -> v);
    }
    if (v > 0) {
        arr[0][0] = 0;
        T x = (T)h * (hsize - 1);
        arr[0][hsize - 1] = init(x, this -> v);
    }
    else {
        arr[0][hsize - 1] = 0;
        arr[0][0] = init(0.0, this -> v);
    }
}

    template<typename T, index_t hsize, index_t tsize>
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

    template<typename T, index_t hsize, index_t tsize>
simpleSolver<T, hsize, tsize>::~simpleSolver()
{
    delete[] this -> elems;
}

    template<typename T, index_t hsize, index_t tsize>
T** simpleSolver<T, hsize, tsize>::getSolved()
{
    return reinterpret_cast<T**>(arr);
}
template<typename T, index_t hsize, index_t tsize>
simpleSolver<T, hsize, tsize>::simpleSolver(const simpleSolver<T, hsize, tsize>& s) :
    h(s.h),
    tau(s.tau),
    v(s.v),
    sigma(v.sigma),
    elems(s.elems),
    arr(s.arr)
{
}
template<typename T, index_t hsize, index_t tsize>
simpleSolver<T, hsize, tsize>& simpleSolver<T, hsize, tsize>::operator=(const simpleSolver<T, hsize, tsize>& s)
{
    this -> h = s.h;
    this -> tau = s.tau;
    this -> v = s.v;
    this -> sigma = s.sigma;
    this -> elems = s.elems;
    this -> arr = s.arr;
}
#endif
