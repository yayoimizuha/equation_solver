#include <iostream>
#include <vector>
using namespace std;

#include "array_calculator.h"

int main() {
    vector<vector<double>> array1 = {{3,  1, -1},
                                     {-1, 2, 2},
                                     {2,  1, 5}};
    vector<double> array2 = {5, 12, 27};

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
