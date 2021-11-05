/**
 * 一共有3个数组，4种操作
 * 0 x s e: 查询数组x的[s, e]区间和
 * 1 x s e d: 数组x的[s, e]区间增加d
 * 2 x y s e: 数组x和数组y的[s, e]区间交换
 * 3 x y s e: 把数组x的[s, e]区间加到数组y的对应区间
 * 矩阵延迟
*/
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getUnsigned(){
	char ch = __hv007();
	while( ch < '0' || ch > '9' ) ch = __hv007();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = __hv007() ) && ch <= '9' ) ret = (ret<<1) + (ret<<3) + (int)(ch-'0');
	return ret;
}

typedef long long llt;
llt const MOD = 998244353LL;
#ifndef ONLINE_JUDGE
int const SIZE = 22;
#else
int const SIZE = 300010;
#endif

inline llt add(llt a, llt b){return (a+b)%MOD;}
inline llt dot(llt const a[], llt x, llt y, llt z, llt w){
	return (a[0]*x%MOD + a[1]*y%MOD + a[2]*z%MOD + a[3]*w%MOD) % MOD;
}

inline int lson(int t){return t<<1;}
inline int rson(int t){return lson(t)|1;}

llt ST[3][SIZE<<2];
typedef llt mat_t[3][4];
mat_t Lazy[SIZE<<2]; // Lazy是一个3×4的矩阵

inline void _pushUp(int t){
	for(int l=lson(t),r=rson(t),i=0;i<3;++i){
		ST[i][t] = add(ST[i][l], ST[i][r]);
	}
}

inline bool isI(const mat_t &lazy){
	return 1 == lazy[0][0] && 0 == lazy[0][1] && 0 == lazy[0][2] && 0 == lazy[0][3]
	    && 0 == lazy[1][0] && 1 == lazy[1][1] && 0 == lazy[1][2] && 0 == lazy[1][3]
		&& 0 == lazy[2][0] && 0 == lazy[2][1] && 1 == lazy[2][2] && 0 == lazy[2][3];
}

inline void mkI(mat_t &lazy){
	memset(lazy, 0, sizeof(lazy));
	lazy[0][0] = lazy[1][1] = lazy[2][2] = 1;
}

/// 根据lazy计算t的值
inline void _f(const mat_t &lazy, int t, int s, int e){
    llt a = dot(lazy[0], ST[0][t], ST[1][t], ST[2][t], e-s+1);
	llt b = dot(lazy[1], ST[0][t], ST[1][t], ST[2][t], e-s+1);
	llt c = dot(lazy[2], ST[0][t], ST[1][t], ST[2][t], e-s+1);

	ST[0][t] = a;
	ST[1][t] = b;
	ST[2][t] = c;

	llt tmp[3][4];
	for(int i=0;i<3;++i)for(int j=0;j<4;++j){
		tmp[i][j] = dot(lazy[i], Lazy[t][0][j], Lazy[t][1][j], Lazy[t][2][j], j==3);
	}

	for(int i=0;i<3;++i)for(int j=0;j<4;++j){
		Lazy[t][i][j] = tmp[i][j];
	}
}

inline void _pushDown(int t, int s, int e){
	mat_t &lazy = Lazy[t];
	if(isI(lazy)) return;

    /// 根据父节点的lazy计算子节点的值
	/// 根据父节点的lazy更新子节点的Lazy
	int mid = (s+e) >> 1;
	_f(lazy, lson(t), s, mid);
	_f(lazy, rson(t), mid+1, e);

    mkI(lazy);
}

/// x表示第几排，从0开始
llt query(int t, int s, int e, int a, int b, int x){
    if(a<=s&&e<=b){
		return ST[x][t];
	}

	_pushDown(t, s, e);
	int mid = (s+e) >> 1;
	llt ans = 0;
	if(a<=mid) ans += query(lson(t), s, mid, a, b, x);
	if(mid<b) ans += query(rson(t), mid+1, e, a, b, x);
	return ans %= MOD;
}

/// 为x排增加delta
void modify(int t, int s, int e, int a, int b, int x, llt delta){
    if(a<=s&&e<=b){ // 增加delta，更新值和延迟
	    (ST[x][t] += (e-s+1) * delta) %= MOD;
        (Lazy[t][x][3] += delta) %= MOD;
		return;
	}

	_pushDown(t, s, e);
	int mid = (s+e) >> 1;
	if(a<=mid) modify(lson(t), s, mid, a, b, x, delta);
	if(mid<b) modify(rson(t), mid+1, e, a, b, x, delta);
	_pushUp(t);
}

/// 对x和y排做操作,注意xy的顺序不能反
void modify(int t, int s, int e, int a, int b, int x, int y, int op){
    if(a<=s&&e<=b){
		if(2==op){ // xy互换		
            swap(ST[x][t], ST[y][t]); // 更新值
            swap(Lazy[t][x][0], Lazy[t][y][0]); //更新延迟标记
			swap(Lazy[t][x][1], Lazy[t][y][1]); 
			swap(Lazy[t][x][2], Lazy[t][y][2]); 
			swap(Lazy[t][x][3], Lazy[t][y][3]); 
		}else if(op==3){ // 把x加到y上面
            (ST[y][t] += ST[x][t]) %= MOD; // 更新值
            (Lazy[t][y][0] += Lazy[t][x][0]) %= MOD;
			(Lazy[t][y][1] += Lazy[t][x][1]) %= MOD;
			(Lazy[t][y][2] += Lazy[t][x][2]) %= MOD;
			(Lazy[t][y][3] += Lazy[t][x][3]) %= MOD;
		}
		return;
	}

	_pushDown(t, s, e);
	int mid = (s+e) >> 1;
	if(a<=mid) modify(lson(t), s, mid, a, b, x, y, op);
	if(mid<b) modify(rson(t), mid+1, e, a, b, x, y, op);
	_pushUp(t);	
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif
    int n = getUnsigned();
	for(int i=1,m=4*n;i<=m;++i)mkI(Lazy[i]);

	int q = getUnsigned();
	int op,x,y,a,b;
	llt d;
	while(q--){
		switch(op=getUnsigned()){
			case 0:{
                x = getUnsigned() - 1;
				a = getUnsigned();
				b = getUnsigned();
				printf("%lld\n", query(1, 1, n, a, b, x));
			}break;
			case 1:{
                x = getUnsigned() - 1;
				a = getUnsigned();
				b = getUnsigned();
				d = getUnsigned();
				modify(1, 1, n, a, b, x, d);
			}break;
			case 2:
			case 3:{
                x = getUnsigned() - 1;
				y = getUnsigned() - 1;
				a = getUnsigned();
				b = getUnsigned();
				modify(1, 1, n, a, b, x, y, op);
			}break;
			default: throw runtime_error("wrong cmd.");
		}
		int fdsfe2=5;
	}
    return 0;
}
