#include <iostream>
#include <math.h>
#include <vector>
#include <string>
using namespace std;

string operator*(const string& a,const string& b){
    int n = a.size();
    int m = b.size();
    if (a=="0"||b=="0") return "0";
    vector<long long>vt(m+n,0);
    for (int i=n-1;i>=0;--i){
        for (int j=m-1;j>=0;--j){
            long long mul = (a[i]-'0')*(b[j]-'0');
            long long sum = mul+vt[i+j+1];
            vt[i+j+1] = sum%10;
            vt[i+j] += sum/10;
        }
    }
    string res = "";
    for (int x : vt){
        if (!res.empty() || x > 0) res += (x+'0');
    }
    return (res.empty() ? "0" : res);
}



long long power(long long a,long long n){
    long long res = 1;
    while (n>0){
        if (n%2!=0) res *= a;
        a *= a;
        n /= 2;
    }
    return res;
}

void factorize(long long n,vector<long long>& p,vector<long long>& a){
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
    int result = 1;
    for (int i=2;i<=sqr;++i){
        if (n%i==0){
            int cnt=0;
            while(n%i==0){
                cnt++;
                n/=i;
            }
            result *= (cnt+1);
        }
    }
    if (n>1)    result*=2;
    return result;
}

vector<long long> get_div_list(long long n){
    vector<long long>vt;
    long long sqr = sqrt(n);
    for (int i=1;i<=sqr;++i){
        if (n%i==0) vt.push_back(i);
    }
    int sz = vt.size();
    for (int i=sz-1;i>=0;--i){
        if (n/vt[i] != vt[i]) vt.push_back(n/vt[i]);
    }
    return vt;
}

long long div_sum1(long long n){
    vector<long long>divList = get_div_list(n);
    long long sum=0;
    for (int i=0;i<divList.size();++i){
        sum += divList[i];
    }
    return sum;
}

long long div_sum2(long long n){
    vector<long long>p,a;
    factorize(n,p,a);
    long long sum=1;
    int sz = p.size();
    for (int i=0;i<sz;++i){
        sum = sum*((power(p[i],a[i]+1)-1)/(p[i]-1));
    }
    return sum;
}

string div_product(long long n){
    vector<long long>divList = get_div_list(n);
    string result = "1";
    for (int i=0;i<divList.size();++i){
        result = result*to_string(divList[i]);
    }
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
    return n == div_sum2(n) - n;
}

long long estimate_primes(long long n){
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
    vector<long long>p,a;
    factorize(n,p,a);
    if (p.size() != a.size()){
        cout << "Error: Kich thuoc cua mang p va a khong giong nhau\n";
        exit(1);
    }
    int sz = p.size();
    cout << "Cau 1: \n";
    cout << "Phan tich thua so nguyen to cua " << n << " la: ";
    for (int i=0;i<sz;++i){
        cout << p[i] << "^" << a[i];
        if (i<sz-1) cout << " * ";
    }
    cout << "\nCau 2: \n";
    vector<long long>divList = get_div_list(n);
    long long divcount = div_count(n);
    cout << "So luong uoc cua " << n << " la: "<< divcount << '\n';
    cout << "Danh sach cac uoc cua " << n <<" la: ";
    for (int i=0;i<divList.size();++i){
        cout << divList[i] << ' ';
    }
    cout << "\nCau 3: \n";
    cout << "Tong cua cac uoc so cua " << n << " la: " << div_sum1(n) << '\n';
    cout << "Cau 4: \n";
    string divproduct = div_product(n);
    cout << "Tich cua cac uoc so la: "  << n << " la: " << divproduct  << '\n';
    cout << "Cau 5: \n";
    cout << "Ham check "<< n <<" co phai la so hoan hao truyen thong: " << (old_check_perfect(n) ? "YES\n" : "NO\n");
    cout << "Ham check "<< n <<" co phai la so hoan hao truyen thong: " << (new_check_perfect(n) ? "YES\n" : "NO\n");
    cout << "Nhap L va R de tinh so luong so hoan hao trong doan [L,R]\n";
    long long l,r;
    cin >> l >> r;
    cout << "Danh sach so hoan hao trong doan [" << l <<","<< r <<"] la: ";
    for (int i=l;i<=r;++i){
        if (old_check_perfect(i)==true){
            cout << i << ' ';
        }
    }
    cout << "\nCau 6: \n";
    cout << "Mat do so nguyen to tu 1->" << n << " la: " << estimate_primes(n) << '\n';
    vector<int>primes = get_primes(l,r);
    cout << "Danh sach so nguyen to trong doan [" << l <<","<< r <<"] la: \n";
    for (int i=0;i<primes.size();++i){
        cout << primes[i] << ' ';
    }
    return 0;
}
