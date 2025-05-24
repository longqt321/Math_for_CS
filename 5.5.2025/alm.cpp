#include <iostream>
#include <cmath>
#include <iomanip>
#include <functional>

using namespace std;

const double EPSILON = 1e-6;
const int MAX_ITER = 100;
const double ALPHA = 0.01;


void solveALM(
    function<double(double, double)> f,
    function<double(double, double)> h,
    function<double(double, double, double)> df_dx1,
    function<double(double, double, double)> df_dx2,
    double x1_init, double x2_init,
    string title
) {
    double x1 = x1_init, x2 = x2_init;
    double lambda = 0.0;
    double rk = 1.0;

    cout << "== " << title << " ==" << endl;
    cout << fixed << setprecision(6);

    for (int k = 0; k < MAX_ITER; ++k) {
        double constraint = h(x1, x2);

       
        double g1 = df_dx1(x1, x2, lambda + 2 * rk * constraint);
        double g2 = df_dx2(x1, x2, lambda + 2 * rk * constraint);


        x1 -= ALPHA * g1;
        x2 -= ALPHA * g2;


        constraint = h(x1, x2);
        lambda += 2 * rk * constraint;

        cout << "Iter " << k + 1 << ": x1 = " << x1 << ", x2 = " << x2 << ", h = " << constraint << endl;

        if (fabs(constraint) < EPSILON) break;
    }

    cout << "Final solution: f(x) = " << f(x1, x2) << ", constraint = " << h(x1, x2) << "\n\n";
}
int main() {
    //  1: f(x) = 6x1^2 + 4x1x2 + 3x2^2, h(x) = x1 + x2 - 5
    solveALM(
        [](double x1, double x2) {
            return 6 * x1 * x1 + 4 * x1 * x2 + 3 * x2 * x2;
        },
        [](double x1, double x2) {
            return x1 + x2 - 5;
        },
        [](double x1, double x2, double lag_term) {
            return 12 * x1 + 4 * x2 + lag_term;
        },
        [](double x1, double x2, double lag_term) {
            return 4 * x1 + 6 * x2 + lag_term;
        },
        0.0, 0.0,
        "Example 1: f(x1,x2) = 6x1^2 + 4x1x2 + 3x2^2, h(x1,x2) = x1 + x2 - 5"
    );

    //  2: g(y) = 5y1^2 + 2y1y2 + 7y2^2, c(y) = y1 - y2 - 3
    solveALM(
        [](double y1, double y2) {
            return 5 * y1 * y1 + 2 * y1 * y2 + 7 * y2 * y2;
        },
        [](double y1, double y2) {
            return y1 - y2 - 3;
        },
        [](double y1, double y2, double lag_term) {
            return 10 * y1 + 2 * y2 + lag_term;
        },
        [](double y1, double y2, double lag_term) {
            return 2 * y1 + 14 * y2 - lag_term;
        },
        0.0, 0.0,
        "Example 2: g(y1,y2) = 5y1^2 + 2y1y2 + 7y2^2, c(y1,y2) = y1 - y2 - 3"
    );

    return 0;
}