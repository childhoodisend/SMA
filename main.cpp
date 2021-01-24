//
// Created by DSS on 22.01.2021.
//

/*
 * Реализовать функцию, реализующую алгоритм простого скользящего среднего
*/

#include <iostream>

#include <cstdlib>
#include <ctime>

#include <deque>
#include <string>

#include <fstream>

using namespace std;


template<typename T>
double TRand(T fMin, T fMax)
{
    T f = (T)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

template<typename price_type, typename sum_type>
class SMA{
public:
    ~SMA(){
        fout.close();
        prices.clear();
    };
    SMA() = delete;

    explicit SMA(uint16_t _window, price_type _min_price, price_type _max_price){
        window = _window;
        min_price = _min_price;
        max_price = _max_price;

        for(size_t i = 0; i < _window; ++i)
            prices.push_back(TRand<price_type>(min_price, max_price));

        for(size_t i = 0; i < _window; ++i)
            sum+=prices[i];

        price_type _p = sum/window;

        fout.open("data.txt");
        fout.clear();
        fout << _p << endl;
    }

    void calculate_sma();


public:
    deque<price_type> prices = {};          // цены(значения) исходной функции за установленный период window
    price_type _p = 0;                      // переменная хранит последнее значение sum/window
    price_type min_price = 0, max_price = 0;// диапазон, в котором генерируем цены
    sum_type sum = 0;                       // храним сумму p[i] + ... + p[i-n+1]
    uint16_t window = 0;                    // длина окна
    ofstream fout;
};



template<typename price_type, typename sum_type>
void SMA<price_type, sum_type>::calculate_sma() {

    if(window > prices.size()){cerr << "Error" << endl; return;}

    for(size_t i = 0; i < 1e6 - 1; ++i){

        price_type last_price = prices.front();
        prices.pop_front();
        prices.push_back(TRand<price_type >(min_price, max_price));
        sum -= last_price;
        sum += prices.back();
        _p = sum/window;

        fout << _p << endl;
    }

}


int main(){
    srand( time( NULL ) );
    SMA<double, double> sma(4, 0.0, 20000.0);
    sma.calculate_sma();

    return 0;
}