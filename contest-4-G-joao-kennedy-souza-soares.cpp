#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>

using namespace std;

struct ConstraintPoint {
    double x_pos; 
    double height;
};

int main() {
    const double g = 9.8;
    const double PI = acos(-1.0);

    int n;
    while (cin >> n) {
        vector<ConstraintPoint> points;
        double h, d;
        double total_distance = 0;
        double current_distance = 0;

        for (int i = 0; i < n; ++i) {
            cin >> h >> d;
            
            if (h > 0) {
                // Adiciona o canto superior esquerdo
                points.push_back({current_distance, h});
                // Adiciona o canto superior direito
                points.push_back({current_distance + d, h});
            }
            
            current_distance += d;
        }
        total_distance = current_distance;

        double min_B = 0.0;
        for (const auto& point : points) {
            if (point.x_pos < total_distance) {
                 double b_ratio = point.height / (point.x_pos * (total_distance - point.x_pos));
                if (b_ratio > min_B) {
                    min_B = b_ratio;
                }
            }
        }
        
        // Calcula o ângulo em radianos e converte para graus
        double angle_rad = atan(min_B * total_distance);
        double angle_deg = angle_rad * 180.0 / PI;

        // Calcula a velocidade horizontal e a velocidade total
        double v_x = sqrt(g / (2.0 * min_B));
        double velocity = v_x / cos(angle_rad);

        cout << fixed << setprecision(2) << angle_deg << " " << velocity << endl;
    }

    return 0;
}
