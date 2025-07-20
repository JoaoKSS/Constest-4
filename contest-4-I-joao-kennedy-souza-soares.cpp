#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    int n;
    bool first_case = true;

    while (cin >> n) {
        if (!first_case) {
            cout << endl;
        }
        first_case = false;

        double radius = (2.0 * n - 1.0) / 2.0;
        double radius_sq = radius * radius;

        long long contained_count = 0;
        long long intersected_count = 0;

        for (long long i = 0; i < n; ++i) {
            for (long long j = 0; j < n; ++j) {
                double dist_sq_min = i * i + j * j;
                double dist_sq_max = (i + 1) * (i + 1) + (j + 1) * (j + 1);

                if (dist_sq_max < radius_sq) {
                    contained_count++;
                } 
                else if (dist_sq_min < radius_sq) {
                    intersected_count++;
                }
            }
        }

        cout << "In the case n = " << n << ", " << intersected_count * 4 
                  << " cells contain segments of the circle." << endl;
        cout << "There are " << contained_count * 4 
                  << " cells completely contained in the circle." << endl;
    }

    return 0;
}