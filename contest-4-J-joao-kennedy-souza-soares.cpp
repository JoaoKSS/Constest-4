#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;

void solve() {
    int m;
    cin >> m;
    vector<long double> radii(m);
    for (int i = 0; i < m; ++i) {
        cin >> radii[i];
    }

    sort(radii.begin(), radii.end());

    long double min_width = -1.0;

    do {
        if (m == 0) {
            min_width = 0.0;
            break;
        }

        vector<long double> centers_x(m);
        centers_x[0] = 0.0;

        for (int i = 1; i < m; ++i) {
            long double best_x = 0.0;
            for (int j = 0; j < i; ++j) {
                long double d = 2.0 * sqrtl(radii[i] * radii[j]);
                best_x = max(best_x, centers_x[j] + d);
            }
            centers_x[i] = best_x;
        }

        long double leftmost = centers_x[0] - radii[0];
        long double rightmost = centers_x[0] + radii[0];

        for (int i = 1; i < m; ++i) {
            leftmost = min(leftmost, centers_x[i] - radii[i]);
            rightmost = max(rightmost, centers_x[i] + radii[i]);
        }

        long double current_width = rightmost - leftmost;

        if (min_width < 0 || current_width < min_width) {
            min_width = current_width;
        }

    } while (next_permutation(radii.begin(), radii.end()));

    cout << fixed << setprecision(3) << min_width << endl;
}

int main() {
    int n;
    cin >> n;
    while (n--) {
        solve();
    }
    return 0;
}
