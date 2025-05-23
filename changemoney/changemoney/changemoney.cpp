/*
Требуется разменять заданную сумму денег минимальным количеством монет.
Ввод. Первая строка файла INPUT.TXT содержит сумму денег L (1 ≤ L ≤ 20000) и количество типов монет N (1 ≤ N ≤ 30). 
Вторая строка содержит N значений Ci через пробел: стоимости типов монет (1 ≤ Ci ≤ L).

Вывод. В первой строке выводится количество типов монет K, необходимое для размена, и общее минимальное количество монет M. 
В следующих K строках выводятся через пробел по 2 числа: стоимость монеты и количество экземпляров данной монеты. 
Эти K строк должны выводится в порядке убывания стоимости монет. Если имеется несколько вариантов решения, достаточно вывести любой из них. 
Если указанную сумму разменять невозможно, то выходной файл должен содержать No.

Москвичев А.Е. ПС-22
Visual Studio 2022
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    ifstream in("INPUT.TXT");
    ofstream out("OUTPUT.TXT");

    int L, N;
    in >> L >> N;
    vector<int> C(N);
    for (int i = 0; i < N; ++i) {
        in >> C[i];
    }

    vector<int> dp(L + 1, INT_MAX);
    vector<vector<int>> count(L + 1, vector<int>(N, 0));

    dp[0] = 0;
    for (int i = 1; i <= L; ++i) {
        for (int j = 0; j < N; ++j) {
            if (C[j] <= i && dp[i - C[j]] != INT_MAX) {
                if (dp[i - C[j]] + 1 < dp[i]) {
                    dp[i] = dp[i - C[j]] + 1;
                    count[i] = count[i - C[j]];
                    count[i][j]++;
                }
            }
        }
    }

    if (dp[L] == INT_MAX) {
        out << "No" << endl;
    }
    else {
        int K = 0;
        for (int j = 0; j < N; ++j) {
            if (count[L][j] > 0) K++;
        }

        out << K << " " << dp[L] << endl;

        vector<pair<int, int>> result;
        for (int j = 0; j < N; ++j) {
            if (count[L][j] > 0) {
                result.emplace_back(C[j], count[L][j]);
            }
        }
        sort(result.rbegin(), result.rend());
        for (const auto& p : result) {
            out << p.first << " " << p.second << endl;
        }
    }

    return 0;
}