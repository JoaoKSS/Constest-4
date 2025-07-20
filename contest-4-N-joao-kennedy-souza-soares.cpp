#include <iostream>
#include <iomanip>
#include <math.h>
#include <algorithm>

using namespace std;

#define eps 1e-8
#define INF 1e+30

struct Pt {
    double x, y;
    Pt(double a = 0, double b = 0): x(a), y(b) {}

    bool operator<(const Pt &a) const {
        if (fabs(x - a.x) > eps) return x < a.x;
        return y < a.y;
    }

    bool operator==(const Pt &a) const {
        return fabs(x - a.x) < eps && fabs(y - a.y) < eps;
    }

    Pt operator+(const Pt &a) const {
        return Pt(x + a.x, y + a.y);
    }

    Pt operator-(const Pt &a) const {
        return Pt(x - a.x, y - a.y);
    }

    Pt operator/(const double val) const {
        return Pt(x / val, y / val);
    }

    Pt operator*(const double val) const {
        return Pt(x * val, y * val);
    }
};

typedef Pt Vector;

double dist(Pt a, Pt b) {
    return hypot(a.x - b.x, a.y - b.y);
}

double dot(Pt a, Pt b) {
    return a.x * b.x + a.y * b.y;
}

double cross2(Pt a, Pt b) {
    return a.x * b.y - a.y * b.x;
}

double cross(Pt o, Pt a, Pt b) {
    return (a.x - o.x)*(b.y - o.y) - (a.y - o.y)*(b.x - o.x);
}

int between(Pt a, Pt b, Pt c) {
    return dot(c - a, b - a) >= 0 && dot(c - b, a - b) >= 0;
}

int onSeg(Pt a, Pt b, Pt c) {
    return between(a, b, c) && fabs(cross(a, b, c)) < eps;
}

double distProjection(Pt as, Pt at, Pt s) {
    double a = at.y - as.y;
    double b = as.x - at.x;
    double c = - (a * as.x + b * as.y);
    return fabs(a * s.x + b * s.y + c) / hypot(a, b);
}

int monotone(int n, Pt p[], Pt ch[]) {
    sort(p, p + n);
    int m = 0, t;
    for (int i = 0; i < n; i++) {
        while (m >= 2 && cross(ch[m - 2], ch[m - 1], p[i]) <= 0)
            m--;
        ch[m++] = p[i];
    }
    for (int i = n - 1, t = m + 1; i >= 0; i--) {
        while (m >= t && cross(ch[m - 2], ch[m - 1], p[i]) <= 0)
            m--;
        ch[m++] = p[i];
    }
    return m - 1;
}

double smallRect(int n, Pt ch[]) {
    double lx = INF, ly = INF, rx = -INF, ry = -INF;
    int up = 0, down = 0, left = 0, right = 0;
    double ret = INF;

    for (int i = 0; i < n; i++) {
        if (ch[i].x > rx) rx = ch[i].x, right = i;
        if (ch[i].y > ry) ry = ch[i].y, up = i;
        if (ch[i].x < lx) lx = ch[i].x, left = i;
        if (ch[i].y < ly) ly = ch[i].y, down = i;
    }

    int corner[] = {up, down, left, right};
    Pt vec[] = {Pt(-1, 0), Pt(1, 0), Pt(0, -1), Pt(0, 1)};
    ret = (rx - lx) * (ry - ly);

    for (int j = 0; j < 4; j++) {
        while (true) {
            Pt a = ch[corner[j]], b = ch[(corner[j] + 1) % n], c = vec[j];
            if (fabs(cross2(b - a, c)) < eps)
                corner[j] = (corner[j] + 1) % n;
            else break;
        }
    }

    for (int i = 0; i < n; i++) {
        double mxVal = -INF;
        int mxIdx = 0;
        for (int j = 0; j < 4; j++) {
            Pt a = ch[corner[j]], b = ch[(corner[j] + 1) % n], c = vec[j];
            double cosA = dot(b - a, c) / dist(b, a) / dist(c, Pt(0, 0));
            if (mxVal < cosA)
                mxVal = cosA, mxIdx = j;
        }

        double cos = mxVal;
        double sin = sqrt(1 - cos * cos);
        for (int j = 0; j < 4; j++) {
            double tx = vec[j].x * cos - vec[j].y * sin;
            double ty = vec[j].x * sin + vec[j].y * cos;
            vec[j] = Pt(tx, ty);
        }

        for (int j = 0; j < 4; j++) {
            while (true) {
                Pt a = ch[corner[j]], b = ch[(corner[j] + 1) % n], c = vec[j];
                if (fabs(cross2(b - a, c)) < eps)
                    corner[j] = (corner[j] + 1) % n;
                else break;
            }
        }

        double w = distProjection(ch[corner[0]], ch[corner[0]] + vec[0], ch[corner[1]]);
        double h = distProjection(ch[corner[2]], ch[corner[2]] + vec[2], ch[corner[3]]);
        ret = min(ret, w * h);
    }

    return ret;
}

int main() {
    Pt p[2048], ch[2048];
    int n;
    cout << fixed << setprecision(4); 
    while (cin >> n && n) {
        for (int i = 0; i < n; i++)
            cin >> p[i].x >> p[i].y;

        int m = monotone(n, p, ch);

        if (m < 3) {
            cout << 0.0000 << endl;
            continue;
        }

        double ret = smallRect(m, ch);
        cout << ret << endl;
    }
    return 0;
}
