#define DEBUG_FLAG

#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <ios>
#include "array_calculator.h"

using namespace std;
default_random_engine engine(12);
uniform_int_distribution<> dist(10, 99);

vector<vector<double>> equations_generator(int size);

int main() {
    // vector<vector<double>> array1 = {{19, 17, 20, 19, 3,  23, 16, 8,  7},
    //                                  {14, 9,  5,  15, 4,  13, 5,  23, 8},
    //                                  {5,  16, 3,  14, 22, 20, 15, 9,  9},
    //                                  {10, 13, 3,  8,  18, 24, 12, 3,  18},
    //                                  {12, 13, 19, 10, 12, 5,  10, 17, 15},
    //                                  {17, 23, 18, 23, 21, 17, 25, 8,  23},
    //                                  {4,  4,  25, 9,  9,  7,  11, 9,  6},
    //                                  {7,  21, 24, 15, 3,  21, 7,  11, 6},
    //                                  {23, 19, 23, 25, 9,  19, 5,  11, 8}};
    // vector<double> array2 = {1399, 944, 1105, 1054, 1129, 1763, 847, 1212, 1546};

    auto random_array = equations_generator(13);

    //for (int i = 0; i < array1.size(); ++i) {
    //    auto variable = 'a';
    //    if (random_array[i][0] > 0) {
    //        cout << ' ';
    //    }
    //    for (int j = 0; j < array1[0].size(); ++j) {
    //        cout << right << setw(2) << array1[i][j] << variable++;
    //        if (j + 1 != array1[0].size()) {
    //            if (array1[i][j + 1] > 0) {
    //                cout << '+';
    //            }
    //        }
    //    }
    //    cout << '=' << array2[i] << endl;
    //}
    //for (int i = 0; i < array1.size(); ++i) {
    //    array1[i].push_back(array2[i]);
    //}
    //auto variable = 'a';
    //for (const auto &i: Sweep_array(array1)) {
    //    cout << variable++ << ": ";
    //    cout << i.back() << ' ';
    //
    //    cout << endl;
    //}

    auto variable = 'a';
    for (const auto &i: Sweep_array(random_array)) {
        cout << variable++ << ": " << i.back() << endl;
    }

    return 0;
}

vector<vector<double>> equations_generator(int size) {
    vector<vector<double>> return_array;
    vector<int> solution;
    cout << "assumed answer: ";
    for (int i = 0; i < size; ++i) {
        solution.push_back(dist(engine));
        cout << solution.back() << ' ';
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