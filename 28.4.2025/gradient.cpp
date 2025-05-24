#include <iostream>
#include <math.h>

using namespace std;

const double LEARNING_RATE = 0.01f;
const double TOLERANCE = 1e-6f;
const int ITERATIONS = 10000;
const double EPS = 1e-9f;
const double E = exp(1);

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

double gradient_descent(double initial_x){
    double x = initial_x;
    for (int i=1;i<=ITERATIONS;++i){
        double df = grad(x);
        if (fabs(df) < TOLERANCE){
            cout << "Converged at iteration " << i << "\n";
            break;
        }
        if(i%10==0)cout << "i = " << i << " => x = " << x << " => f(x) = " << f(x) << '\n';
        x = x - LEARNING_RATE*df;
    }
    return x;
}

int main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    double x_result = gradient_descent(1);
    cout << "Result:\n";
    cout << "x = "  << x_result << "\nf(x) = " << f(x_result) << '\n'; 
    return 0;
}