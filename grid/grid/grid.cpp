/*
* 11.8. За решеткой (6)
Два бегемота, Вася и Эдик, живут в зоопарке. Каждый живет в отдельной прямоугольной клетке, три стены которой каменные, а четвертая образована решеткой. 
Через решетки бегемоты видят друг друга. Однажды ночью обоих мучила бессонница, и Вася предложил сыграть в морской бой, чтобы скоротать время. 
Чтобы сообщать о своем ходе как можно тише (ночь все-таки, все остальные звери спят), Эдик предложил найти такие положения около решеток, расстояние между которыми минимально.
Ввод
из файла INPUT.TXT. В единственной строке задаются через пробел восемь чисел: сначала описание первой решетки, затем второй. 
Каждая решетка задается координатами концов (x1, y1, x2, y2). Все числа целые, по модулю не больше 10000.
Вывод
в файл OUTPUT.TXT. В единственной строке вывести минимальное расстояние, которое может быть между Васей и Эдиком, если каждый будет стоять около своей решетки. 
Расстояние должно быть выведено с тремя знаками после запятой.

Москвичев А.Е. ПС-22 
Visual Studio 2022
*/

#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>

using namespace std;

double distance(double x1, double y1, double x2, double y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

double point_to_segment_distance(double px, double py, double x1, double y1, double x2, double y2) {
    double dx = x2 - x1, dy = y2 - y1; // направление вектора
    double t = ((px - x1) * dx + (py - y1) * dy) / (dx * dx + dy * dy); // ap*ab/ab^2
    t = std::max(0.0, std::min(1.0, t)); 
    return distance(px, py, x1 + t * dx, y1 + t * dy);
}

double segments_distance(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) {
    return min({
        point_to_segment_distance(x1, y1, x3, y3, x4, y4),
        point_to_segment_distance(x2, y2, x3, y3, x4, y4),
        point_to_segment_distance(x3, y3, x1, y1, x2, y2),
        point_to_segment_distance(x4, y4, x1, y1, x2, y2)
        });
}

int main() {
    ifstream input("INPUT.TXT"); 
    ofstream output("OUTPUT.TXT");
    double x1, y1, x2, y2, x3, y3, x4, y4;
    input >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;

    double min_dist = segments_distance(x1, y1, x2, y2, x3, y3, x4, y4);
    output.precision(3);
    output << fixed << min_dist << endl;

    return 0;
}
