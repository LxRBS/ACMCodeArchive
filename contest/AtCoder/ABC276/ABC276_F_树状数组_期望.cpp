/**
 * ��������ΪN������A����A[1...i]�ȸ����ظ�����������������x��y
 * ��max(x, y)������
 * ��Ҫ��ÿһ��i=1,2,...,N���ش��������⣬���һ����N����
 * ���м�����ģ������
 * ����ǰi������Ei=SS{max(Ax, Ay)}/(i*i)
 * ��Di=SS{max(Ax, Ay)}�����Է���Di�����������
 * Di = D[i-1] + A[i] + 2 * (c * A[i] + s)
 * ����c��A[1...i-1]��С�ڵ���Ai������������s�Ǹ������д���Ai������Ԫ��֮��
 * c��s�ֱ���������״����ά������
 */
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
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
#else
int const SIZE = 2E5+13;
#endif

using llt = long long int;
llt const MOD = 998244353LL;

llt powerMod(llt a,llt n,llt mod){
    llt ret = 1;
    a %= mod;

    while( n ){
        if ( n & 1 ) ret = ret * a % mod;
        n >>= 1;
        a = a * a % mod;
    }
    return ret;
}


inline llt inv(llt a){return powerMod(a, MOD-2, MOD);}

inline llt add(llt a, llt b){return (a+b)%MOD;}
inline llt add(llt a, llt b, llt c){return (a+b+c)%MOD;}
inline llt mul(llt a, llt b){return a*b%MOD;}


struct Bit{

int _n;
llt c[SIZE];

void init(int n){this->_n = n; fill(this->c, this->c+n+1, 0LL);}

void modify(int pos, llt delta){
    for(int i=pos;i<=this->_n;i+=lowbit(i)) this->c[i] += delta;
}

llt query(int pos){
    llt ans = 0;
    for(int i=pos;i;i-=lowbit(i)) ans += this->c[i];
    return ans;
}

llt query(int s, int e){return this->query(e) - this->query(s-1);}

static int lowbit(int x){return x & -x;}

};

int N;
llt A[SIZE];
llt D[SIZE];

Bit U, V;

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r" ,stdin);
#endif
    N = getInt();
    llt maxv = 0;
    for(int i=1;i<=N;++i) maxv = max(maxv, A[i] = getInt());

    U.init(maxv);
    V.init(maxv);

    printf("%lld\n", D[1] = A[1]);
    U.modify(A[1], 1);
    V.modify(A[1], A[1]);
    
    for(int i=2;i<=N;++i){
        llt c = U.query(A[i]); // С�ڵ���Ai������
        llt s = V.query(A[i]+1, maxv); // ���ڵ���Ai��������֮��
        D[i] = mul(2LL, add(mul(c, A[i]), s));
        D[i] = add(D[i], A[i], D[i-1]);
        llt ans = mul(D[i], inv(mul(i, i)));
        printf("%lld\n", ans);
        U.modify(A[i], 1);
        V.modify(A[i], A[i]);
    }
    return 0;
}