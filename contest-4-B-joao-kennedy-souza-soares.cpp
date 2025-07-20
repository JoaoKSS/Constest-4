#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
    int n;
    cin >> n;

    const double PI = 2.0 * acos(0.0); 
    for (int i = 0; i < n; ++i) {
        double d, l;
        cin >> d >> l;

        double a = l / 2.0;        
        double c = d / 2.0;        
        double b = sqrt(max(0.0, a * a - c * c));  

        double area = PI * a * b;
        cout << fixed << setprecision(3) << area << endl;
    }

    return 0;
}
