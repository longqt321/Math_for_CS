#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <Eigen/Dense>

const double EPS = 1e-10;

using namespace std;
const double PI = acos(-1);
const double inf = 1e9+7;


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

        Matrix invert() {
            if (m != n) {
                cout << "Khong the nghich dao ma tran khong vuong\n";
                return Matrix(0, 0);
            }
            
            Matrix inv(m, n);
            Matrix temp(*this);
            
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= n; ++j) {
                    inv.set(i, j, (i == j) ? 1.0 : 0.0);
                }
            }
            
            for (int i = 1; i <= n; ++i) {
                double diag = temp.get(i, i);
                if (fabs(diag) < EPS){
                    cout << "Khong the nghich dao ma tran vi co hang bang 0.\n";
                    return Matrix(0,0);
                }
                for (int j = 1; j <= n; ++j) {
                    temp.set(i, j, temp.get(i, j) / diag);
                    inv.set(i, j, inv.get(i, j) / diag);
                }
                for (int k = 1; k <= n; ++k) {
                    if (k != i) {
                        double factor = temp.get(k, i);
                        for (int j = 1; j <= n; ++j) {
                            temp.set(k, j, temp.get(k, j) - temp.get(i, j) * factor);
                            inv.set(k, j, inv.get(k, j) - inv.get(i, j) * factor);
                        }
                    }
                }
            }
            return inv;
        }

        vector<double> eigenvalues(){
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
        Matrix eigenvector(){
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
        bool isDiagonalizable(){
            if (m!=n)   return false;

            Matrix eigen_vecs = this->eigenvector();
            Eigen::MatrixXd P_eigen(n,n);

            for (int i=1;i<=n;++i){
                for (int j=1;j<=n;++j){
                    P_eigen(i-1,j-1) = eigen_vecs.get(i,j);
                }
            }
            double det_P = P_eigen.determinant();
            return det_P > EPS;
        }
};


int main(){
    int n;
    cout << "Nhap kich thuoc n cho ma tran vuong n x n : \n";
    cin >> n;
    Matrix a = Matrix(n,n);
    cout << "Nhap cac phan tu cho ma tran " << n << 'x' << n << ":\n"; 
    for (int i=1;i<=n;++i){
        for (int j=1;j<=n;++j){
            double v;
            cin >> v;
            a.set(i,j,v);
        }
    }
    cout << "Ma tran a ban dau la:\n";
    cout << a << '\n';
    if (a.isDiagonalizable() == false){
        cout << "Ma tran khong thoa man dieu kien co du vectors doc lap:\n";
        cout << "=> Ma tran khong thoa man dieu kien cheo hoa:\n";
        return 0;
    }
    
    vector<double> eigen_vals = a.eigenvalues();
    Matrix eigen_vecs = a.eigenvector();

    Matrix P(n,n);
    for (int j = 1; j <= n; j++){
        if (j-1 < eigen_vals.size()){
            for (int i = 1; i <= n; i++){
                P.set(i, j, eigen_vecs.get(i,j));
            }
        }
        else {
            for (int i = 1; i <= n; i++){
                P.set(i, j, 0.0);
            }
        }
    }
    cout << "\nMa tran P (cac vecto rieng theo cot):\n";
    cout << P;
    Matrix D(n,n);
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            if (i == j && i-1 < eigen_vals.size())
                D.set(i, j, eigen_vals[i-1]);
            else
                D.set(i, j, 0.0);
        }
    }
    cout << "\nMa tran D (duong cheo voi eigenvalues):\n";
    cout << D << '\n';

    Matrix Pinv = P.invert();
    cout << "Ma tran nghich dao cua P:\n";
    cout << Pinv << '\n';


    Matrix A_diag = P*D*Pinv;

    cout << "Kiem tra ket qua. Ma tran tich cua PxDxPinv:\n";
    cout << A_diag << '\n';
    return 0;
}