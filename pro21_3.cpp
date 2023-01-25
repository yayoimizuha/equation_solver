#define DEBUG_FLAG

#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <ios>
#include <chrono>
#include "array_calculator.h"

using namespace chrono;
using namespace std;
default_random_engine engine(43);
uniform_int_distribution<> dist(10, 99);

vector<vector<double>> equations_generator(int size);

int main() {
    auto start_time = system_clock::now();
    auto random_array = equations_generator(13);
    auto variable = 'a';
    for (const auto &i: Sweep_array(random_array)) {
        cout << variable++ << ": " << i.back() << endl;
    }
    cout << duration_cast<milliseconds>(system_clock::now() - start_time).count() << endl;
    return 0;
}

vector<vector<double>> equations_generator(int size) {
    vector<vector<double>> return_array;
    vector<int> solution;
#ifdef DEBUG_FLAG
    cout << "assumed answer: ";
#endif
    for (int i = 0; i < size; ++i) {
        solution.push_back(dist(engine));
#ifdef DEBUG_FLAG
        cout << solution.back() << ' ';
#endif
    }
    cout << endl;
    return_array.resize(size);
    for (int i = 0; i < size; ++i) {
        return_array[i].resize(size + 1);
        for (int j = 0; j < size; ++j) {
            return_array[i][j] = dist(engine);
            return_array[i].back() += return_array[i][j] * solution[j];
        }
    }
    return return_array;
}