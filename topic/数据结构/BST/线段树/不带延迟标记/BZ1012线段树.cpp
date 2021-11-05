#include <cstdio>
#include <climits>
#include <algorithm>
using namespace std;

typedef int value_t;

int const SIZE = 200010;

inline int lson(int t){return t<<1;}
inline int rson(int t){return lson(t)|1;}

value_t ST[SIZE<<2];

//implement f according problems
inline void _pushUp(int t){
    ST[t] = max(ST[lson(t)],ST[rson(t)]);
}

void modify(int t,int s,int e,int idx,value_t delta){
    if ( s == e ){
        ST[t] += delta;
        return;
    }

    int m = ( s + e ) >> 1;
    if ( idx <= m ) modify(lson(t),s,m,idx,delta);
    else modify(rson(t),m+1,e,idx,delta);
    _pushUp(t);
}

value_t query(int t,int s,int e,int a,int b){
    if ( a <= s && e <= b ){
        return ST[t];
    }

    int m = ( s + e ) >> 1;
    value_t ret = INT_MIN;
    if ( a <= m ) ret = max(ret,query(lson(t),s,m,a,b));
    if ( m < b ) ret = max(ret,query(rson(t),m+1,e,a,b));
    return ret;
}

int M,D;
int main(){
    //freopen("1.txt","r",stdin);
    scanf("%d%d",&M,&D);
    fill(ST,ST+(M<<2)+1,0);

    int t = 0;
    int cnt = 0;
    for(int kase=0;kase<M;++kase){
        char cmd[3];
        int n;
        scanf("%s%d",cmd,&n);

        if ( 'A' == *cmd ){
            n = ( n + t ) % D;
            modify(1,1,M,++cnt,n);
        }else{
            t = query(1,1,M,cnt-n+1,cnt);
            printf("%d\n",t);
        }
    }
}

