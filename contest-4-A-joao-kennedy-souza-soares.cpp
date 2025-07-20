#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int t;
    cin >> t;

    for (int i = 0; i < t; ++i) {
        if (i > 0) cout << "\n"; 

        int xll1, yll1, xur1, yur1;
        int xll2, yll2, xur2, yur2;

        cin >> xll1 >> yll1 >> xur1 >> yur1;
        cin >> xll2 >> yll2 >> xur2 >> yur2;

        int xll_overlap = max(xll1, xll2);
        int yll_overlap = max(yll1, yll2);
        int xur_overlap = min(xur1, xur2);
        int yur_overlap = min(yur1, yur2);

        if (xll_overlap >= xur_overlap || yll_overlap >= yur_overlap) {
            cout << "No Overlap" << endl;
        } else {
            cout << xll_overlap << " " << yll_overlap << " " << xur_overlap << " " << yur_overlap << endl;
        }
    }

    return 0;
}