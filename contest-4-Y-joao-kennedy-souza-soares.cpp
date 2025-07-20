#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;

struct Point {
    double x, y;
};

vector<Point> P, CH;

bool cmp(const Point& a, const Point& b) {
    if (a.x != b.x)
        return a.x < b.x;
    return a.y < b.y;
}

double cross(const Point& o, const Point& a, const Point& b) {
    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

void monotoneChain(int n) {
    sort(P.begin(), P.end(), cmp);
    CH.clear();
    int m = 0;

    vector<Point> lower, upper;

    for (int i = 0; i < n; i++) {
        while (lower.size() >= 2 && cross(lower[lower.size()-2], lower[lower.size()-1], P[i]) >= 0)
            lower.pop_back();
        lower.push_back(P[i]);
    }

    for (int i = n - 1; i >= 0; i--) {
        while (upper.size() >= 2 && cross(upper[upper.size()-2], upper[upper.size()-1], P[i]) >= 0)
            upper.pop_back();
        upper.push_back(P[i]);
    }

    CH = lower;
    CH.insert(CH.end(), upper.begin() + 1, upper.end() - 1);
    CH.push_back(CH.front()); 

    double length = 0.0;
    cout << fixed << setprecision(1);

    for (size_t i = 0; i < CH.size(); i++) {
        if (i > 0)
            cout << "-";
        cout << "(" << CH[i].x << "," << CH[i].y << ")";
        if (i > 0) {
            double dx = CH[i].x - CH[i - 1].x;
            double dy = CH[i].y - CH[i - 1].y;
            length += sqrt(dx * dx + dy * dy);
        }
    }
    cout << endl;
    cout << fixed << setprecision(2);
    cout << "Perimeter length = " << length << endl;
}

int main() {
    int n, region = 0;
    while (cin >> n && n) {
        P.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> P[i].x >> P[i].y;
        }
        if (region > 0)
            cout << endl;
        cout << "Region #" << ++region << ":" << endl;
        monotoneChain(n);
    }
    return 0;
}
