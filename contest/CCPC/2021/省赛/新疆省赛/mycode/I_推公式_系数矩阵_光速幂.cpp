/**
 * 令f(x)=f(x-1)+f(x-2)+2sqrt(3+f(x-1)f(x-2))
 * 给定f0, f1, M，以及长度为n的X数组，求PI{f(xi)}%M
 * 令g(i-1)=sqrt(3+f(i-1)f(i-2))，所以f(i-2)=(g(i-1)^2-3)/f(i-1)
 * 代入到递推式中，最后有f(i)f(i-1)=(f(i-1)+g(i-1))^2-3
 * 注意到f(i)f(i-1)=gi^2-3，所以最后有
 * gi=f(i-1)+g(i-1) 以及
 * fi=f(i-1)+f(i-2)+2g(i-1)
 * 令列向量 Fi = [fi, gi, f(i-1)]^t
 *  fi        1 2 1     f(i-1) 
 *  gi     =  1 1 0  *  g(i-1)
 *  f(i-1)    1 0 0     f(i-2)
 * 于是有了系数矩阵，矩阵快速幂会超时，要用光速幂
 * 与大步小步算法的查找有些类似
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
int const SIZE = 13;
#else
int const SIZE = 1E6+10;
#endif

using llt = long long int;
using Real = double;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vpii = vector<pii>;

llt MOD;

struct matrix_t{
    enum{SIZE=3};
	llt data[SIZE][SIZE];

	matrix_t(){memset(data, 0, sizeof(data));}

	void i(){
		memset(this->data, 0, sizeof(this->data));
		for(int i=0;i<SIZE;++i) this->data[i][i] = 1;
	}

	void copy(matrix_t const & b){
		for(int i=0;i<SIZE;++i) std::copy(b.data[i], b.data[i]+SIZE, this->data[i]);
	}

	static void mul(const matrix_t & a, const matrix_t & b, matrix_t & c){
		for(int i=0;i<SIZE;++i)for(int j=0;j<SIZE;++j){
			llt & r = c.data[i][j];
			r = 0;
			for(int k=0;k<SIZE;++k){
				(r += a.data[i][k] * b.data[k][j] % MOD) %= MOD;
			}
		}
	}

	static matrix_t t1, t2, t3;
	static matrix_t & pow(const matrix_t & mat, int n){
		matrix_t * rp = &t1, * tp = &t2, * mp = &t3;
		rp->i(); mp->copy(mat);

		while(n){
			if(n & 1){
				mul(*rp, *mp, *tp);
				swap(rp, tp);
			}

			mul(*mp, *mp, *tp);
			swap(mp, tp);
			n >>= 1;
		}

		return *rp;
	}

	static void swap(matrix_t *&pa, matrix_t *&pb){
		matrix_t *tp = pa; pa = pb; pb = tp;
	}
};

matrix_t matrix_t::t1;
matrix_t matrix_t::t2;
matrix_t matrix_t::t3;

llt F0, F1, G1, M, N, X[SIZE];
matrix_t Xishu;

using matvec = vector<matrix_t>;
matvec Da, Xi;

void init(int n){
    matrix_t a, b;
	a.i();
	b = matrix_t::pow(Xishu, n);

	Da.push_back(a);
	Xi.push_back(a);
	for(int i=1;i<=n;++i){
		matrix_t u;
		matrix_t::mul(Xi.back(), Xishu, u);
        Xi.emplace_back(u);

		matrix_t v;
		matrix_t::mul(Da.back(), b, v);
		Da.emplace_back(v);
	}
}


llt f(int x){
	if(0 == x) return F0;
	if(1 == x) return F1;

    llt a = x / M, b = x % M;
	matrix_t m;
	matrix_t::mul(Da[a], Xi[b], m);
    llt ans = m.data[2][0] * F1 % MOD + m.data[2][1] * G1 % MOD + m.data[2][2] * F0 % MOD;
	ans %= MOD;
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif

	Xishu.data[0][0] = Xishu.data[0][2] = 1;
	Xishu.data[0][1] = 2;
	Xishu.data[1][0] = Xishu.data[1][1] = Xishu.data[2][0] = 1;

    F0 = getInt(); F1 = getInt();
	MOD = getInt(); N = getInt();
	G1 = (llt)sqrt(3+F0*F1);
	assert(G1*G1 == 3+F0*F1);

    M = 0;
	for(int i=1;i<=N;++i) M = max(M, X[i] = getInt());
	
	/// 光速幂，预处理
	M = sqrt(M) + 1;
	init(M);

	llt ans = 1;

	for(int i=1;i<=N;++i) {
        (ans *= f(X[i])) %= MOD;
	}

    cout<<ans<<endl;
    return 0;
}