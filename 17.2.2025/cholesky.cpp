#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>

using namespace std;
const long double EPS = 1e-9;
typedef vector<vector<long double>> matrix;

bool isDoiXung(const matrix& a){
    int n = a.size();
    int m = a[0].size();
    if (n!=m)   return false;
    for (int i=0;i<n;++i){
        for (int j=0;j<n;++j){
            if (fabs(a[i][j]-a[j][i]) > EPS)   return false;
        }
    }
    return true;
}

bool Cholesky (const matrix& a,matrix& L){
    int n = a.size();
    for (int i=0;i<n;++i){
        for (int j=0;j<=i;++j){
            long double sum = 0.0;
            for (int k=0;k<j;++k){
                sum += L[i][k]*L[j][k];
            }
            if (i==j){
                long double diag = a[i][i] - sum;
                if (diag <= EPS) return false;
                L[i][j] = sqrt(diag);
            }else{
                if (fabs(L[j][j]) < EPS) return false;
                L[i][j] = (a[i][j]-sum)/L[j][j];
            }
        }
    }
    return true;
}

matrix transpose(const matrix& a){
    int n = a.size();
    int m = a[0].size();
    matrix T(m,vector<long double>(n));
    for (int i=0;i<m;++i){
        for (int j=0;j<n;++j){
            T[i][j] = a[j][i];
        }
    }
    return T;
}

matrix operator*(const matrix& a,const matrix& b){
    int arow = a.size(),brow = b.size();
    int acol = a[0].size(),bcol = b[0].size();
    if (acol!=brow){
        cout << "So hang cua ma tran a phai bang so cot cua ma tran b\n";
        return matrix(0);
    }
    matrix result(arow,vector<long double>(bcol,0.0));
    for (int i=0;i<arow;++i){
        for (int j=0;j<bcol;++j){
            long double sum=0.0;
            for (int k=0;k<acol;++k){
                result[i][j] += a[i][k]*b[k][j];
            }
        }
    }
    return result;
}

void print_matrix(const matrix& a){
    int n = a.size();
    int m = a[0].size();
    for (int i=0;i<n;++i){
        for (int j=0;j<m;++j){
            cout<<fixed<<setprecision(5)<< a[i][j] << ' ';
        }
        cout << '\n';
    }
}

int main(){
    int n;
    cout << "Nhap kich thuoc n cho ma tran vuong n x n: \n";
    cin >> n;
    matrix a(n,vector<long double>(n,0.0));
    matrix L(n,vector<long double>(n,0.0));
    cout << "Nhap cac phan tu cho ma tran " << n << 'x' << n << ":\n"; 
    for (int i=0;i<n;++i){
        for (int j=0;j<n;++j){
            cin >> a[i][j];
        }
    }
    if (isDoiXung(a)== false){
        cout << "Ma tran khong doi xung, khong the thuc hien phan ra Cholesky \n";
    }
    else{
        if (Cholesky(a,L)==false){
            cout << "Ma tran khong xac dinh duong, khong the thuc hien phan ra Cholesky\n";
        }
        else{
            cout << "Ma tran L sau khi phan ra Cholesky tu ma tran a la:\n";
            print_matrix(L);
            cout << "Ma tran L*(LT):\n";
            print_matrix(L*transpose(L));
        }
    }
    return 0;
}
