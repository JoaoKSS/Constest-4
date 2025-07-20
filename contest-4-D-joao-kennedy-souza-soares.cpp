#include <bits/stdc++.h>
using namespace std;

long long count_grid(double w, double h) {
    long long cols = (long long)floor(w);
    long long rows = (long long)floor(h);
    return cols * rows;
}

long long count_skew(double w, double h) {
    if (h < 1.0 || w < 1.0) return 0;
    const double vstep = sqrt(3.0) / 2.0; 
    long long nrows = 1 + (long long)floor((h - 1.0) / vstep);
    long long odd_rows = (nrows + 1) / 2;
    long long odd_cols = (long long)floor(w);
    long long even_rows = nrows / 2;
    long long even_cols = (w >= 1.0 + 0.5) ? (long long)floor(w - 0.5) : 0;
    return odd_rows * odd_cols + even_rows * even_cols;
}

int main(){
    double a, b;
    while ( (cin >> a >> b) ){
        long long best_grid = count_grid(a, b);

        long long skew1 = count_skew(a, b);
        long long skew2 = count_skew(b, a);
        long long best_skew = max(skew1, skew2);

        if (best_grid >= best_skew) {
            cout << best_grid << " grid" << endl;
        } else {
            cout << best_skew << " skew" << endl;
        }
    }
    return 0;
}
