#include <iostream>
#include <vector>
#include "array_calculator.h"

using namespace std;

int main() {
    vector<vector<double>> array1 = {{4,  1,  -3, 5},
                                     {2,  3,  1,  2},
                                     {5,  -4, -2, 1},
                                     {-2, 2,  8,  2}};
    vector<double> array2 = {18, 21, 5, 16};

    for (int i = 0; i < array1.size(); ++i) {
        auto variable = 'a';
        if (array1[i][0] > 0) {
            cout << ' ';
        }
        for (int j = 0; j < array1[0].size(); ++j) {
            cout << array1[i][j] << variable++;
            if (j + 1 != array1[0].size()) {
                if (array1[i][j + 1] > 0) {
                    cout << '+';
                }
            }
        }
        cout << '=' << array2[i] << endl;
    }
    for (int i = 0; i < array1.size(); ++i) {
        array1[i].push_back(array2[i]);
    }
    auto variable = 'a';
    for (const auto &i: Sweep_array(array1)) {
        cout << variable++ << ": ";
        cout << i.back() << ' ';

        cout << endl;
    }
    return 0;
}
