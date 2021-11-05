#include <cstdio>
#include <algorithm>
using namespace std;

int const SIZE = 30100;
int const BLOCK_SIZE = 200;

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
_t B[200010];
int Ans[200010];
int Cnt[1000010] = {0};

void read(){
    scanf("%d",&N);
    for(int i=1;i<=N;++i)scanf("%d",A+i);
    scanf("%d",&Q);
    for(int i=0;i<Q;++i){
        scanf("%d%d",&B[i].s,&B[i].e);
        B[i].idx = i;
    }
}

int MoAns;
inline void insert(int n){
    ++Cnt[n];
    if ( 1 == Cnt[n] ) ++MoAns;
}

inline void remove(int n){
    --Cnt[n];
    if ( 0 == Cnt[n] ) --MoAns;
}

void Mo(){
    sort(B,B+Q);

    int curLeft = 1;
    int curRight = 0;
    MoAns = 0;

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
    for(int i=0;i<Q;++i)printf("%d\n",Ans[i]);
    return 0;
}

