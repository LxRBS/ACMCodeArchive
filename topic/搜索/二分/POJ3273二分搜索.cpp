/*
    长度为N的序列
    划分为M个子段
    要求最大子段和尽可能小
*/
#include <stdio.h>
#include <algorithm>
#include <iostream>
using namespace std;
typedef long long llt;

int N,M;
int A[100010];
int Mmax;
llt  Total;
bool read(){
    if ( !(cin>>N>>M) ) return false;
    Total = Mmax = 0LL;
    for(int i=0;i<N;++i)cin>>A[i], Total += A[i], Mmax = max(Mmax,A[i]);
    return true;
}

//检查子段和能否做到m以下
bool check(llt m){
    int i = 0, cnt = 0;
    while(1){
        llt tmp = 0LL;
        int k = 0;
        while( i+k<N && tmp <= m ) tmp += A[i+k], ++k;

        if ( i + k == N && tmp <= m ) return true;

        if ( 1 == k ) return false;

        i += k - 1;
        ++cnt;
        if ( cnt > M || ( M == cnt && i < N ) ) return false;
    }
}

llt proc(){
    llt mid,left = max((llt)Mmax,Total / M), right = Total;
    //可行解从大到小，需求取最小解
    //最后答案为left
    do{
        mid = ( left + right ) >> 1;
        if ( check(mid) ) right = mid - 1;
        else left = mid + 1;
    }while( left <= right );
    return left;
}
int main(){
    //freopen("1.txt","r",stdin);
    while( read() ) cout<<proc()<<endl;
    return 0;
}
