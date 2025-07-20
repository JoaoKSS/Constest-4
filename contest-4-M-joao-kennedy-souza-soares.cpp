#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>

using namespace std;

struct Pt {
    double x, y;
};

bool cmp(Pt a, Pt b) {
    if (a.x != b.x)
        return a.x < b.x;
    return a.y < b.y;
}

double cross(Pt o, Pt a, Pt b) {
    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

int monotone(Pt p[], int n, Pt ch[]) {
    sort(p, p + n, cmp);
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

int main() {
    int t, n;
    cin >> t;
    while (t--) {
        double len;
        cin >> len >> n;

        Pt p[1005], ch[1005];
        for (int i = 0; i < n; i++)
            cin >> p[i].x >> p[i].y;

        int m = monotone(p, n, ch);

        double sum = 0;
        for (int i = 0; i < m; i++) {
            double dx = ch[i].x - ch[i + 1].x;
            double dy = ch[i].y - ch[i + 1].y;
            sum += sqrt(dx * dx + dy * dy);
        }

        cout << fixed << setprecision(5) << max(len, sum) << endl;
    }

    return 0;
}
