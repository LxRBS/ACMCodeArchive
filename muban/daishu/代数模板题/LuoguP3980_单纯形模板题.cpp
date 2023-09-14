/**
 * 权值类型用longdouble，最后一个点会MLE
 */
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

struct Simplex{
using weight_t = double;

/**
 * 标准型 
 * max CtX, st. AX <= B, X >= 0
 */

int N; // x的数量
int M; // 约束的数量
vector<vector<weight_t>> A; // M * N 的矩阵
vector<weight_t> B; // M长度向量
vector<weight_t> C; // N长度向量
weight_t ans;

void init(int n, int m){
    A.assign((M = m) + 1, vector<weight_t>((N = n) + 1, 0));
	B.assign(M + 1, 0);
	C.assign(N + 1, 0);
}

std::pair<bool, weight_t> calc(){
	ans = 0;
	for(;;){
        int e = 0, s = 0;
		for(e=1;e<=N;++e)if(1 == cmp(C[e], (weight_t)0)) break;
		// cout << "e = " << e << endl;
		if(N + 1 == e) return {true, ans};
		weight_t bound = inf(), tmp;
		for(int i=1;i<=M;++i){
			if(1 == cmp(A[i][e], (weight_t)0) and 1 == cmp(bound, tmp = B[i] / A[i][e])){
				bound = tmp;
				s = i;
			}
		}
		if(0 == cmp(bound, inf())) return {true, inf()};
		pivot(s, e);
	}
	return {false, 0};
}

void pivot(int s, int e){
	B[s] /= A[s][e];
	for(int j=1;j<=N;++j)if(j!=e)A[s][j] /= A[s][e];
	A[s][e] = 1 / A[s][e];

	for(int i=1;i<=M;++i){
		if(i != s and sgn(A[i][e])){
            B[i] -= A[i][e] * B[s];
			for(int j=1;j<=N;++j){
				if(j != e){
					A[i][j] -= A[i][e] * A[s][j];
				}
			}
			A[i][e] *= - A[s][e];
		}
	}

	ans += C[e] * B[s];
	for(int j=1;j<=N;++j)if(j != e)C[j] -= C[e] * A[s][j];
	C[e] *= - A[s][e];
	return;
}

static int sgn(weight_t x){
	return x > eps() ? 1 : (x < -eps() ? -1 : 0);
}

static int cmp(weight_t a, weight_t b){
    return sgn(a - b);    
}

static weight_t inf(){
	static const weight_t INF = 0x7F8F9FAFBFCFDFEF;
	return INF;
}

static weight_t eps(){
	static const weight_t EPS = 1E-6;
	return EPS;
}

void output(ostream & os){
	os << "A:" << endl;
	for(int i=1;i<=M;++i){
		for(int j=1;j<=N;++j) os << fixed << setprecision(1) << A[i][j] << " ";
	    os << endl;
	}
	os << "B:";
	for(int i=1;i<=M;++i) os << " " << fixed << setprecision(1) << B[i];
	os << endl;
	os << "C:";
	for(int i=1;i<=N;++i) os << " " << fixed << setprecision(1) << C[i];
	os << endl;
}

};

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n, m, t;
	cin >> n >> m;
    Simplex simple;
	simple.init(n, m);
	for(int i=1;i<=n;++i) cin >> simple.C[i];
	for(int a,b,i=1;i<=m;++i){
		cin >> a >> b;
		fill(simple.A[i].begin()+a, simple.A[i].begin()+b+1, 1);
        cin >> simple.B[i];
	}
	auto ans = simple.calc();
	if(not ans.first){
		cout << "Infeasible" << endl;
	}else if(0 == Simplex::cmp(ans.second, Simplex::inf())){
		cout << "Unbounded" << endl;
	}else{
		int tmp = (int)(ans.second + 0.5);
		cout << tmp << endl;
	}
    return 0;
}