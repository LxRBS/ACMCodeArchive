/**
 * 给定2个L形状，问L1旋转平移是否能够变成L2。
 * 保证2个L可以旋转平移翻转得到。
 * 所以就是用叉积判断旋向，把翻转去掉即可。
 * 注意如果L的两端长度是相等的，则一定可以。
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
#else
int const SIZE = 5500;
#endif

using Real = long double;
using llt = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using prr = pair<Real, Real>;

Real const EPS = 1E-9;
inline int sgn(Real x) {return x>=EPS?1:(x<=-EPS?-1:0);}
inline bool is0(Real x){return 0 == sgn(x);}

prr A[3];
prr B[3];

Real dist(const prr & a, const prr  & b){
    Real x = b.first - a.first;
    Real y = b.second - a.second;
    return x * x + y * y;
}

int cross(const prr a[]){
    Real xoa = a[0].first - a[1].first;
    Real yoa = a[0].second - a[1].second;
    Real xob = a[2].first -  a[1].first;
    Real yob = a[2].second - a[1].second;
    return sgn(xoa * yob - xob * yoa);
}

bool proc(){
    int att = sgn(dist(A[0], A[1]) - dist(A[1], A[2]));
    if(0 == att) return false;
    if(att > 0) swap(A[0], A[2]);

    int btt = sgn(dist(B[0], B[1]) - dist(B[1], B[2]));
    assert(btt);
    if(btt > 0) swap(B[0], B[2]);

    auto ta = cross(A);
    auto tb = cross(B);
    if(ta == 0){
        assert(0 == tb);
        return false;
    }
    return ta * tb < 0;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int nofkase; cin >> nofkase;
    while(nofkase--){
        for(auto & p : A) cin >> p.first >> p.second;
        for(auto & p : B) cin >> p.first >> p.second;
        puts(proc()?"YES":"NO");
    }

    return 0;
}


