/*
 * Реализовать функцию, реализующую алгоритм простого скользящего среднего
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

        /*---Test section---*/
        fin_test.open("test.txt");
        for (size_t i = 0; i < _window; ++i) {
            price_type cur;
            fin_test >> cur;
            prices.push_back(cur);
        }
        /*~~~Test section~~~*/


//      for(size_t i = 0; i < _window; ++i)
//          prices.push_back(TRand<price_type>(min_price, max_price));

        for (size_t i = 0; i < window; ++i)
            sum += prices[i];

        _p.push_back(sum / window);
    }

    void calculate_sma();

    void save_prices_to_file();

    void save_results_to_file(int clocks, double sec);

private:
    deque<price_type> prices = {};          // цены(значения) исходной функции за установленный период window, храним их c условием FIFO
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
        price_type cur;
        fin_test >> cur;
        prices.push_back(cur);
        /*~~~Test section~~~*/

        //prices.push_back(TRand<price_type >(min_price, max_price));

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

    cout << "window -> 4\n";
    SMA<float, float> sma(4, 0.01, 30.99);
    clock_t start = clock();
    sma.calculate_sma();
    clock_t end = clock() - start;
    sma.save_results_to_file(end, (double) end / CLOCKS_PER_SEC);
    sma.save_prices_to_file();

    cout << "window -> 8\n";
    SMA<float, float> sma1(8, 0.01, 30.99);
    start = clock();
    sma1.calculate_sma();
    end = clock() - start;
    sma1.save_results_to_file(end, (double) end / CLOCKS_PER_SEC);
    sma1.save_prices_to_file();

    cout << "window -> 16\n";
    SMA<float, float> sma2(16, 0.01, 30.99);
    start = clock();
    sma2.calculate_sma();
    end = clock() - start;
    sma2.save_results_to_file(end, (double) end / CLOCKS_PER_SEC);
    sma2.save_prices_to_file();

    cout << "window -> 32\n";
    SMA<float, float> sma3(32, 0.01, 30.99);
    start = clock();
    sma3.calculate_sma();
    end = clock() - start;
    sma3.save_results_to_file(end, (double) end / CLOCKS_PER_SEC);
    sma3.save_prices_to_file();

    cout << "window -> 64\n";
    SMA<float, float> sma4(64, 0.01, 30.99);
    start = clock();
    sma4.calculate_sma();
    end = clock() - start;
    sma4.save_results_to_file(end, (double) end / CLOCKS_PER_SEC);
    sma4.save_prices_to_file();

    cout << "window -> 128\n";
    SMA<float, float> sma5(128, 0.01, 30.99);
    start = clock();
    sma5.calculate_sma();
    end = clock() - start;
    sma5.save_results_to_file(end, (double) end / CLOCKS_PER_SEC);
    sma5.save_prices_to_file();

    cout << "window -> 4\n";
    SMA<double, double> sma6(4, 0.01, 30.99);
    start = clock();
    sma6.calculate_sma();
    end = clock() - start;
    sma6.save_results_to_file(end, (double) end / CLOCKS_PER_SEC);
    sma6.save_prices_to_file();

    cout << "window -> 8\n";
    SMA<double, double> sma7(8, 0.01, 30.99);
    start = clock();
    sma7.calculate_sma();
    end = clock() - start;
    sma7.save_results_to_file(end, (double) end / CLOCKS_PER_SEC);
    sma7.save_prices_to_file();

    cout << "window -> 16\n";
    SMA<double, double> sma8(16, 0.01, 30.99);
    start = clock();
    sma8.calculate_sma();
    end = clock() - start;
    sma8.save_results_to_file(end, (double) end / CLOCKS_PER_SEC);
    sma8.save_prices_to_file();

    cout << "window -> 32\n";
    SMA<double, double> sma9(32, 0.01, 30.99);
    start = clock();
    sma9.calculate_sma();
    end = clock() - start;
    sma9.save_results_to_file(end, (double) end / CLOCKS_PER_SEC);
    sma9.save_prices_to_file();

    cout << "window -> 64\n";
    SMA<double, double> sma10(64, 0.01, 30.99);
    start = clock();
    sma10.calculate_sma();
    end = clock() - start;
    sma10.save_results_to_file(end, (double) end / CLOCKS_PER_SEC);
    sma10.save_prices_to_file();

    cout << "window -> 128\n";
    SMA<double, double> sma11(128, 0.01, 30.99);
    start = clock();
    sma11.calculate_sma();
    end = clock() - start;
    sma11.save_results_to_file(end, (double) end / CLOCKS_PER_SEC);
    sma11.save_prices_to_file();


    return 0;
}