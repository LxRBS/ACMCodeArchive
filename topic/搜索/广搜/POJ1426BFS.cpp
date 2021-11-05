/*
    给定n，找n的倍数m
    使得m均由0/1组成
    
    实际上不会超过longlong范围，所以很简单
    但是C++超时，G++AC
*/
#include <stdio.h>
#include <queue>
#include <algorithm>
using namespace std;

int N;
long long bfs(){
    if ( 1 == N ) return 1LL;

    queue<long long> q;
    q.push(1LL);

    long long u,v;
    while( !q.empty() ){
        u = q.front();
        q.pop();

        if ( (v = u * 10) % N == 0 ) return v;
        q.push(v);

        if ( ++v % N == 0 ) return v;
        q.push(v);
    }
}

int main(){
    while( scanf("%d",&N),N ){
        printf("%lld\n",bfs());
    }
    return 0;
}
