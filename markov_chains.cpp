#include <iostream>

using namespace std;

class matrix{
    public:
        int n,m;
        double** a;
        matrix(int n=3,int m=3){
            this->a = new double*[n+1];
            for (int i=1;i<=m;++i){
                this->a[i] = new double[m+1];
            }
            this->n=n;
            this->m=m;
        }
        matrix(const matrix& o){
            this->n = o.n;
            this->m = o.m;
            
        }
}

int main(){

}