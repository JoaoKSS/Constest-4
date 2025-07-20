#include <iostream>
#include <iomanip>
#include <cmath>
#include <map>
#include <string>
#include <vector>
using namespace std;

const double PI = acos(-1);

map<string, double> createDirectionMap() {
    vector<string> directions = {
        "N", "NbE", "NNE", "NEbN", "NE", "NEbE", "ENE", "EbN",
        "E", "EbS", "ESE", "SEbE", "SE", "SEbS", "SSE", "SbE",
        "S", "SbW", "SSW", "SWbS", "SW", "SWbW", "WSW", "WbS",
        "W", "WbN", "WNW", "NWbW", "NW", "NWbN", "NNW", "NbW"
    };
    map<string, double> dir_map;
    for (int i = 0; i < 32; ++i) {
        dir_map[directions[i]] = i * 11.25;
    }
    return dir_map;
}

int main() {
    map<string, double> direction_map = createDirectionMap();
    cout << fixed << setprecision(2);

    while (true) {
        int n;
        cin >> n;
        if (n == 0) break;

        vector<pair<double, double>> path; 
        double x = 0, y = 0;

        vector<pair<string, double>> steps;
        for (int i = 0; i < n; ++i) {
            string dir;
            double paces;
            cin >> dir >> paces;
            steps.push_back({dir, paces});
        }

        double declination;
        cin >> declination;

        double tx = 0, ty = 0;
        for (auto& [dir, paces] : steps) {
            double angle = direction_map[dir];
            angle += declination;  
            angle = fmod(angle + 360, 360); 
            double rad = angle * PI / 180.0;
            tx += paces * sin(rad);
            ty += paces * cos(rad);
        }

        x = y = 0;
        double minDist = hypot(tx, ty); 
        for (auto& [dir, paces] : steps) {
            double angle = direction_map[dir];
            double rad = angle * PI / 180.0;
            double dx = paces * sin(rad);
            double dy = paces * cos(rad);

            double px = x, py = y;
            double qx = x + dx, qy = y + dy;

            double vx = qx - px;
            double vy = qy - py;
            double wx = tx - px;
            double wy = ty - py;

            double proj = (vx * wx + vy * wy) / (vx * vx + vy * vy);
            proj = max(0.0, min(1.0, proj)); 

            double cx = px + proj * vx;
            double cy = py + proj * vy;

            double dist = hypot(cx - tx, cy - ty);
            minDist = min(minDist, dist);

            x += dx;
            y += dy;
        }

        cout << minDist << endl;
    }

    return 0;
}
