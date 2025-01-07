#include <iostream>
#include <math.h>

using namespace std;
int idx=0;

int divcount(long long n,int* a){
    long long sqr = sqrt(n);
    int cnt = 0;
    for (int i=1;i<=sqr;++i){
        if (n%i==0){
            a[++idx] = i;
            if (n/i==i) cnt++;
            else cnt+=2;
        }
    }
    int tmp = idx;
    for (int i=tmp;i>=1;--i){
        if (n/a[i] != a[i]){
            a[++idx] = n/a[i];
        }
    }
    return cnt;
}

int main(){
    long long n;
    int* a = new int[1003];
    cin >> n;
    cout << "So luong uoc so cua n: " << divcount(n,a) << '\n';
    cout << "Liet ke uoc so: ";
    for (int i=1;i<=idx;++i){
        cout << a[i] << ' ';
    }
    return 0;
}