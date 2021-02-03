/* Задача:
 * Реализовать функцию, реализующую алгоритм простого скользящего среднего
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>
#include <string>


using namespace std;

static const size_t SIGNAL_SIZE = 1e6;

template<typename T>
void print(vector<T> &_p){
    for(T i : _p){
        cout << i << endl;
    }
}

template<typename T>
void fill_random(vector<T> &source_signal){
    srand(time(NULL));
    for (size_t i = 0; i < SIGNAL_SIZE; ++i) {
        source_signal[i] = rand();
    }

}
template<typename T>
vector<T> apply_sma_filter(const vector<T> &source_signal, size_t win_len)
{
    if(source_signal.empty())
        throw invalid_argument("source_signal is empty");
    if(source_signal.size() < win_len)
        throw invalid_argument("source_signal.size() < win_len");

    vector<T> _p(SIGNAL_SIZE);
    T sum = 0.0;
    for (size_t i = 0; i < win_len; ++i) {
        sum += source_signal[i];
    }
    _p.push_back(sum / win_len);
    for (size_t i = win_len; i < SIGNAL_SIZE; ++i) {
        sum -= source_signal[i - win_len];
        sum += source_signal[i];
        _p[i - win_len] = T(sum / win_len);
    }
    return _p;
}

void save_results(double time, const string& type) {
    ofstream fout;
    fout.open("results.txt",ios_base::app);
    fout << type << endl;
    fout << time << endl;
    fout << SIGNAL_SIZE/time << endl;
    fout << endl;
}
int main() {

    vector<float> source1(SIGNAL_SIZE);
    fill_random<float>(source1);

    vector<double> source2(SIGNAL_SIZE);
    fill_random<double>(source2);
    //print(source);
    try {
        //float
        time_t start = clock();
        auto answer1 = apply_sma_filter<float>(source1,64);
        time_t end = clock() - start;
        double time = (double)(end)/CLOCKS_PER_SEC;
        save_results(time, "float");

        //double
        start = clock();
        auto answer2 = apply_sma_filter<double>(source2, 64);
        end = clock() - start;
        time = (double)(end)/CLOCKS_PER_SEC;
        save_results(time,  "double");
    }
    catch (invalid_argument &e) {
        cerr << e.what() << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}