/**
 * 给定A和B，表示矩形的长和宽，问其中能放的最大正三角形边长是多少
 * 有一个公式
 * b / a >= 2 / sqrt(3), ans = 2A / sqrt(3)
 * b / a < 2 / sqrt(3), ans = 2sqrt(a^2+b^2-sqrt(3)ab)
 * 这里用二分。正三角形的一个端点必然在矩形上。另一个点必然在对边上。又旋转角度在[0, 30度]之间
 * 对于指定角度，看第三个点是否也在矩形内。
 */
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
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
int const SIZE = 66;
#endif

using Real = long double;
using llt = long long;
using vi = vector<int>;
using vll =vector<llt>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vpii = vector<pii>;

llt const MOD = 998244353LL;

Real const EPS = 1E-16;
Real const PI = acos(-1.L);
inline int sgn(Real x){return x > EPS ? 1 : (x < -EPS ? -1 : 0);}
inline bool is0(Real x){return 0 == sgn(x);}

Real A, B;

bool check(Real theta){
	theta = theta * PI / 180;
    Real x0 = A * tan(theta);
	Real y0 = A;
	assert(sgn(x0 - B) < 0);

	Real a = sqrt(x0 * x0 + y0 * y0);
	Real angle = PI / 6.0 - theta;
	assert(sgn(angle) >= 0);

	Real x1 = a * cos(angle);
	Real y1 = a * sin(angle);
	assert(sgn(y1 - A) < 0);

	auto tmp = sgn(x1 - B);
	return tmp <= 0;
}

Real proc(){
	auto tmp = sgn(A - B);
	if(0 == tmp) return (sqrt(6.L) - sqrt(2.L)) * A;
	if(tmp > 0) swap(A, B);

    Real left = 0, right = 30, mid;
    do{
		mid = (left + right) * 0.5;
        if(check(mid)) left = mid + EPS;
		else right = mid - EPS;
	}while(left <= right);
	// cout << right << endl;
	right = right * PI / 180;
	return A * sqrt(tan(right) * tan(right) + 1.L);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	// int nofkase; scanf("%d", &nofkase);
    // int nofkase = getInt();
    cin >> A >> B;
	cout << fixed <<setprecision(16) << proc() << endl;
    return 0; 
}