#include <iostream>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <Eigen/Dense>
#include <iomanip>

using namespace std;
const double PI = acos(-1);
const double inf = 1e9+7;
const long double EPS = (long double)1e-9;

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
                    if (fabs(mat.a[i][j]) < EPS){
                        mat.a[i][j] = fabs(mat.a[i][j]);
                    }
                    os<<fixed<<setprecision(5)<< mat.a[i][j] << " ";
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
        vector<double> eigenValues(){
            if (m != n){
                cout << "Khong the tinh eigenvalues cho ma tran khong vuong\n";
                return vector<double>();
            }
            Eigen::MatrixXd mat(m,n);
            for (int i=1;i<=m;++i){
                for (int j=1;j<=n;++j){
                    mat(i-1,j-1) = a[i][j];
                }
            }
            Eigen::EigenSolver<Eigen::MatrixXd> eigenSolver(mat);
            vector<double> res;
            for (int i=0;i<m;++i){
                if (abs(eigenSolver.eigenvalues()[i].real()) < EPS){
                    res.push_back(0);
                    continue;
                }
                res.push_back(eigenSolver.eigenvalues()[i].real());
            }
            reverse(res.begin(),res.end());
            return res;
        }
        Matrix eigenVector(){
            if (m != n){
                cout << "Khong the tinh eigenvectors cho ma tran khong vuong\n";
                return Matrix(0,0);
            }
            Eigen::MatrixXd mat(m,n);
            for (int i=1;i<=m;++i){
                for (int j=1;j<=n;++j){
                    mat(i-1,j-1) = a[i][j];
                }
            }
            Eigen::EigenSolver<Eigen::MatrixXd> eigenSolver(mat);
            Matrix res = Matrix(m,m);
            for (int i=0;i<m;++i){
                for (int j=0;j<m;++j){
                    res.set(i+1,j+1,eigenSolver.eigenvectors()(i,j).real());
                }
            }
            for (int i=1;i<=m/2;++i){
                Matrix col = res.col(i);
                res.setCol(i,res.col(m-i+1));
                res.setCol(m-i+1,col);
            }
            return res;
        }
        
};


int main(){
    int m,n;
    cout << "Nhap kich thuoc cho ma tran m x n\n"; 
    cin >> m >> n;
    Matrix a = Matrix(m,n);
    cout << "Nhap cac gia tri cho ma tran " << m << 'x' << n << '\n';
    for (int i=1;i<=m;++i){
        for (int j=1;j<=n;++j){
            long double v;
            cin >> v;
            a.set(i,j,v);
        }
    }
    Matrix AtA = a.transpose()*a;
    vector<double> eigenValues = AtA.eigenValues();
    cout << "\nEigenvalues cua ma tran AtA la:\n";
    for (int i=0;i<eigenValues.size();++i){
        cout << eigenValues[i] << " ";
    }
    vector<double> singularValues = AtA.eigenValues();
    cout << '\n';
    Matrix V = AtA.eigenVector();
    cout << "\nEigenvectors cua ma tran AtA la:\n" << V;
    for (int i=0;i<singularValues.size();++i){
        singularValues[i] = sqrt(singularValues[i]);
    }
    Matrix U = Matrix::zeros(m,m);
    for (int i=0;i<singularValues.size();++i){
        if (singularValues[i] < EPS) continue;
        U.setCol(i+1,a*V.col(i+1)*(1.0/singularValues[i]));
    }
    cout << "\nMa tran U la:\n";
    cout << U << '\n';
    Matrix Sigma = Matrix::zeros(m,n);
    for (int i=0;i<singularValues.size();++i){
        if (singularValues[i] < EPS) continue;
        Sigma.set(i+1,i+1,singularValues[i]);
    }
    cout << "Ma tran V la:\n";
    cout << V << '\n';
    cout << "Ma tran Sigma la:\n";
    cout << Sigma << '\n';
    cout << "Kiem tra ket qua. Ma tran tich UxSigma*(V^T) la:\n";
    cout << U*Sigma*V.transpose();
    return 0;
}