typedef unsigned long long index_t;
template<class T> class Solver {
    protected:
        T** arr;
        T h;
        T tau;
        index_t hsize;
        index_t tsize;
    public:
        Solver() = 0;
        ~Solver() = 0;
        void solve() = 0;
};

template<class T, index_t hsize, index_t tsize> class simpleSolver : public Solver<T> {
    private:
        T* elems;
    protected:
        T h;
        T tau;
        T v;
        T** arr;
        T* ns;
        T sigma;
        ~simpleSolver();
    public:
        simpleSolver(T h, T tau, T (*init) (T, T), T v);
        void solve();
        T** getSolved();
        T* getConcentrations();
};


