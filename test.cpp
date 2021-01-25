#include <cstdlib>
#include <ctime>
#include <fstream>

namespace test {
    template<typename T>
    double TRand(T fMin, T fMax)
    {
        T f = (T)rand() / RAND_MAX;
        return fMin + f * (fMax - fMin);
    }

    template<typename price_type>
    void test(price_type min_price, price_type max_price) {
        srand(time(NULL));

        std::ofstream test("test.txt");
        test.clear();
        for (size_t i = 0; i < 1e6; ++i) {
            test << TRand<price_type>(min_price, max_price) << std::endl;
        }
        test.close();
    }
}