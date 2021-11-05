#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long llt;

llt gcd(llt a,llt b){
    while( b ){
        llt r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int const SIZE = 50300;
int const BLOCK_SIZE = 250;
int N,M;
int A[SIZE];
int Cnt[SIZE] = {0};

struct{
    llt a;
    llt b;
    void f(){llt g=gcd(a,b);a/=g;b/=g;}
}Ans[SIZE];

struct _t{
    int s,e;
    int idx;
}B[SIZE];

bool operator < (_t const&lhs,_t const&rhs){
    int lb = lhs.s / BLOCK_SIZE;
    int rb = rhs.s / BLOCK_SIZE;
    return lb < rb || ( lb == rb && lhs.e < rhs.e );
}

bool read(){
    scanf("%d%d",&N,&M);
    for(int i=1;i<=N;++i)scanf("%d",A+i);

    for(int i=0;i<M;++i){
        scanf("%d%d",&B[i].s,&B[i].e);
        B[i].idx = i;
    }
    return true;
}

llt MoAns = 0LL;
inline void insert(int n){
    MoAns += Cnt[n]++;
}

inline void remove(int n){
    MoAns -= --Cnt[n];
}

void Mo(){
    sort(B,B+M);

    int curLeft = 1;
    int curRight = 0;
    MoAns = 0;

    for(int i=0;i<M;++i){
        while( curRight < B[i].e ) insert(A[++curRight]);
        while( curLeft > B[i].s ) insert(A[--curLeft]);
        while( curRight > B[i].e ) remove(A[curRight--]);
        while( curLeft < B[i].s ) remove(A[curLeft++]);
        Ans[B[i].idx].a = MoAns;
        Ans[B[i].idx].b = ( curRight - curLeft + 1LL ) * ( curRight - curLeft ) >> 1;
        Ans[B[i].idx].f();
    }
}

int main(){
    //freopen("1.txt","r",stdin);
    read();
    Mo();
    for(int i=0;i<M;++i){
        printf("%lld/%lld\n",Ans[i].a,Ans[i].b);
    }
    return 0;
}
