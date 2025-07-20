#include <bits/stdc++.h>
using namespace std;

struct Point {
    double x, y;
};

Point midpoint(const Point &A, const Point &B) {
    return {(A.x + B.x) / 2.0, (A.y + B.y) / 2.0};
}

Point reflectAcrossLine(const Point &P, const Point &A, const Point &B) {
    double vx = B.x - A.x;
    double vy = B.y - A.y;
    double wx = P.x - A.x;
    double wy = P.y - A.y;
    double t = (vx*wx + vy*wy) / (vx*vx + vy*vy); 
    double qx = A.x + t * vx;
    double qy = A.y + t * vy;
    return {2*qx - P.x, 2*qy - P.y};
}

bool almostEqual(double a, double b, double eps = 1e-8) {
    return fabs(a - b) < eps;
}

int main() {
    int n;
    int caseNo = 1;
    while ( (cin >> n) && n != 0 ) {
        vector<Point> poly(n);
        for (int i = 0; i < n; i++) {
            cin >> poly[i].x >> poly[i].y;
        }

        vector<pair<Point,Point>> axes;
        if (n % 2 == 1) {
            int m = n / 2;
            for (int k = 0; k < n; k++) {
                Point A = poly[k];
                Point E1 = poly[(k + m) % n];
                Point E2 = poly[(k + m + 1) % n];
                Point B = midpoint(E1, E2);
                axes.emplace_back(A, B);
            }
        } else {
            int half = n / 2;
            for (int k = 0; k < half; k++) {
                Point A = poly[k];
                Point B = poly[k + half];
                axes.emplace_back(A, B);
            }
            for (int k = 0; k < half; k++) {
                Point E1 = poly[k];
                Point E2 = poly[(k + 1) % n];
                Point F1 = poly[k + half];
                Point F2 = poly[(k + half + 1) % n];
                axes.emplace_back(midpoint(E1, E2), midpoint(F1, F2));
            }
        }

        int symCount = 0;
        for (auto &ax : axes) {
            const Point &A = ax.first;
            const Point &B = ax.second;
            bool ok = true;
            for (int i = 0; i < n; i++) {
                int j = ( (int)(&ax - &axes[0]) < n ? 0 : 0 ); 
            }

            vector<Point> refl(n);
            for (int i = 0; i < n; i++) {
                refl[i] = reflectAcrossLine(poly[i], A, B);
            }
            reverse(refl.begin(), refl.end());
            bool matched = false;
            for (int s = 0; s < n && !matched; s++) {
                bool good = true;
                for (int i = 0; i < n; i++) {
                    const Point &P = poly[i];
                    const Point &Q = refl[(i + s) % n];
                    if (!almostEqual(P.x, Q.x) || !almostEqual(P.y, Q.y)) {
                        good = false;
                        break;
                    }
                }
                if (good) matched = true;
            }
            if (matched) symCount++;
        }

        cout << "Polygon #" << caseNo++
             << " has " << symCount << " symmetry line(s)." << endl;
    }

    return 0;
}
