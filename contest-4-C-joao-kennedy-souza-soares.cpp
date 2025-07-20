#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

double polygon_area(const vector<double>& x, const vector<double>& y) {
    int n = x.size();
    double a = 0.0;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        a += x[i] * y[j] - x[j] * y[i];
    }
    return 0.5 * fabs(a);
}

int main() {
    const double PI = 2.0 * acos(0.0);

    while (true) {
        int N;
        if (!(cin >> N)) return 0;
        if (N == 0) break;

        double total_volume = 0.0;
        string line;
        getline(cin, line); 

        for (int i = 0; i < N; ++i) {
            do {
                if (!getline(cin, line)) break;
            } while (line.empty());

            stringstream ss(line);
            double Ti;
            ss >> Ti;

            vector<double> coords;
            double v;
            while (ss >> v) {
                coords.push_back(v);
            }

            int m = coords.size();
            int num_points = m / 2 - 1;

            vector<double> x(num_points), y(num_points);
            for (int k = 0; k < num_points; ++k) {
                x[k] = coords[2*k];
                y[k] = coords[2*k + 1];
            }

            double area = polygon_area(x, y);
            total_volume += area * Ti;
        }

        double R, Tcover;
        cin >> R >> Tcover;

        double cover_volume = PI * R * R * Tcover;
        long long count = static_cast<long long>(floor(total_volume / cover_volume));

        cout << count << endl;
    }

    return 0;
}
