#include <bits/stdc++.h>
using namespace std;
const long double PI = acosl(-1.0L);

long double normalize_angle(long double a) {
    while (a < 0) a += 2*PI;
    while (a >= 2*PI) a -= 2*PI;
    return a;
}

int main(){
    int T;
    cin >> T;
    for(int tc = 1; tc <= T; tc++){
        int N;
        long double R;
        cin >> N >> R;
        vector<pair<long double,long double>> intervals;

        for(int i = 0; i < N; i++){
            long double x1,y1,x2,y2;
            cin >> x1 >> y1 >> x2 >> y2;
            long double t1 = atan2l(y1, x1);
            long double t2 = atan2l(y2, x2);
            t1 = normalize_angle(t1);
            t2 = normalize_angle(t2);
            long double d = t2 - t1;
            if (d <= -PI) d += 2*PI;
            else if (d > PI) d -= 2*PI;

            long double a, b;
            if (d >= 0) {
                if (d <= PI) {
                    a = t1;
                    b = t2;
                } else {
                    a = t2;
                    b = t1 + 2*PI;
                }
            } else { 
                if (-d <= PI) {
                    a = t2;
                    b = t1;
                } else {
                    a = t1;
                    b = t2 + 2*PI;
                }
            }
            a = normalize_angle(a);
            b = normalize_angle(b);
            if (b < a) {
                intervals.emplace_back(a, 2*PI);
                intervals.emplace_back(0, b);
            } else {
                intervals.emplace_back(a, b);
            }
        }

        long double cool_pct;
        if (intervals.empty()) {
            cool_pct = 100.0L;
        } else {
            sort(intervals.begin(), intervals.end());
            long double blocked = 0;
            long double cur_s = intervals[0].first;
            long double cur_e = intervals[0].second;
            for(size_t i = 1; i < intervals.size(); i++){
                auto [s,e] = intervals[i];
                if (s <= cur_e) {
                    cur_e = max(cur_e, e);
                } else {
                    blocked += (cur_e - cur_s);
                    cur_s = s;
                    cur_e = e;
                }
            }
            blocked += (cur_e - cur_s);
            if (blocked > 2*PI) blocked = 2*PI;
            cool_pct = (1.0L - blocked / (2*PI)) * 100.0L;
        }

        cout << "Case " << tc << ": "
             << fixed << setprecision(2) << cool_pct << "%" << endl;
    }
    return 0;
}
