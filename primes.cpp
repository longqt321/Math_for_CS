#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

long long power(long long a,long long n){
    long long res = 1;
    while (n>0){
        if (n%2==1) res *= a;
        a *= a;
        n /= 2;
    }
    return res;
}

void factorize(long long n,vector<int>& p,vector<int>& a){
    long long sqr = sqrt(n);
    for (int i=2;i<=sqr;++i){
        if (n%i==0){
            p.push_back(i);
            a.push_back(0);
            while(n%i==0){
                a.back()++;
                n/=i;
            }
        }
    }
    if (n>1){
        p.push_back(n);
        a.push_back(1);
    }
}

int div_count(long long n){
    long long sqr = sqrt(n);
    int cnt = 0;
    for (int i=1;i<=sqr;++i){
        if (n%i==0){
            if (n/i==i) cnt++;
            else cnt+=2;
        }
    }
    return cnt;
}

vector<int> get_div_list(long long n){
    vector<int>vt;
    long long sqr = sqrt(n);
    for (int i=2;i<=sqr;++i){
        if (n%i==0) vt.push_back(i);
    }
    int sz = vt.size();
    for (int i=sz-1;i>=0;--i){
        if (n/vt[i] != vt[i]) vt.push_back(n/vt[i]);
    }
    return vt;
}

long long div_sum(long long n){
    vector<int>p,a;
    factorize(n,p,a);
    long long sum=1;
    int sz = p.size();
    for (int i=0;i<sz;++i){
        sum = sum*((power(p[i],a[i]+1)-1)/(p[i]-1));
    }
    return sum;
}

long long div_product(long long n){
    int divcount = div_count(n);
    long long result = power(n,div_count(n)/2);
    if (divcount%2!=0) result *= sqrt(n);
    return result;
}

bool old_check_perfect(long long n){
    long long sum = 1;
    long long sqr = sqrt(n);
    for (int i=2;i<=sqr;++i){
        if (n%i==0){
            if (n/i==i) sum += i;
            else sum += (i+ n/i);
        }
    }
    return n == sum;
}

bool new_check_perfect(long long n){
    return n == div_sum(n) - n;
}

int estimate_primes(long long n){
    return n/log(n);
}

vector<int> get_primes(long long l,long long r){
    vector<bool>E (r+1,true);
    E[0] = E[1] = false;
    long long sqr=sqrt(r);
    for (int i=2;i<=sqr;++i){
        if (E[i]==true){
            for (int j=i*i;j<=r;j+=i){
                E[j] = false;
            }
        }
    }
    vector<int>primes;
    for (int i=l;i<=r;++i){
        if (E[i]==true) primes.push_back(i);
    }
    return primes;
}

int main(){
    long long n;
    cout << "Nhap n: ";
    cin >> n;
    vector<int>p,a;
    factorize(n,p,a);
    if (p.size() != a.size()){
        cout << "Error:\n";
        exit(1);
    }
    int sz = p.size();
    cout << "Cau 1: \n";
    cout << "Phan tich thua so nguyen to cua n: ";
    for (int i=0;i<sz;++i){
        cout << p[i] << "^" << a[i];
        if (i<sz-1) cout << " * ";
    }
    cout << "\nCau 2: \n";
    vector<int>divList = get_div_list(n);
    long long divcount = div_count(n);
    cout << "Tong so uoc cua n: " << divcount << '\n';
    cout << "Danh sach cac uoc cua n: ";
    for (int i=0;i<divList.size();++i){
        cout << divList[i] << ' ';
    }
    cout << "\nCau 3: \n";
    cout << "Tong cua cac uoc so la: " << div_sum(n) << '\n';
    cout << "Cau 4: \n";
    long long divproduct = div_product(n);
    cout << "Tich cua cac uoc so la: " << divproduct  << '\n';
    cout << "Cau 5: \n";
    cout << "Ham check so hoan hao truyen thong: " << (old_check_perfect(n) ? "YES\n" : "NO\n");
    cout << "Ham check so hoan hao theo cong thuc: " << (new_check_perfect(n) ? "YES\n" : "NO\n");
    cout << "Nhap L va R de tinh so luong so hoan hao tron doan [L,R]\n";
    long long l,r;
    cin >> l >> r;
    cout << "Danh sach so hoan hao trong doan [L,R] la: ";
    for (int i=l;i<=r;++i){
        if (old_check_perfect(i)==true){
            cout << i << ' ';
        }
    }
    cout << "\nCau 6: \n";
    cout << "Mat do so nguyen to tu 1->N la: " << estimate_primes(n) << '\n';
    vector<int>primes = get_primes(l,r);
    cout << "Danh sach so nguyen to tu L->R la: \n";
    for (int i=0;i<primes.size();++i){
        cout << primes[i] << ' ';
    }
    return 0;
}
