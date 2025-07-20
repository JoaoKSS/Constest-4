#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Box {
    ll x1, y1, z1, x2, y2, z2;
};

int main() {
    int n;
    while ( (cin >> n) ) {
        vector<Box> boxes(n);
        vector<ll> xs, ys, zs;
        for (int i = 0; i < n; i++) {
            cin >> boxes[i].x1 >> boxes[i].y1 >> boxes[i].z1
                >> boxes[i].x2 >> boxes[i].y2 >> boxes[i].z2;
            xs.push_back(boxes[i].x1);
            xs.push_back(boxes[i].x2);
            ys.push_back(boxes[i].y1);
            ys.push_back(boxes[i].y2);
            zs.push_back(boxes[i].z1);
            zs.push_back(boxes[i].z2);
        }

        if (n < 2) {
            cout << 0 << endl;
            continue;
        }

        auto uniq = [&](vector<ll>& v) {
            sort(v.begin(), v.end());
            v.erase(unique(v.begin(), v.end()), v.end());
        };
        uniq(xs);
        uniq(ys);
        uniq(zs);

        ll total = 0;

        for (int i = 0; i + 1 < (int)xs.size(); i++) {
            ll dx = xs[i+1] - xs[i];
            for (int j = 0; j + 1 < (int)ys.size(); j++) {
                ll dy = ys[j+1] - ys[j];
                for (int k = 0; k + 1 < (int)zs.size(); k++) {
                    ll dz = zs[k+1] - zs[k];
                    int cnt = 0;
                    for (int b = 0; b < n; b++) {
                        if (boxes[b].x1 <= xs[i] && boxes[b].x2 >= xs[i+1]
                         && boxes[b].y1 <= ys[j] && boxes[b].y2 >= ys[j+1]
                         && boxes[b].z1 <= zs[k] && boxes[b].z2 >= zs[k+1]) {
                            cnt++;
                            if (cnt >= 2) break;
                        }
                    }
                    if (cnt >= 2) {
                        total += dx * dy * dz;
                    }
                }
            }
        }

        cout << total << endl;
    }

    return 0;
}
