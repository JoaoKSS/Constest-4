#include <bits/stdc++.h>
using namespace std;

struct Point {
    double x,y;
    Point operator+(Point const&o) const{ return {x+o.x,y+o.y}; }
    Point operator-(Point const&o) const{ return {x-o.x,y-o.y}; }
    Point operator*(double s) const{ return {x*s,y*s}; }
};

double dot(Point a,Point b){ return a.x*b.x + a.y*b.y; }
double cross(Point a,Point b){ return a.x*b.y - a.y*b.x; }

vector<Point> clipHP(vector<Point> P, Point A, Point n, double h){
    vector<Point> Q;
    int m = P.size();
    for(int i=0;i<m;i++){
        Point S = P[i], E = P[(i+1)%m];
        double fS = dot(n, S-A) - h;
        double fE = dot(n, E-A) - h;
        bool inS = (fS <= 0), inE = (fE <= 0);
        if(inS && inE){
            Q.push_back(E);
        } else if(inS && !inE){
            double t = fS/(fS - fE);
            Q.push_back(S + (E-S)*t);
        } else if(!inS && inE){
            double t = fS/(fS - fE);
            Q.push_back(S + (E-S)*t);
            Q.push_back(E);
        }
    }
    return Q;
}

double polygonArea(vector<Point> const& P){
    double A=0;
    for(int i=0,n=P.size();i<n;i++){
        A += cross(P[i], P[(i+1)%n]);
    }
    return fabs(A)*0.5;
}

int main(){
    while(true){
        int n,k;
        double h;
        cin>>n>>k>>h;
        if(!cin|| (n|k|int(h))==0) break;

        vector<Point> poly(n);
        for(int i=0;i<n;i++){
            cin>>poly[i].x>>poly[i].y;
        }

        vector<Point> Apts(n), un(n);
        for(int i=0;i<n;i++){
            Point A = poly[i], B = poly[(i+1)%n];
            Point v = {B.x-A.x, B.y-A.y};
            Point inorm = {-v.y, v.x};
            double L = sqrt(dot(inorm,inorm));
            inorm.x/=L; inorm.y/=L;
            Apts[i]=A; un[i]=inorm;
        }

        int FULL = 1<<n;
        vector<double> areaI(FULL, 0.0);

        vector<int> masks;
        masks.reserve(1<<n);
        for(int m=1;m<FULL;m++){
            if(__builtin_popcount(m) <= k){
                masks.push_back(m);
                vector<Point> Q = poly;
                for(int i=0;i<n;i++){
                    if(m & (1<<i)){
                        Q = clipHP(Q, Apts[i], un[i], h);
                        if(Q.empty()) break;
                    }
                }
                if(!Q.empty())
                    areaI[m] = polygonArea(Q);
            }
        }

        double best = 0.0;
        for(int A : masks){
            double u = 0.0;
            for(int T=A; T; T=(T-1)&A){
                double a = areaI[T];
                int pc = __builtin_popcount(T);
                u += ((pc&1)? +a : -a);
            }
            best = max(best, u);
        }

        cout<<fixed<<setprecision(2)<<best << endl;
    }
    return 0;
}
