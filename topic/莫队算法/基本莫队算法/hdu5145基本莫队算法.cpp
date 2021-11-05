#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long int llt;
typedef llt int_t;

int const SIZE = 30002;
int const BLOCK_SIZE = 200;

llt const MOD = 1000000007LL;
llt Inv[SIZE] = {0LL};

//The extended Euclidean algorithm implemented by iteration
//returns gcd(a,b), and x, y are satisfied with ax + by = gcd
int_t exEuclid(int_t a,int_t b,int_t&x,int_t&y){
    int_t x0 = 1, y0 = 0;
    int_t x1 = 0, y1 = 1;
    x = 0; y = 1;
    int_t r = a % b;
    int_t q = ( a - r ) / b;
    while( r ){
        x = x0 - q * x1;
        y = y0 - q * y1;
        x0 = x1; y0 = y1;
        x1 = x; y1 = y;
        a = b; b = r; r = a % b;
        q = ( a - r ) / b;
    }
    return b;
}

//returns the inverse of a mod p satisfied with 1 == ax%p
//it will be success only when a and p are co-prime
int_t inv(int_t a,int_t p){
    int_t x,y;
    int_t r = exEuclid(a,p,x,y);
    if ( r != 1 ) return 0;
    x = x % p;
    if ( x < 0 ) x += p;
    return x;
}

struct _t{
    int s,e;
    int idx;
};

bool operator  < (_t const&lhs,_t const&rhs){
    int ln = lhs.s / BLOCK_SIZE;
    int rn = rhs.s / BLOCK_SIZE;
    return ln < rn || ( ln == rn && lhs.e < rhs.e );
}

int N,M;
int A[SIZE];
_t B[SIZE];
llt Ans[SIZE],Cnt[SIZE];

llt MoAns;
llt TotalCnt;
inline void insert(int n){
    MoAns = MoAns * ++TotalCnt % MOD * Inv[++Cnt[n]] % MOD;
}

inline void remove(int n){
    MoAns = MoAns * Cnt[n]-- % MOD * Inv[TotalCnt--] % MOD;
}

void Mo(){
    sort(B,B+M);
    fill(Cnt,Cnt+SIZE+1,0);

    int curLeft = 1;
    int curRight = 0;
    MoAns = 1LL;
    TotalCnt = 0LL;

    for(int i=0;i<M;++i){
        while( curRight < B[i].e  ) insert(A[++curRight]);
        while( curLeft > B[i].s ) insert(A[--curLeft]);
        while( curRight > B[i].e ) remove(A[curRight--]);
        while( curLeft < B[i].s ) remove(A[curLeft++]);
        Ans[B[i].idx] = MoAns;
    }
}

int getUnsigned(){
	char ch = getchar();
	while( ch > '9' || ch < '0' ) ch = getchar();

	int ret = 0;
	do ret = ret * 10 + (int)(ch-'0');while( '0' <= (ch=getchar()) && ch <= '9' );
	return ret;
}

void read(){
    N = getUnsigned();
    M = getUnsigned();

    for(int i=1;i<=N;++i) A[i] = getUnsigned();

    for(int i=0;i<M;++i){
        B[i].s = getUnsigned();
        B[i].e = getUnsigned();
        B[i].idx = i;
    }
}
int main(){
    //freopen("1.txt","r",stdin);
    for(int i=1;i<SIZE;++i) if( Inv[i] == 0LL ) Inv[i] = inv(i,MOD);

    int nofkase = getUnsigned();
    while(nofkase--){
        read();
        Mo();
        for(int i=0;i<M;++i)printf("%lld\n",Ans[i]);
    }
    return 0;
}

