#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <string>
#include <bitset>

using namespace std;
#define ll long long
#define ld long double
#define ii pair<ll,ll>
#define iii pair<ll,ii>
#define iiii pair<ii,ii>
#define pb push_back 
#define fi first 
#define se second 
#define log(a,b) ln(b)/ln(a)
#define deb(x) cout << #x << " = " << x << '\n'

const ll MOD = 1e9+7;
const ll inf = 1e9+7;
const ll N = 1e6+5;
const ll BASE = 31;

template <typename T,typename U>
ostream& operator<<(ostream& os,const pair<T,U>& x){ //  operator<< for pair
    os << '(' << x.fi << ',' << x.se << ')';
    return os;
}

int lg2(const ll& x){return (x<=0 ? -1:63 - __builtin_clzll(x));}
ll gcd(ll a,ll b){if (b==0) return a;return gcd(b,a%b);}
ll lcm(ll a,ll b){return (a/gcd(a,b))*b;}
ll tonum(const string& s){ll num=0;for (const char& x : s){if (x<'0'||x>'9') return -1;num = num*10 + x-'0';}return num;}
void fill(ll a[],int  n,ll num){for (int i=0;i<=n;++i) a[i] = num;}
bool betw(ll u,ll L,ll R){return (u>=L&&u<=R);}

// bits manipulation
void On(ll& n,const int& i){
    n |= (1LL<<i);
}
void Off(ll& n,const int& i){
    n &= ~(1LL<<i);
}

void Flip(ll& n,const int& i){
    n ^= (1LL<<i);
}
bool Get(const ll& n,const int& i){
    return n & (1LL<<i);
}
void print(const ll& n){ // Print binary of a number
    if (n>1) print(n>>1);
    cout << (n&1);
}

template <typename T>void setmax(T& x,const T& y){if(x<y)x=y;}
template <typename T>void setmin(T& x,const T& y){if(x>y)x=y;}
template <typename T> void print(const vector<T>& v){cout << "[";   int n = v.size()-1;for (const T& x : v){cout << x;  if (n>0)   cout << ',',n--;}cout << "]\n";}
// Print a elements of array in [L,R]
template <typename T> void print(T a[],int L,int R){cout << '[';for (int i=L;i<=R;++i){cout << a[i];if (i<R) cout << ',';}cout << ']';}

void file(const string& PATH){
    freopen((PATH+".inp").c_str(),"r",stdin);
    freopen((PATH+".out").c_str(),"w",stdout);
}
/*
    31 -> 3131 = 31*100 + 31 = 31*(100+1) = 31*101
    313131 = 31 * 10000 + 31 * 100 + 31 = 31*(10101)
    11 = 1*10 + 1 = 1*11
    111 = 1 * 100 + 1*10 + 1 = 1*(111)
    x(d,k) = x*10^kd + x
*/
bool isPrime(ll n){
    if (n<=1)   return 0;
    for (ll i=2;i*i<=n;++i){
        if (n%i==0) return 0;
    }
    return 1;
}

ll n,k;
void solve(){
    cin >> n >> k;
    if (k==1&&isPrime(n)){
        cout << "YES\n";
        return;
    }
    if (n==1&&k==2){
        cout << "YES\n";
        return;
    }
    cout << "NO\n";
}

int main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    ll t = 1;
    cin >> t;
    for (int i = 1;i <= t;++i){
        solve();
    }
    return 0;
}
