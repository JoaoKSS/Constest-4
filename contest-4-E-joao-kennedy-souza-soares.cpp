#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    const double PI = acos(-1.0);

    // Converte os ângulos de graus para radianos.
    double angle_108_rad = 108.0 * PI / 180.0;
    double angle_63_rad = 63.0 * PI / 180.0;
    
    // Calcula o fator de multiplicação constante.
    double factor = sin(angle_108_rad) / sin(angle_63_rad);

    double pentagon_side;

    while (cin >> pentagon_side) {
        // Calcula o lado do quadrado.
        double square_side = pentagon_side * factor;

        cout << fixed << setprecision(10) << square_side << endl;
    }

    return 0;
}