/**
 * 有A和B两组糖水，分别有N个和M个，均给出糖质量与水质量。
 * 假设A和B各取一杯进行混合，则一共有 N*M 种可能性
 * 问在这么多可能性中，第K大的含糖率是多少？
 * N和M在1E5，K在N*M量级。显然不能直接求出N*M个进行排序。
 * 考虑二分判定
 * 首先解决如下问题：给定含糖率x，有多少混合物的含糖率比x大
 * 令  糖 / (糖 + 水) = x 令 缺口 = 水 * x / (1 - x) - 糖
 * 缺口表明此糖水要达到x还需要多少糖，对A中的所有糖水计算缺口并排序。
 * 对B中的每一杯糖水，计算 多余 = 糖 - 水 * x / (1 - x)
 * 查看此 多余 比多少个 缺口 大，就表明此杯糖水能混合出多少杯大于等于 x 的混合物
 * 遍历B就可以在O(NlogN + MlogN)求出有多少杯混合物比x大。
 * 再二分一下即可。考虑到精度，大概二分50次左右即可。
 */
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_cxx;
using namespace __gnu_pbds;


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
int const SIZE = 21;
#else
int const SIZE = 2E5+10;
#endif

using llt = long long;
using vi = vector<int>;
using vll =vector<llt>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vpii = vector<pii>;
using ull = unsigned long long;
// using i128 = __int128_t;
using Real = long double;

Real const EPS = 1E-14;
inline int sgn(Real x) {return x > EPS ? 1 : (x < -EPS ? -1 : 0);}
inline bool is0(Real x) {return 0 == sgn(x);}

llt K;
int N, M;
vpii A, C;

bool check(Real x){
	Real z = x / (1.L - x);
	vector<Real> v;
	v.reserve(N);
	for(const auto & p : A) v.emplace_back(p.second * z - p.first);
	sort(v.begin(), v.end());

	llt tmp = 0;
	for(const auto & p : C){
		auto w = p.first - p.second * z;
		tmp += upper_bound(v.begin(), v.end(), w) - v.begin();
	}
	return tmp >= K;
}

Real proc(){
	Real left = 0, right = 1, mid;
	do{
        mid = (left + right) * 0.5L;
		if(check(mid)) left = mid + EPS;
		else right = mid - EPS;
	}while(sgn(left - right) <= 0);
	return left * 100.L;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	// int nofkase; scanf("%d", &nofkase);
    cin >> N >> M >> K;
	A.assign(N, {}); C.assign(M, {});
	for(auto & p : A) cin >> p.first >> p.second;
	for(auto & p : C) cin >> p.first >> p.second;
	cout << fixed << setprecision(12) << proc() << endl;
    return 0; 
}


