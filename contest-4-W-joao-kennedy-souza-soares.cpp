#include <bits/stdc++.h>
using namespace std;

int main() {
    const int OFFSET = 500;
    const int SIZE = 20001;
    vector<int> city(SIZE, 0);

    int l, h, r;
    int rmax = -1;

    while ( (cin >> l >> h >> r) ) {
        for (int x = l; x < r; x++) {
            city[x + OFFSET] = max(city[x + OFFSET], h);
        }
        rmax = max(r, rmax);
    }

    int i = 0;
    while (i < SIZE && city[i] == 0) {
        i++;
    }

    bool first = true;
    while (i <= rmax + OFFSET) {
        if (!first) {
            cout << ' ';
        }
        first = false;

        int x_coord = i - OFFSET;
        int curH    = city[i];

        cout << x_coord << ' ' << curH;

        while (i <= rmax + OFFSET && city[i] == curH) {
            i++;
        }
    }
    cout << "\n";
    return 0;
}
