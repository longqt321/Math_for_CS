#include <iostream>
#include <vector>

using namespace std;

// Hàm tính phi Euler
// Độ phức tạp: O(sqrt(N))
long long Euler_totient_function(long long n){
    if (n==0)   return 0;
    long long ans = n;
    for (int i=2;i*i<=n;++i){
        if (n%i==0){
            ans -= ans/i;
            while (n%i==0)  n/=i;
        }
    }
    if (n>1)    ans -= ans/n;
    return ans;
}

// Thuật toán Euclid mở rộng
// Độ phức tạp: O(logmax(a,b))
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

// Độ phức tạp: O(logN)
long long power(long long a,long long n){
    if (n==0)   return 1;
    if (n==1)   return a;
    long long tmp = power(a,n/2);
    if (n%2==1) return a*tmp*tmp;
    else return  tmp*tmp;
}

// Độ phức tạp: O(logN)
long long power_mod(long long a, long long n, long long m) {
    long long res = 1;
    a = a % m;
    while (n > 0) {
        if (n % 2 == 1) {
            res = (res * a) % m;
        }
        a = (a * a) % m;
        n = n / 2;
    }
    return res;
}

// Tìm nghịch đảo modulo bằng thuật toán Euclid mở rộng
// Độ phức tạp = độ phức tạp của hàm extended_euclid.
int inv(int a,int m){
    int x,y;
    int g = extended_euclid(a,m,x,y);
    if (g!=1)   return 0;
    else return (x+m)%m;
}

// Tìm nghịch đảo modulo bằng định lý Euler
// Độ phức tạp: O(sqrtN). Do cần tính hàm phi Euler cho m.
long long euler_inv(long long a,long long m){
    long long phi = Euler_totient_function(m);
    return (power_mod(a,phi-1,m)+m)%m;
}

// Tìm nghịch đảo modulo bằng phương pháp phép chia Euclid (Euclidean division).
// Độ phức tạp: xấp xỉ O(logN)
int euclid_inv(int a,int m){
    if (a>m) a%=m;
    return a <= 1 ? a : m - ((long long)(m/a)*euclid_inv(m%a,m)%m+m)%m;
}

// Tìm nghịch đảo modulo bằng định lý Fermat nhỏ
// Độ phức tạp: O(logN).
long long fermat_inv(long long a,long long m){
    return (power_mod(a,m-2,m)+m)%m;
}

bool check_add(long long x,long long y,long long m){
    return (x+y+m*m)%m == (x%m+y%m+m*m)%m;
}

bool check_minus(long long x,long long y,long long m){
    return (x-y+m*x*y)%m == ((x%m-y%m)+m*x*y)%m;
}
bool check_multiply(long long x,long long y,long long m){
    return (x*y+m)%m == (x%m*y%m+m)%m;
}

// Có thể cho kết quả sai do bị tràn số ở hàm power vì lấy mod sau.
bool check_power(long long x,long long n,long long m){
    //cout << power(x,n) << ' ' << power_mod(x,n,m) << '\n';
    return power(x,n)%m == power_mod(x,n,m);
}

bool check_inv(long long a,long long x,long long m){
    // cout << a << ' ' << x << ' ' << m << '\n';
    // cout << ((a%m)*(x%m)+m)%m << '\n';
    return ((a%m)*(x%m)+m)%m == 1;
}

int gcd(int a,int b){
    return b == 0 ? a : gcd(b,a%b);
}

bool check_coprime_array(const vector<int>& a){
    int n = a.size();
    for (int i=0;i<n;++i){
        for (int j=i+1;j<n;++j){
            if (gcd(a[i],a[j]) != 1)    return false;
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
    // long long x,y,m;
    // cin >> x >> y >> m;
    // cout << "Kiem tra cong thuc:\n";
    // cout << "(x+y)%m = (x%m + y%m)%m => " << (check_add(x,y,m) ? "Dung" : "Sai") << '\n';
    // cout << "(x-y)%m = (x%m - y%m)%m => " << (check_minus(x,y,m) ? "Dung" : "Sai") << '\n';
    // cout << "(x*y)%m = (x%m * y%m)%m => " << (check_multiply(x,y,m) ? "Dung" : "Sai") << '\n';
    // cout << "(x^y)%m = [(x%m)^y]%m => " << (check_power(x,y,m) ? "Dung" : "Sai. Co the do tran so") << '\n';

    // cout << "Tinh nghich dao modulo cua x bang nhieu phuong phap\n";
    // int tmp1,tmp2;
    // int g = extended_euclid(x,m,tmp1,tmp2);
    // if (g==1){
    //     cout << "Thuat toan Euclid mo rong: " << inv(x,m) << '\n';
    //     cout << "Phuong phap dinh ly Euler: " << euler_inv(x,m) << '\n';
        
    //     cout << "2 phuong phap duoi day yeu cau m phai la so nguyen to:\n"; 
    //     cout << "Phuong phap phep chia Euclid: " << euclid_inv(x,m) << '\n';
    //     cout << "Phuong phap dinh ly Fermat nho: " << fermat_inv(x,m) << '\n';
    // }
    // else cout << "Khong ton tai nghich dao modulo " << m << " cho x = " << x << '\n';
    chinese_reminder_problem();
    return 0;
}