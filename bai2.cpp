#include <iostream>
#include <vector>

using namespace std;

int gcd(int a,int b){
    return b == 0 ? a : gcd(b,a%b);
}

int extended_euclid(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int d = extended_euclid(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    //cout << a << ' ' << b << ' ' << x << ' ' << y << '\n';
    return d;
}

int inv(int a,int m){
    int x,y;
    int g = extended_euclid(a,m,x,y);
    if (g!=1)   return 0;
    else return (x+m)%m;
}

bool check_coprime_array(const vector<int>& a){
    int n = a.size();
    for (int i=0;i<n;++i){
        for (int j=i+1;j<n;++j){
            if (gcd(a[i],a[j]) != 1){
                //cout << a[i] << ' ' << a[j]  << '\n';
                return false;
            }
        }
    }
    return true;
}

void chinese_reminder_problem(){
    cout << "Bai toan trung hoa\n";
    cout << "Tim x sao cho x thoa man n phuong trinh co dang:\n";
    cout << "x = a (mod b)\n";
    int n;
    cout << "Nhap so luong phuong trinh: ";
    cin >> n;
    vector<int>a(n),b(n);
    cout << "Nhap cac he so a:\n";
    for (int i=0;i<n;++i)   cin >> a[i];
    cout << "Nhap cac he so cho b:\n";
    for (int i=0;i<n;++i)   cin >> b[i];
    if (check_coprime_array(b)==false){
        cout << "Mang b khong dam bao cac he so la nguyen to cung nhau tung doi mot:\n";
        cout << "=> Khong the tim ket qua:\n";
        return;
    }
    cout << "He phuong trinh co dang: \n";
    for (int i=0;i<n;++i){
        cout << "x = " << a[i] << " (mod " << b[i] << ")\n";
    }

    long long M=1;
    for (int i=0;i<n;++i){
        M *= b[i];
    }
    long long res=0;
    for (int i=0;i<n;++i){
        long long p = M/b[i];
        res = (res + a[i]*p*(inv(p,b[i])%M) + M)%M;
    }
    cout << "Ket qua cua phuong trinh la: x = " << res << " (mod " << M << ")\n";
}


int main(){
    chinese_reminder_problem();
    return 0;
}