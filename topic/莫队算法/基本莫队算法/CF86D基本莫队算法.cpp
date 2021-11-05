#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long int llt;

int const SIZE = 200100;
int const BLOCK_SIZE = 450;

struct _t{
    int s,e;
    int idx;
};

bool operator  < (_t const&lhs,_t const&rhs){
    int ln = lhs.s / BLOCK_SIZE;
    int rn = rhs.s / BLOCK_SIZE;
    return ln < rn || ( ln == rn && lhs.e < rhs.e );
}

int N,Q;
int A[SIZE];
_t B[SIZE];
llt Cnt[1001000] = {0LL};
llt Ans[SIZE];

bool read(){
    if ( EOF == scanf("%d%d",&N,&Q) ) return false;
    for(int i=1;i<=N;++i)scanf("%d",A+i);

    for(int i=0;i<Q;++i){
        scanf("%d%d",&B[i].s,&B[i].e);
        B[i].idx = i;
    }

    fill(Cnt,Cnt+1001000,0LL);
    return true;
}

llt MoAns;
inline void insert(int n){
    llt &a = ++Cnt[n];
    MoAns += ( a << 1 ) * n - n;
}

inline void remove(int n){
    llt & a = -- Cnt[n];
    MoAns -= ( a << 1 ) * n + n;
}

void Mo(){
    sort(B,B+Q);

    int curLeft = 1;
    int curRight = 0;
    MoAns = 0LL;

    for(int i=0;i<Q;++i){
        while( curRight < B[i].e  ) insert(A[++curRight]);
        while( curLeft > B[i].s ) insert(A[--curLeft]);
        while( curRight > B[i].e ) remove(A[curRight--]);
        while( curLeft < B[i].s ) remove(A[curLeft++]);
        Ans[B[i].idx] = MoAns;
    }
}

int main(){
    //freopen("1.txt","r",stdin);
    read();
    Mo();
    for(int i=0;i<Q;++i) printf("%I64d\n",Ans[i]);

    return 0;
}

