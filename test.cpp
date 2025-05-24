#include <iostream>

using namespace std;

int maxDiv(int n){
    int res = 1;
    for (int i=2;i*i<=n;++i){
        if (n%i==0){
            res = max(res,i);
            while(n%i==0) n/=i;
        }
    }
    if (n>1)    res = max(res,n);
    return res;
}

bool isPerfect(long long n){
    if (n<=1) return false;
    long long sum=1;
    for (int i=2;i*i<=n;++i){
        if(n%i==0){
            if (n/i==i) sum+=i;
            else sum += (i+n/i);
        }
    }
    return sum==n;
}

int perfectCount(int n){
    int dem =0;
    for (int i=1;i<=n;++i){
        if (isPerfect(i))   dem++;
    }
    return dem;
}

void printPerfects(int n){
    for (int i=1;i<n;++i){
        if (isPerfect(i)){
            cout << i << ' ';
        }
    }
    cout << '\n';
}

int sumPerfect(int n){
    int sum=0;
    for (int i=1;i<n;++i){
        if (isPerfect(i))   sum += i;
    }
    return sum;
}

bool isPrime(int n){
    if (n<=1)   return false;
    for (int i=2;i*i<=n;++i){
        if (n%i==0) return false;
    }
    return true;
}

int primeCount(int n){
    int dem=0;
    for (int i=1;i<n;++i){
        if (isPrime(i)) dem++;
    }
    return dem;
}

void printPrimes(int n){
    for (int i=1;i<n;++i){
        if (isPrime(i)){
            cout << i << ' ';
        }
    }
    cout << '\n';
}

int sumPrimes(int n){
    int sum=0;
    for (int i=1;i<n;++i){
        if (isPrime(i)) sum += i;
    }
    return sum;
}

int main(){
    int n = 97700;
    int m = maxDiv(n);
    cout << "Uoc so nguyen to lon nhat cua " << n << " la: " << m << '\n';
    cout << "So luong cac so hoan hao tu 1->" << m << " la: " << perfectCount(m) << '\n';
    cout << "Cac so hoan hao tu 1->" << m << '\n';
    printPerfects(m);
    cout << "Tong cua cac so hoan hao tu 1->" << m << " la: " << sumPerfect(m) << '\n';

    cout << "So luong cac so nguyen to tu 1->" << m << " la: " << primeCount(m) << '\n';
    cout << "Cac so nguyen to tu 1->" << m << '\n';
    printPrimes(m);
    cout << "Tong cua cac so nguyen to tu 1->" << m << " la: " << sumPrimes(m);
    return 0;
}