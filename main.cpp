/* Задача:
 * Реализовать функцию, реализующую алгоритм простого скользящего среднего
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

static const size_t SIGNAL_SIZE = 1e6;
void print(vector<float> &_p){
    for(float i : _p){
        cout << i << endl;
    }
}
void fill_random(vector<float> &source_signal){
    srand(time(NULL));
    for (size_t i = 0; i < SIGNAL_SIZE; ++i) {
        source_signal.push_back(rand());
    }

}

vector<float> apply_sma_filter(const vector<float> &source_signal, size_t win_len)
{
    if(source_signal.empty())
        throw invalid_argument("source_signal is empty");
    if(source_signal.size() < win_len)
        throw invalid_argument("source_signal.size() < win_len");

    vector<float> _p;
    float last_signal = source_signal[0];
    float sum = 0.0;
    for (size_t i = 0; i < win_len; ++i) {
        sum += source_signal[i];
    }
    _p.push_back(sum / win_len);
    for (size_t i = win_len; i < SIGNAL_SIZE; ++i) {
        sum -= last_signal;
        sum += source_signal[i];
        last_signal = source_signal[i];
        _p.push_back(sum / win_len);
    }
    return _p;
}
int main() {

    vector<float> source;
    fill_random(source);
    //print(source);
    try {
        auto answer = apply_sma_filter(source,2);
        //print(answer);
    }
    catch (invalid_argument &e) {
        cerr << e.what() << endl;
        return EXIT_FAILURE;
    }
    return 0;
}