//给定区间[a,b]，求约数个数最多的数
//算术基本定理，然后求约数的个数
#include <iostream>
#include <math.h>
using namespace std;


//线性筛法
int const SIZE = sqrt(1E9) + 2;//一般只筛到30000+即可
bool isComp[SIZE] = {false};//isComp[i]为真说明i是合数
int P[SIZE];//P[i]为第i个素数，i从0开始
int PCnt = 0;//PCnt记录1~SIZE之间的素数的个数
void sieve(){
    for(int i=2;i<SIZE;++i){
        if ( !isComp[i] ) P[PCnt++] = i;

        for(int j=0;j<PCnt&&i*P[j]<SIZE;++j){
            isComp[i*P[j]] = true;
            if ( 0 == i % P[j] ) break;
        }
    }
}

int proc(int n){
    int r = 1;
    for(int i=0;i<PCnt&&P[i]*P[i]<=n;++i){
        if ( n % P[i] ) continue;

        int k = 0;
        while( 0 == n % P[i] ) n /= P[i], ++k;
        r *= 1 + k;
    }
    if ( 1 != n ) r *= 2;
    return r;
}

void proc(int a,int b,int&n,int&k){
    k = 0;
    int t;
    for(int i=a;i<=b;++i){
        t = proc(i);
        if ( k < t ) n = i, k = t;
    }
}

int main(){
    sieve();

    int kase,a,b,n,k;
    cin>>kase;
    while(kase--){
        cin>>a>>b;
        proc(a,b,n,k);
        cout<<"Between "<<a<<" and "<<b<<", "<<n<<" has a maximum of "<<k<<" divisors."<<endl;
    }
}
