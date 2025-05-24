#include <iostream>
#include <math.h>

using namespace std;

const double LEARNING_RATE = 0.01;
const double TOLERANCE = 1e-6;
const int ITERATIONS = 10000;
const double EPS = 1e-8;
const double E = exp(1);
const double MOMENTUM = 0.9;
const int INF = 1e9;

double ln(double x){
    return log(x)/log(E);
}

double f(double x){
    double tu = (3*x*x*x + 3*x*x - 4*x)*(pow(E,x) + x)*ln(abs(x));
    double mau = 5*pow(E,x);
    return tu/mau;
}

double grad(double x){
    return (f(x+EPS) - f(x-EPS))/(2*EPS);
}

double gd_momentum(double initial_x){
    double x = initial_x;
    double v = 0;
    for (int i=1;i<=ITERATIONS;++i){
        double df = grad(x);
        if (fabs(df) < TOLERANCE){
            cout << "Converged at iteration " << i << "\n";
            break;
        }
        if(i%10==0)cout << "i = " << i << " => x = " << x << " => f(x) = " << f(x) << '\n';
        v = MOMENTUM*v + LEARNING_RATE * df;
        
        double x_new = x - v;
        if (fabs(x-x_new) < TOLERANCE){
            cout << "Converged at iteration " << i << "\n";
            break;
        }
        x = x_new;
    }
    return x;
}


int main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    double x_result = gd_momentum(2);
    cout << "x = " << x_result << '\n';
    cout << "f(x) = " << f(x_result) << '\n';
    return 0;
}