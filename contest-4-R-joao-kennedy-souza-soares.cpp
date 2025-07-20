#include <bits/stdc++.h>
using namespace std;

struct point {
    int x, y;
    point(int _x = 0, int _y = 0): x(_x), y(_y) {}
    bool operator < (const point &other) const {
        return x > other.x;
    }
};

double dist(const point &p1, const point &p2) {
    return hypot(p1.x - p2.x, p1.y - p2.y);
}

int main(){
    int c;
    cin >> c;
    while (c--) {
        int n;
        cin >> n;

        vector<point> mountain(n);
        for (int i = 0; i < n; i++) {
            cin >> mountain[i].x >> mountain[i].y;
        }

        sort(mountain.begin(), mountain.end());

        int maxY = 0;
        double res = 0.0;
        for (int i = 1; i < n; i++) {
            if (mountain[i].y > maxY) {
                double total = dist(mountain[i], mountain[i - 1]);
                double ratio = double(mountain[i].y - maxY) / (mountain[i].y - mountain[i - 1].y);
                res += total * ratio;
                maxY = mountain[i].y;
            }
        }

        cout << fixed << setprecision(2) << res << endl;
    }

    return 0;
}
