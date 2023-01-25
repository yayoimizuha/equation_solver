#include <random>
#include "array_calculator.h"

vector<vector<double>> equations_generator(int size);


int main() {
    auto equation = equations_generator(5);
    vector<double> X_i(equation.size(), 1);
    for (int i = 0; i < equation.size(); ++i) {
        X_i[i] = *equation.at(i).end();
        for (int j = 0; j < equation.at(i).size(); ++j) {
            X_i[i] -= equation.at(i).at(j) * X_i.at(j);
        }
    }
}


default_random_engine engine(43);
uniform_int_distribution<> dist(10, 99);

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
    for (auto &row: return_array) {
        row.resize(size + 1);
        for (int j = 0; j < size; ++j) {
            row[j] = dist(engine);
            row.back() += row[j] * solution[j];
        }
    }
    return return_array;
}