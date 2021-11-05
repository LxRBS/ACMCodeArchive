//×´Ì¬Ñ¹Ëõ
#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>
using namespace std;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

struct _t{
    char a[110];
    int d;
    int c;
}A[17];
bool operator < (_t const&lhs,_t const&rhs){
    return lhs.d < rhs.d || ( lhs.d == rhs.d && lhs.c > rhs.c ) ||
        ( lhs.d == rhs.d && lhs.c == rhs.c && strcmp(lhs.a,rhs.a) < 0 );
}

int N;
void read(){
    N = getUnsigned();
    for(int i=0;i<N;++i){
        scanf("%s",A[i].a);
        A[i].d = getUnsigned();
        A[i].c = getUnsigned();
    }
}

int calc(int status){
    int ret = 0;
    for(int i=0;i<N;++i){
        if ( status & ( 1 << i ) ) ret += A[i].c;
    }
    return ret;
}

int D[1<<15];
int C[1<<15];
int Pre[1<<15];
int dp(int status){
    if ( INT_MAX != D[status] ) return D[status];

    int ret = INT_MAX;
    for(int i=0;i<N;++i){
        if ( 0 == ( status & ( 1 << i ) ) ) continue;

        int st = status ^ ( 1 << i );
        int x = C[st] + A[i].c - A[i].d;
        if ( x < 0 ) x = 0;
        x += dp(st);
        if ( x < ret || ( x == ret && 0 < strcmp(A[i].a,A[Pre[status]].a) ) ) ret = x, Pre[status] = i;
    }
    return D[status] = ret;
}

void output(int status){
    if ( status != 0 ){
        int i = Pre[status];
        output(status^(1<<i));
        printf("%s\n",A[i].a);
    }
}

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase = getUnsigned();
    while( nofkase-- ){
        read();

        fill(D,D+(1<<N),INT_MAX);
        D[0] = 0;
        for(int i=0;i<(1<<N);++i){
            C[i] = calc(i);
        }

        printf("%d\n",dp((1<<N)-1));
        output((1<<N)-1);
    }
    return 0;
}
