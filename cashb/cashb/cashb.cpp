/*
15.6. Касса (5)
Написать программу для игры касса, рассмотренной в настоящем разделе.
Ввод из файла INPUT.TXT. В единственной строке находится количество монет N (N ≤ 200).
Вывод в файл OUTPUT.TXT. Вывести 1, если при правильной игре выигрывает первый игрок, либо 2 – если выигрывает второй.

Москвичев А.Е. ПС-22
Visual Studio 2022
*/

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

const int MAX_N = 200;

int main() {
    ifstream fin("INPUT.TXT");
    ofstream fout("OUTPUT.TXT");

    int N;
    fin >> N;

    // S[K][M]
    int maxM = N + 1;
    vector<vector<int>> S(N + 1, vector<int>(maxM + 1, 0));

    // K <= 2M можно забрать всё
    for (int K = 0; K <= N; ++K) {
        for (int M = 1; M <= maxM; ++M) {
            if (K <= 2 * M) {
                S[K][M] = K;
            }
        }
    }

    for (int K = 3; K <= N; ++K) {
        for (int M = 1; M <= maxM; ++M) {
            if (K <= 2 * M) continue;
            bool losingPosition = true;
            for (int L = 1; L <= 2 * M; ++L) {
                if (K - L >= 0 && S[K - L][L] == 0) {
                    S[K][M] = L;
                    losingPosition = false;
                    break;
                }
            }
            if (losingPosition) {
                S[K][M] = 0;
            }
        }
    }

    if (S[N][1] > 0) {
        fout << 1 << endl;
    }
    else {
        fout << 2 << endl;
    }

    return 0;
}
