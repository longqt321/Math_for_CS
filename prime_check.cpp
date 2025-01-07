#include <iostream>
#include <math.h>

using namespace std;
int idx=0;

bool check(long long n){
    if (n<=1)   return false;
    if (n==2||n==3) return true;
    if (n%2==0||n%3==0) return false;
    long long sqr = sqrt(n);
    for (int i=5;i<=sqr;i+=6){
        if (n%i==0 || n%(i+2)==0)   return false;
    }
    return true;
}

int main(){
    long long n;
    cin >> n;
    cout << check(n);
    return 0;
}