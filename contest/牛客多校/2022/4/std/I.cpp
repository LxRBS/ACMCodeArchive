#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int mod = 998244353;
const LL G = 3;
const int maxn = 2000005;

namespace Poly {
    inline void Add(int &x, const int &b) {
        x += b; if(x >= mod) x -= mod;
    }
    inline int sum(const int &a, const int &b) {
        return a + b >= mod ? a + b - mod : a + b;
    }
    inline void Dec(int &x, const int &b) {
        x -= b; if(x < 0) x += mod;
    }
    inline int delt(const int &a, const int &b) {
        return a - b < 0 ? a - b + mod : a - b;
    }
    struct PLG {
        vector<int > x;
        PLG() {}
        PLG(int sz) {cg(sz);}
        inline int deg() const {return x.size() - 1;}
        inline void cg(int k) {x.resize(k + 1);}
        void read(int n) {
            int u;
            for(register int i = 0; i <= n; ++i)
                scanf("%d", &u), x.push_back(u);
        }
        void prt() {
            for(register int i = 0; i < x.size(); ++i)
                printf("%d ", x[i]);
            putchar('\n');
        }
    };
    int RL[maxn], w[maxn];
    LL fpow(LL a, int b) {
        LL ans = 1;
        while(b) {
            if(b & 1) ans = ans * a % mod;
            a = a * a % mod, b >>= 1;
        }
        return ans;
    }
    const int IG = fpow(G, mod - 2);
    int mx2p = 1, N = 1;
    void init(int n) {
        for(mx2p = 0, N = 1; N <= n; N <<= 1, ++mx2p);
    }
    int NTT(PLG &A, int type) {
        A.x.resize(N);
        for (register int i = 0, j = 0; i < N; i++) {
            if (i > j) std::swap(A.x[i], A.x[j]);
            for (register int k = N >> 1; (j ^= k) < k; k >>= 1)
                ;
        }
        int x, y, Wn;
        vector<int >::iterator p1, p2;
        for(register int i = 1; i < N; i <<= 1) {
            if(~type) Wn = fpow(G, (mod - 1) / (i << 1));
            else Wn = fpow(IG, (mod - 1) / (i << 1));
            w[0] = 1;
            for(register int j = 1; j < i; ++j)
                w[j] = 1ll * w[j - 1] * Wn % mod;
            p1 = A.x.begin();
            p2 = A.x.begin() + i;
            for(register int p = i << 1, j = 0; j < N; j += p) {
                for(register int k = 0; k < i; ++k) {
                    x = *(p1 + k), y = 1ll * w[k] * (*(p2 + k)) % mod;
                    *(p1 + k) = sum(x, y);
                    *(p2 + k) = delt(x, y);
                }
                p1 += p, p2 += p;
            }
        }
        if(type == -1) {
            LL inv = fpow(N, mod - 2);
            for(register int i = 0; i < N; ++i)
                A.x[i] = A.x[i] * inv % mod;
        }
        return N;
    }
    PLG tmpa, tmpb;
    PLG operator * (const PLG &A, const PLG &B) {
        int len = A.deg() + B.deg();
        tmpa = A, tmpb = B;
        tmpa.cg(len), tmpb.cg(len);
        init(len);
        NTT(tmpa, 1), NTT(tmpb, 1);
        for(register int i = 0; i < N; ++i)
            tmpa.x[i] = 1ll * tmpa.x[i] * tmpb.x[i] % mod;
        NTT(tmpa, -1), tmpa.cg(len);
        return tmpa;
    }
    PLG operator * (const PLG &A, const LL &x) {
        PLG C;
        for(register int i = 0; i <= A.deg(); ++i)
            C.x.push_back(A.x[i] * x % mod);
        return C;
    }
}

using namespace Poly;
int K, u, v, lenv, MXID = 1;
vector<int > D, VD, tmp;
PLG A, B, C, avapos;
int mp[maxn], vec[maxn];

int id(const vector<int > &p) {
	int ret = 0;
	for(int i = 0; i < K; ++i)
		ret = D[i] * ret + p[i];
	return ret;
}

vector<int > pos(int id) {
	vector<int > ret;
	for(int i = K - 1; i >= 0; --i)
		ret.push_back(id % D[i]), id /= D[i];
	reverse(ret.begin(), ret.end());
	return ret;
}

int illegal(int id) {
	vector<int > p = pos(id);
	for(int i = K - 1; i >= 0; --i) {
		if(p[i] + VD[i] > D[i])
			return 1;
	}
	return 0;
}

int inV(int id) {
	vector<int > p = pos(id);
	for(int i = K - 1; i >= 0; --i) {
		if(p[i] >= VD[i])
			return 0;
	}
	return 1;
}

void fit(int x) {
	for(int i = 0; i <= MXID; ++i) {
		if(mp[i] < x) A.x[i] = 1;
		else A.x[i] = 0;
	}
	//A.prt();
	for(int i = 0; i <= lenv; ++i) {
		if(vec[i] == x) B.x[i] = 1;
		else B.x[i] = 0;
	}
	//B.prt();
	reverse(A.x.begin(), A.x.end());
	C = A * B;
	for(int i = lenv; i <= MXID; ++i)
		if(C.x[i]) avapos.x[i - lenv] |= 1;
}

int main() {
	scanf("%d", &K);
	for(int i = 1; i <= K; ++i)
		scanf("%d", &u), D.push_back(u);
	for(int i = 0; i < K; ++i)
		MXID *= D[i];
	MXID--;
	scanf("%d", &u);
    for(int i = 1; i <= u; ++i) {
    	vector<int > p;
    	for(int j = 0; j < K; ++j) {
			scanf("%d", &v);
			p.push_back(v);
		}
		scanf("%d", &v);
		int vid = id(p);
		mp[vid] = v;
	}
	for(int i = 0; i <= MXID; ++i) {
		if(!mp[i]) mp[i] = K;
	}
	for(int i = 1; i <= K; ++i)
		scanf("%d", &u), VD.push_back(u), tmp.push_back(u - 1);
	lenv = id(tmp);
	scanf("%d", &u);
	for(int i = 1; i <= u; ++i) {
    	vector<int > p;
    	for(int j = 0; j < K; ++j) {
			scanf("%d", &v);
			p.push_back(v);
		}
		scanf("%d", &v);
		int vid = id(p);
		vec[vid] = v;
	}
	for(int i = 0; i <= lenv; ++i) {
		if(!vec[i] && inV(i))
			vec[i] = K;
	}
	A.cg(MXID), B.cg(lenv);
	avapos.cg(MXID - lenv);
	for(int i = 2; i <= K; ++i)
		fit(i);
	int ans = 0;
	for(int i = 0; i <= MXID - lenv; ++i) {
		if(!avapos.x[i] && !illegal(i))
			++ans;
	}
	//avapos.prt();
	printf("%d", ans);
    return 0;
}