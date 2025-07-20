#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

struct Block {
    long double x, y, r, mass;
};

int main() {
    int N;
    while (cin >> N && N != 0) {
        vector<Block> tower(N);
        bool collapsed = false;

        for (int i = 0; i < N; ++i) {
            cin >> tower[i].x >> tower[i].y >> tower[i].r;
            tower[i].mass = tower[i].r * tower[i].r;

            if (i > 0) {
                for (int j = i - 1; j >= 0; --j) {
                    long double sum_mass_x = 0;
                    long double sum_mass_y = 0;
                    long double total_mass = 0;

                    for (int k = j + 1; k <= i; ++k) {
                        sum_mass_x += tower[k].mass * tower[k].x;
                        sum_mass_y += tower[k].mass * tower[k].y;
                        total_mass += tower[k].mass;
                    }

                    long double cm_x = sum_mass_x / total_mass;
                    long double cm_y = sum_mass_y / total_mass;

                    long double dx = cm_x - tower[j].x;
                    long double dy = cm_y - tower[j].y;
                    long double dist_sq = dx * dx + dy * dy;
                    long double r_sq = tower[j].r * tower[j].r;

                    if (dist_sq >= r_sq) {
                        cout << "Unfeasible " << i << endl;
                        collapsed = true;
                        break;
                    }
                }
            }

            if (collapsed) {
                for (int rem = i + 1; rem < N; ++rem) {
                    long double dummy;
                    cin >> dummy >> dummy >> dummy;
                }
                break;
            }
        }

        if (!collapsed) {
            cout << "Feasible" << endl;
        }
    }

    return 0;
}