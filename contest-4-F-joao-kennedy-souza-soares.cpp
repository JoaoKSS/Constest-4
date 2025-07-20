#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    const double PI = 3.141592653589793;

    double x1, y1, x2, y2, x3, y3;

    while (cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3) {
        double a = sqrt(pow(x2 - x3, 2) + pow(y2 - y3, 2));
        double b = sqrt(pow(x1 - x3, 2) + pow(y1 - y3, 2));
        double c = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));

        double area = 0.5 * abs(x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2));
        double radius = (a * b * c) / (4.0 * area);
        double circumference = 2.0 * PI * radius;

        cout << fixed << setprecision(2) << circumference << endl;
    }

    return 0;
}