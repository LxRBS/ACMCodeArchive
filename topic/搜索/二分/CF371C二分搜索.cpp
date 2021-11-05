/*
    做一个汉堡包需要若干个B、S、C
    现有B/S/C的数量
    再给定B/S/C的单价，可以使用这个价格去购买
    再给定现在拥有的钱
    问最多能做几个汉堡
*/
#include <stdio.h>
#include <iostream>
using namespace std;
typedef long long llt;

char T[110];
int Nb,Ns,Nc,Pb,Ps,Pc;
int Cb,Cs,Cc;//一个汉堡包含的各材料的数量
llt Money;
bool read(){
    if ( ! (cin>>T>>Nb>>Ns>>Nc>>Pb>>Ps>>Pc>>Money) ) return false;

    Cb = Cs = Cc = 0;
    for(char*p=T;*p;++p)if('B'==*p)++Cb;else if('S'==*p)++Cs;else++Cc;
    return true;
}

//检查是否能做出m个汉堡
bool check(llt m){
    llt a = ( m * Cb - Nb ) * Pb;
    if ( a < 0 ) a = 0LL;
    llt b = ( m * Cs - Ns ) * Ps;
    if ( b < 0 ) b = 0LL;
    llt c = ( m * Cc - Nc ) * Pc;
    if ( c < 0 ) c = 0LL;
    return Money >= a + b + c;
}

llt proc(){
    llt mid,left = 0LL, right = 1000000000000LL+100LL;
    
    //可行解从小到大，需求取最大解
    //则判断条件为本身，最后答案为right
    do{
        mid = ( left + right ) >> 1;
        if ( check(mid) ) left = mid + 1;
        else right = mid - 1;
    }while( left <= right );
    return right;
}
int main(){
    //freopen("1.txt","r",stdin);
    while( read() ) cout<<proc()<<endl;
    return 0;
}
