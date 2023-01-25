#include <random>
#include <iomanip>
#include "array_calculator.h"

#define DEBUG_FLAG

vector<vector<double>> equations_generator(int size);

vector<double> jacobi(vector<vector<double>> a, vector<double> b, size_t limit);

int main() {
    auto equation = equations_generator(3);
    for (auto &row: equation) {
        for (auto &cell: row) {
            cout << cell << ' ';
        }
        cout << endl;
    }
    vector<vector<double>> array;
    vector<double> solution;
    for (auto &i: equation) {
        array.emplace_back();
        for (auto j = 0; j < i.size() - 1; ++j) {
            array.back().push_back(i.at(j));
        }
        solution.push_back(i.back());
    }
    auto ans = jacobi(array, solution, 50);
    for (auto &item: ans) {
        cout << item << '\t';
    }
    cout << endl;
    return 0;
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

vector<double> jacobi(vector<vector<double>> a, vector<double> b, size_t limit) {
    vector<double> c(b.size(), 20);
    for (int n = 0; n < limit; ++n) {
        vector<double> s(b.size());
        double e = 0;
        for (int i = 0; i < a.size(); ++i) {
            s.at(i) = b.at(i);
            for (int j = 0; j < a.at(i).size(); j++) {
                if (j != i) {
                    s.at(i) -= a.at(i).at(j) * c.at(j);
                }
            }
            s.at(i) /= a.at(i).at(i);
            e += fabs(s.at(i) - c.at(i));
        }
        for (int i = 0; i < c.size(); ++i) {
            c.at(i) = s.at(i);
        }
        for (auto &item: c) {
            cout << setw(8) << fixed << setprecision(7) << item << '\t';
        }
        cout << endl;
        if (e < 1e-6)return c;
    }
    cout << "収束せず" << endl;
    return c;
}