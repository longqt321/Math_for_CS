#include <iostream>
#include <math.h>
#include <algorithm>
#include <functional>
#include <random>
using namespace std;
const double eps = 1e-6;


struct point{
    double x,y;
    point(double x=0,double y=0) : x(x),y(y){}
    bool operator==(const point& o){
        return fabs(x - o.x) <= eps && fabs(y-o.y) <= eps;
    }
    bool operator!=(const point& o){
        return !(*this == o); 
    }
    point operator-(const point& o){
        return point(x-o.x,y - o.y);
    }
    point operator+(const point& o){
        return point(x+o.x,y+o.y);
    }
    double length() const{
        return sqrt((long double)x*x + (long double)y*y);
    }
};
ostream& operator<<(ostream& os, const point& a){
    os << '(' << a.x << ',' << a.y << ')';
    return os;
}

double dot(const point& a,const point& b){
    return a.x*b.x + a.y*b.y;
}

double calcAngle(const point& a,const point& b){
    return acos(dot(a,b)/a.length()/b.length());
}

vector<point> gift_wrapping(vector<point>input){
    int n = input.size();
    if (n<=2)   return input;
    for (int i=1;i<n;++i){
        if (input[0].x > input[i].x) swap(input[0],input[i]);
    }
    vector<point>hull;
    hull.push_back(input[0]);
    do
    {
        // Đỉnh cuối
        point p = hull.back();


        // Đỉnh kế cuối
        // Nếu hull size = 1 thì điểm kế cuối là point(p.x,p.y-1), để hướng nhìn ban đầu là từ dưới lên trên.
        point p1 = (hull.size() == 1 ? point(p.x,p.y-1) : hull[hull.size()-2]);

        // Điểm tiếp theo của tập hull
        point q = input[0];
        double angle = calcAngle(p1-p,q-p);

        for (int i=1;i<n;++i){
            if (q==p || q == p1){
                q = input[i];
                angle = calcAngle(p1-p,q-p);
                continue;
            }
            if (input[i] == p || input[i] == p1) continue;

            double newAngle = calcAngle(p1-p,input[i]-p);
            if (fabs(angle-newAngle) > eps){
                if (angle<newAngle){
                    q = input[i];
                    angle = newAngle;
                }
            }
            else{
                if ((q-p).length() > (input[i] - p).length()){
                    q = input[i];
                    angle = newAngle;
                }
            }
        }
        hull.push_back(q);
        cout << "Hull size: " << hull.size() << '\n';
        cout << hull[0] << ' ' << hull.back() << '\n';
    } while (hull[0] != hull.back());
    hull.pop_back();
    return hull;
}

int main(){
    int n;
    cin >> n;
    int k=5;
    srand(time(nullptr));
    vector<point>list;
    for (int i=1;i<=n;++i){
        double x,y;
        x = rand()%k + 1;
        y = rand()%k + 1;
        list.push_back(point(x,y));
    }
    for (const point& p : list){
        cout << p.x << ' ' << p.y << '\n';
    }
    cout << "Convex hull:\n";
    vector<point>hull = gift_wrapping(list);
    for (const point& p : hull){
        cout << p.x << ' ' << p.y << '\n';
    }
    return 0;
}