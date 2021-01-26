/* Задача:
 * Реализовать функцию, реализующую алгоритм простого скользящего среднего
*/

/*
 * При работе с тестовыми данными -- закоментировать Work Section и раскоментировать Test Section.
 * Для генерации рандомных данных для каждого объекта -- ноборот,
 * закоментировать Test Section и раскоментировать  Work Section.
 */
#include <iostream>

#include <cstdlib>
#include <ctime>

#include <vector>
#include <deque>
#include <string>

#include "test.cpp"

using namespace std;


template<typename T>
double TRand(T fMin, T fMax) {
    T f = (T) rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

template<typename price_type, typename sum_type>
class SMA {
public:
    ~SMA() = default;

    SMA() = delete;

    explicit SMA(uint8_t _window, price_type _min_price, price_type _max_price) {
        window = _window;
        min_price = _min_price;
        max_price = _max_price;
        cout << "window -> " << window << endl;
        /*---Test section---*/
//        fin_test.open("test.txt");
//        for (size_t i = 0; i < _window; ++i) {
//            price_type cur;
//            fin_test >> cur;
//            prices.push_back(cur);
//        }
        /*~~~Test section~~~*/

        /*---work section---*/
        for(size_t i = 0; i < _window; ++i)
          prices.push_back(TRand<price_type>(min_price, max_price));
        /*~~~work section~~~*/

        for (size_t i = 0; i < window; ++i)
            sum += prices[i];

        _p.push_back(sum / window);
    }

    void calculate_sma();

    void save_prices_to_file();

    void save_results_to_file(int clocks, double sec);

private:
    deque<price_type> prices = {};          // значения исходной функции за установленный период window, храним их c условием FIFO
    vector<price_type> _p = {};             // храним значения sum/window на каждой итерации
    price_type min_price = 0, max_price = 0;// диапазон, в котором генерируем цены
    sum_type sum = 0;                       // храним сумму prices[i] + ... + prices[i + n - 1]
    uint16_t window = 0;                    // длина окна
    ofstream fout, fout_price;
    ifstream fin_test;
};


template<typename price_type, typename sum_type>
void SMA<price_type, sum_type>::calculate_sma() {
    if (window > prices.size()) {
        cerr << "Error" << endl;
        return;
    }


    for (size_t i = 0; i < 1e6 - 1; ++i) {
        price_type last_price = prices.front();
        prices.pop_front();

        /*---Test section---*/
//        price_type cur;
//        fin_test >> cur;
//        prices.push_back(cur);
        /*~~~Test section~~~*/

        /*---work section---*/
        prices.push_back(TRand<price_type >(min_price, max_price));
        /*~~~work section~~~*/

        sum -= last_price;
        sum += prices.back();
        _p.push_back(sum / window);
    }
}

template<typename price_type, typename sum_type>
void SMA<price_type, sum_type>::save_prices_to_file() {
    fout_price.open("data" + to_string(window) + typeid(price_type).name() + ".txt");
    fout_price.clear();
    for (auto price: _p) {
        fout_price << price << endl;
    }
    fout_price.close();
}

template<typename price_type, typename sum_type>
void SMA<price_type, sum_type>::save_results_to_file(int clocks, double sec) {
    fout.open("results.txt", ios::app);
    fout << typeid(price_type).name() << " "
         << typeid(sum_type).name() << " "
         << window << " "
         << clocks << " "
         << sec << endl;
    fout.close();
}


int main() {
    srand(time(NULL));
    //test::test<double>(0.01,29.99); // сгенерировать новые данные для теста

    SMA<float, float> sma(4, 0.01, 30.99);

    clock_t start = clock();
    sma.calculate_sma();
    clock_t end = clock() - start;
    sma.save_results_to_file(end, (double) end / CLOCKS_PER_SEC);

    //sma.save_prices_to_file();

    return 0;
}