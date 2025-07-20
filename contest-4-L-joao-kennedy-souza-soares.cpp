#include <iostream>
#include <vector>

using namespace std;   

struct Point {
    long long x, y;
};

long long cross_product(Point p1, Point p2, Point p3) {
    return (p2.x - p1.x) * (p3.y - p2.y) - (p2.y - p1.y) * (p3.x - p2.x);
}

int main() {
    int N;
    while (cin >> N && N != 0) {
        vector<Point> vertices(N);
        for (int i = 0; i < N; ++i) {
            cin >> vertices[i].x >> vertices[i].y;
        }

        bool is_concave = false;

        long long first_turn = cross_product(vertices[0], vertices[1], vertices[2]);

        for (int i = 1; i < N; ++i) {
            Point p1 = vertices[i];
            Point p2 = vertices[(i + 1) % N];
            Point p3 = vertices[(i + 2) % N];

            long long current_turn = cross_product(p1, p2, p3);

            if (current_turn * first_turn < 0) {
                is_concave = true;
                break;
            }
        }

        if (is_concave) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }

    return 0;
}