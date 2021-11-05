/*
    计算调和级数 Hn = SIGMA(1/i)
    有公式
    GAMMA = 0.57721566490153286060651209008240243104215933593992
    GAMMA = Hn - ln(n) - 1/(2n),当n趋近于无穷大
*/
#include <stdio.h>
#include <math.h>
#include <iomanip>
#include <iostream>
using namespace std;

typedef long long llt;
typedef long double ldt;

ldt const GAMMA = 0.57721566490153286060651209008240243104215933593992L;
int const SIZE = 1500000;
ldt H[SIZE] = {0.0,1.0};

int main(){
    //freopen("1.txt","r",stdin);
    for(int i=2;i<SIZE;++i) H[i] = H[i-1] + 1.0/i;

    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        llt n;
        scanf("%lld",&n);
        cout<<"Case "<<kase<<": "<<fixed<<setprecision(18)<<(n<SIZE?H[n]:log((ldt)n)+GAMMA+0.5/n)<<endl;
    }
    return 0;
}