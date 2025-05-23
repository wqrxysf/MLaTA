/*
1.7. Шашки (5)
На шахматном поле расположены N черных и одна белая шашка. Требуется написать программу, которая по заданному расположению шашек определяет, какое максимальное количество шашек может взять белая шашка за один ход. Черная шашка сразу после взятия снимается с доски.
Ввод из файла INPUT.TXT. Задается 8 строк, каждая содержит 8 символов. Символом ‘0’ обозначается пустая клетка, символом ‘1’ положение черной шашки и символом ‘2’ - положение белой шашки.
Вывод в файл OUTPUT.TXT. Вывести единственное число – максимальное количество черных шашек, которых можно взять за один ход.

Москвичев А.Е. ПС-22
Visual Studio 2022
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int N = 8;
const int dx[] = { -1, -1, 1, 1 }; // смещения по строкам (верх-лево, верх-право, низ-лево, низ-право)
const int dy[] = { -1, 1, -1, 1 }; // смещения по столбцам

bool isValid(int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < N;
}

int maxCaptures(vector<vector<char>>& board, int x, int y) {
    int maxTake = 0;

    for (int d = 0; d < 4; d++) {
        int nx = x + dx[d], ny = y + dy[d]; // клетка, которую хотим срубить
        int nnx = x + 2 * dx[d], nny = y + 2 * dy[d]; // клетка, куда в результате упадём

        if (isValid(nx, ny) && isValid(nnx, nny) && board[nx][ny] == '1' && board[nnx][nny] == '0') {
            board[x][y] = '0';
            board[nx][ny] = '0';
            board[nnx][nny] = '2';
            maxTake = max(maxTake, 1 + maxCaptures(board, nnx, nny));
            board[x][y] = '2'; // возвращаем обратно после обратной рекурсии
            board[nx][ny] = '1';
            board[nnx][nny] = '0';
        }
    }

    return maxTake;
}

int main() {
    ifstream fin("INPUT.TXT");
    ofstream fout("OUTPUT.TXT");

    vector<vector<char>> board(N, vector<char>(N));
    int x, y;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fin >> board[i][j];
            if (board[i][j] == '2') {
                x = i;
                y = j;
            }
        }
    }

    fout << maxCaptures(board, x, y) << endl;

    fin.close();
    fout.close();
    cout << "complete!\n";
    return 0;
}
