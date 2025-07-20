#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Pt {
    int x, y;
    Pt(int a = 0, int b = 0) : x(a), y(b) {}
    bool operator<(const Pt &p) const {
        if (p.x != x)
            return x < p.x;
        return y < p.y;
    }
};

bool cmp(Pt a, Pt b) {
    if (a.y != b.y)
        return a.y < b.y;
    return a.x < b.x;
}

int main() {
    int testcase;
    cin >> testcase;
    while (testcase--) {
        int h, w;
        cin >> h >> w;

        vector<Pt> tree;
        tree.push_back(Pt(0, 0));
        tree.push_back(Pt(h, w));
        tree.push_back(Pt(h, 0));
        tree.push_back(Pt(0, w));

        while (true) {
            int op, x, y, dx = 0, dy = 0;
            cin >> op;
            if (op == 0) break;
            cin >> x >> y;
            if (op != 1) cin >> dx >> dy;

            for (int i = 0; i < op; i++) {
                tree.push_back(Pt(x, y));
                x += dx;
                y += dy;
            }
        }

        sort(tree.begin(), tree.end());
        int area = 0;
        int n = tree.size();

        for (int i = 0; i < n; i++) {
            int mny = 0, mxy = w;
            for (int j = i + 1; j < n; j++) {
                area = max(area, (tree[j].x - tree[i].x) * (mxy - mny));
                if (tree[j].x == tree[i].x) continue;
                if (tree[j].y > tree[i].y)
                    mxy = min(mxy, tree[j].y);
                else
                    mny = max(mny, tree[j].y);
            }
        }

        sort(tree.begin(), tree.end(), cmp);

        for (int i = 0; i < n; i++) {
            int mnx = 0, mxx = h;
            for (int j = i + 1; j < n; j++) {
                area = max(area, (tree[j].y - tree[i].y) * (mxx - mnx));
                if (tree[j].y == tree[i].y) continue;
                if (tree[j].x > tree[i].x)
                    mxx = min(mxx, tree[j].x);
                else
                    mnx = max(mnx, tree[j].x);
            }
        }

        cout << area << endl;
    }
    return 0;
}
