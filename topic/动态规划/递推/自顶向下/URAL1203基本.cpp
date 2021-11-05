/*
    N个报告，每个报告有起始时间
    问最多能听多少场
*/
#include <cstdio>
#include <set>
#include <functional>
#include <algorithm>
using namespace std;

int N;
set<int> V[30001];
int Dp[30001] = {0,0};
int dp(int e){
    if ( -1 != Dp[e] ) return Dp[e];

    if ( V[e].empty() ){
        int first = e - 1;
        while( first && V[first].empty() ) --first;
        int t = dp(first);
        for(int i=first+1;i<=e;++i) Dp[i] = t;
        return t;
    }

    int ret = 0;
    set<int>::iterator it=V[e].begin();
    for(;it!=V[e].end();++it){
        int t = dp(*it-1) + 1;
        if ( ret < t ) ret = t;
    }

    --it;
    for(int i=*it;i<e;++i){
        int t = dp(i);
        if ( ret < t ) ret = t;
    }
    return Dp[e] = ret;
}

bool read(){
    if ( EOF == scanf("%d",&N) ) return false;

    for_each(V+1,V+30001,mem_fn(set<int>::clear));
    int last = 0;
    for(int i=0;i<N;++i){
        int s,e;
        scanf("%d%d",&s,&e);
        V[e].insert(s);
        if ( last < e ) last = e;
    }

    fill(Dp+2,Dp+last+1,-1);
    printf("%d\n",dp(last));
    return true;
}
int main(){
    //freopen("1.txt","r",stdin);
    while( read() );
    return 0;
}

