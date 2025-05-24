#include <iostream>
#include <iomanip>

using namespace std;

class Matrix{
    private:
        long double** a;
        int m,n;
    public:
        Matrix(int m,int n){
            a = new long double*[m+1];
            for (int i = 1; i <= m; ++i) {
                a[i] = new long double[n+1];
            }
            this->m = m;
            this->n = n;
        }
        Matrix(const Matrix &other) {
            m = other.m;
            n = other.n;
            a = new long double*[m+1];
            for (int i = 1; i <= m; ++i) {
                a[i] = new long double[n+1];
                for (int j = 1; j <= n; ++j) {
                    a[i][j] = other.a[i][j];
                }
            }
        }
        ~Matrix(){
            for (int i = 1; i <= m; ++i) {
                delete[] a[i];
            }
            delete[] a;
        }
        friend ostream& operator<<(ostream& os, const Matrix& mat){
            for (int i=1;i<=mat.m;++i){
                for(int j=1;j<=mat.n;++j){
                    os<<fixed<<setprecision(6)<< mat.a[i][j] << " ";
                }
                os << "\n";
            }
            return os;
        }
        Matrix operator*(const Matrix &other){
            if (this->n != other.m) {
                cout << "Khong the nhan hai ma tran nay voi nhau\n";
                return Matrix(0,0);
            }
            Matrix res = Matrix(this->m,other.n);
            for (int i = 1; i <= this->m; ++i) {
                for (int j = 1; j <= other.n; ++j) {
                    double sum = 0;
                    for (int k = 1; k <= this->n; ++k) {
                        sum += this->a[i][k]*other.a[k][j];
                    }
                    res.a[i][j] = sum;
                }
            }
            return res;
        }
        Matrix operator*(const long double& val){
            Matrix res = Matrix(this->m,this->n);
            for (int i = 1; i <= this->m; ++i) {
                for (int j = 1; j <= this->n; ++j) {
                    res.a[i][j] = this->a[i][j]*val;
                }
            }
            return res;
        }
        static Matrix zeros(int m,int n){
            Matrix res = Matrix(m,n);
            for (int i = 1; i <= m; ++i) {
                for (int j = 1; j <= n; ++j) {
                    res.a[i][j] = 0;
                }
            }
            return res;
        }
        double get(int i,int j) const {
            return this->a[i][j];
        }
        void set(int i,int j,double val){
            this->a[i][j] = val;
        }
        void setRow(int i,Matrix row){
            for (int j = 1; j <= this->n; ++j) {
                this->a[i][j] = row.get(1,j);
            }
        }
        void setCol(int j,Matrix col){
            for (int i = 1; i <= this->m; ++i) {
                this->a[i][j] = col.get(i,1);
            }
        }
        int rows() const {
            return this->m;
        }
        int cols() const {
            return this->n;
        }
        Matrix row(int i){
            Matrix res = Matrix(1,this->n);
            for (int j = 1; j <= this->n; ++j) {
                res.set(1,j,this->a[i][j]);
            }
            return res;
        }
        Matrix col(int j){
            Matrix res = Matrix(this->m,1);
            for (int i = 1; i <= this->m; ++i) {
                res.set(i,1,this->a[i][j]);
            }
            return res;
        }
        Matrix transpose(){
            Matrix res = Matrix(n,m);
            for (int i = 1; i <= m; ++i) {
                for (int j = 1; j <= n; ++j) {
                    res.set(j,i,this->a[i][j]);
                }
            }
            return res;
        }
};

int main(){
    int numStates;
    cout << "Nhap so trang thai: ";
    cin >> numStates;
    Matrix transitionMatrix(numStates, numStates);
    cout << "Nhap ma tran chuyen trang thai:\n";
    for (int i = 1; i <= numStates; ++i) {
        for (int j = 1; j <= numStates; ++j) {
            double value;
            cin >> value;
            transitionMatrix.set(i, j, value);
        }
    }
    cout << "Nhap ma tran chuyen trang thai:\n";
    Matrix initialState(1,numStates);
    for (int i = 1; i <= numStates; ++i) {
        double value;
        cin >> value;
        initialState.set(1,i, value);
    }
    int numSteps;
    cout << "Nhap so buoc thoi gian: ";
    cin >> numSteps;
    Matrix result = initialState;
    for (int i=1;i<=numSteps;++i){
        result = result * transitionMatrix ;
    }
    cout << result;
    double sum=0;
    for (int i=1;i<=numStates;++i){
        sum += result.get(1,i);
    }
    cout << sum << "\n";
    return 0;
}