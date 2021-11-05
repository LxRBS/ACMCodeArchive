/*
     给定公式n^2+n+41
     问区间[a,b]之间符合这个公式的质数一共有多少个
     输出百分比
*/
#include <stdio.h>
#include <cmath>
#include <sstream>
#include <algorithm>
using namespace std;

bool Flag[10010] = {false};
bool isPrime(int n){
    for(int i=2;i*i<=n;++i){
        if ( 0 == n % i ) return false;
    }
    return true;
}
inline int f(int n){return n*n+n+41;}
void init(){
    int n;
    for(int i=0;i<10010;++i){
        Flag[i] = isPrime(f(i));
    }
}
int main(){
    init();printf("%.32f\n",0.1);

    int a,b;
    while( 2 == scanf("%d%d",&a,&b) ){
        int ans = 0;
        for(int i=a;i<=b;++i)if(Flag[i])++ans;
        printf("%.2f\n",(double)ans*100.0/(double)(b-a+1)+1E-7);
    }
    return 0;
}







