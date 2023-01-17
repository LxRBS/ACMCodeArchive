/**
 * 一个数组，M个操作，每次操作：
 * 1 s e k, 对[s, e]范围内的Ai操作k次，每次令Ai = round(10 * sqrt(Ai))
 * 2, 求数组总和
 * 很显然，对每个Ai只要少数操作之后，后续操作就不起作用了。
 * 但是要注意Ai的不动点有3个：0, 99, 100。
 * 经典的线段树，但是分块也可以做。
 * 感觉分块的代码虽然比线段树少一点点点，但是优势也不明显。
 */
#include <bits/stdc++.h>
using namespace std;
 
char *__abc147, *__xyz258, __ma369[1000000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getInt(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}
 
	int ret = (int)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}
 
#ifndef ONLINE_JUDGE
int const SIZE = 23;
int const BLOCKSIZE = 3;
#else
int const SIZE = 100010;
int const BLOCKSIZE = 300;
#endif

using Real = long double;
using llt = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using prr = pair<Real, Real>;
using mvi = map<int, vi>;

int N, M;
llt A[SIZE];
int Lazy[SIZE];
int Block[SIZE];
llt Sum[SIZE] = {0};
llt Total;

void build(int n){
    for(int i=1;i<=n;++i){
        Block[i] = (i - 1) / BLOCKSIZE + 1;
        Sum[Block[i]] += A[i];
        Lazy[Block[i]] = 1;
        Total += A[i];
    }
}

void f(int pos, int k){
    auto & v = A[pos];
    while(k--){
        if(0 == v || 99 == v || 100 == v) break;
        auto tmp = (llt)(10.0 * sqrt(v) + 0.5);
        Total += tmp - v;
        v = tmp;
    }
}

void fblock(int bindex, int k){
    int s = (bindex - 1) * BLOCKSIZE + 1;
    int e = s + BLOCKSIZE - 1;
    bool flag = true;
    for(int i=s;i<=e;++i){
        f(i, k);
        if(A[i] != 0 && A[i] != 99 && A[i] != 100) flag = false;
    }
    if(flag) Lazy[bindex] = 0;
}

void modify(int s, int e, int k){
    int bs = Block[s], be = Block[e];
    if(Lazy[bs])for(int i=s,n=min(bs*BLOCKSIZE, e);i<=n;++i){
        f(i, k);
    }
    if(bs != be && Lazy[be])for(int i=(be-1)*BLOCKSIZE+1;i<=e;++i){
        f(i, k);
    }
    for(int i=bs+1;i<be;++i){
        if(0 == Lazy[i]) continue;
        fblock(i, k);
    }
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    N = getInt();
    M = getInt();
    for(int i=1;i<=N;++i) A[i] = getInt();
    build(N);

    for(int cmd,q=1;q<=M;++q){
        cmd = getInt();
        if(2 == cmd){
            printf("%lld\n", Total);
        }else{
            int a = getInt();
            int b = getInt();
            int k = getInt();
            modify(a, b, k);
        }
    }
    return 0;
}


