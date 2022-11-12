#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <utility>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
using namespace std;

vector<vector<double>> Transpose_array(const vector<vector<double>> &input_array);

vector<vector<double>> Produce_array(const vector<vector<double>> &arrayA, const vector<vector<double>> &arrayB);

vector<vector<double>> Inverse_array(const vector<vector<double>> &input_array);

vector<vector<double>> Identity_array(size_t size);

vector<vector<double>> Sweep_array(const vector<vector<double>> &input_array);

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

vector<vector<double>> Transpose_array(const vector<vector<double>> &input_array) {
    auto array_length = input_array[0].size();
    for (const vector<double> &row: input_array) {
        if (array_length != row.size()) {
            cout << "Array is not square" << endl;
            return {{-1}};
        }
    }
    vector<vector<double>> return_array;
    return_array.resize(input_array[0].size());
    for (int i = 0; i < input_array.size(); ++i) {
        for (int j = 0; j < input_array[0].size(); ++j) {
            return_array[j].resize(input_array.size());
            return_array[j][i] = input_array[i][j];
        }
    }
    return return_array;
}

vector<vector<double>> Produce_array(const vector<vector<double>> &arrayA, const vector<vector<double>> &arrayB) {
    if (arrayA[0].size() != arrayB.size()) {
        cout << "Can't define array product." << endl;
    }
    vector<double> vecA;
    vecA.resize(arrayB.size());
    vector<double> vecB;
    vecB.resize(arrayB.size());

    double inner_product;
    vector<vector<double>> arrayC;
    arrayC.resize(arrayA.size());
    for (int i = 0; i < arrayA.size(); ++i) {
        arrayC[i].resize(arrayB[0].size());
        for (int j = 0; j < arrayB[0].size(); ++j) {
            inner_product = 0.0;
            for (int k = 0; k < arrayB.size(); ++k) {
                inner_product += arrayA[i][k] * arrayB[k][j];
            }
            arrayC[i][j] = inner_product;
        }
    }
    return arrayC;
}

vector<vector<double>> Inverse_array(const vector<vector<double>> &input_array) {
    auto identity_array = Identity_array(input_array.size());
    vector<vector<double>> sweep_array;
    sweep_array.resize(input_array.size());
    for (auto &row: sweep_array)row.resize(input_array[0].size());
    copy(input_array.begin(), input_array.end(), sweep_array.begin());
    for (int i = 0; i < sweep_array.size(); ++i) {
        sweep_array[i].insert(sweep_array[i].end(), identity_array[i].begin(), identity_array[i].end());
    }
    auto return_array = Sweep_array(sweep_array);
    for (auto &i: return_array) {
        i.erase(i.cbegin(), i.cbegin() + static_cast<long long>(input_array[0].size()));
    }
    return return_array;
}

vector<vector<double>> Identity_array(size_t size) {
    vector<vector<double>> return_array;
    return_array.resize(size);
    for (int i = 0; i < size; ++i) {
        return_array[i].resize(size);
        std::fill(return_array[i].begin(), return_array[i].end(), 0);
        return_array[i][i] = 1;

    }
    return return_array;
}

vector<vector<double>> Sweep_array(const vector<vector<double>> &input_array) {
    vector<vector<double>> return_array(input_array.size());
    for (int i = 0; i < input_array.size(); ++i) {
        return_array[i].resize(input_array[i].size());
        copy(input_array[i].begin(), input_array[i].end(), return_array[i].begin());
    }
    for (int i = 0; i < return_array.size(); ++i) {
        vector<pair<double, int>> swap_array;
        for (int j = i; j < return_array.size(); ++j) {
            swap_array.emplace_back(abs(return_array[i][j]), i);
        }
        auto max_el = *max_element(swap_array.begin(), swap_array.end());
        if (max_el.first < 1e-7) {
            cout << "cannot divide" << endl;
            exit(-1);
        }
        if (max_el.second != i) {
            return_array[i].swap(return_array[max_el.second]);
        }

        auto mag = 1.0 / return_array[i][i];
        for (double &j: return_array[i]) {
            j *= mag;
        }
        for (int j = 0; j < return_array.size(); ++j) {
            if (j == i)continue;
            auto a = -return_array[j][i];
            for (int k = 0; k < return_array[0].size(); ++k) {
                return_array[j][k] += return_array[i][k] * a;
            }
        }
    }
    for (auto &i: return_array) {
        for (auto &j: i) {
            if (abs(j) < 1e-20)j = 0;
        }
    }
    return return_array;
}

#pragma clang diagnostic pop