/*
    给定n、k，n可以变成n+1、n-1和2n
    问最少多少次变化，n变成k
*/
#include <stdio.h>
#include <deque>
#include <algorithm>
using namespace std;

int N,K;
bool read(){
    return EOF != scanf("%d%d",&N,&K);
}

deque<int> Q;
int D[200010];

int bfs(){
    int kk = 2 * K, m = K - N;
    Q.clear();
    fill(D,D+kk+1,-1);

    Q.push_back(N);
    D[N] = 0;

    int a,b,c;
    while( !Q.empty() ){
        int u = Q.front();
        Q.pop_front();

        if ( (a=u+1) == K || (b=u-1)==K || (c=2*u)==K ) return D[u]+1;
        
        if ( D[u] == m ) continue;

        if ( 0 <= a && a <= kk && -1 == D[a] ){
            D[a] = D[u] + 1;
            Q.push_back(a);
        }

        if ( 0 <= b && b <= kk && -1 == D[b] ){
            D[b] = D[u] + 1;
            Q.push_back(b);
        }

        if ( 0 <= c && c <= kk && -1 == D[c] ){
            D[c] = D[u] + 1;
            Q.push_back(c);
        }
    }
}
int main(){
    while( read() ){
        if ( N >= K ) printf("%d\n",N-K);
        else printf("%d\n",bfs());
    }
    return 0;
}
