/// 圆内某线段，可以绕中点任意选择
/// 问该线段在圆周上覆盖的最长圆弧是多少
/// 只需旋转90度即可，简单枚举一下发现总是90度取到最大值
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
int const SIZE = 106;
#else
int const SIZE = 1E6+7;
#endif

using llt = long long;
using Real = long double;

Real const PI = acos(-1);
Real const EPS = 1E-8;
inline int sgn(Real x){return x >= EPS ? 1 : (x <= -EPS ? -1 : 0);}
inline bool is0(Real x){return 0 == sgn(x);}

struct Point{
    Real x, y;
    Point(Real a=0, Real b=0):x(a),y(b){}
};

using ppp = pair<Point, Point>;

inline ppp get(Point p, Real d, Real theta){
    Point a = {p.x + d * cos(theta), p.y + d * sin(theta)};
    Point b = {p.x + d * cos(theta+PI), p.y + d * sin(theta+PI)};
    return {a, b};
}

int f(Real a, Real b, Real c, Real x[]){
    Real delta = b * b - 4.0 * a * c;
    if(sgn(delta) < 0) return 0;
    if(0 == sgn(delta)){
        x[0] = - b / (a + a);
        return 1;
    }
    Real dd = sqrt(delta);
    x[0] = (-b - dd) / (a + a);
    x[1] = (-b + dd) / (a + a);
    return 2;
}

Point Q;
Real D, R;

void f(Point p, Real jiao, Point ans[]){
    Real a = 1.0;
    Real b = 2.0 * (p.x * cos(jiao) + p.y * sin(jiao));
    Real c = p.x * p.x + p.y * p.y - R * R;
    Real sol[2];
    int tmp = f(a, b, c, sol);
    assert(tmp >= 1);
    assert(sgn(sol[0] * sol[1]) <= 0);

    ans[0] = {p.x + sol[0] * cos(jiao), p.y + sol[0] * sin(jiao)};
    ans[1] = {p.x + sol[1] * cos(jiao), p.y + sol[1] * sin(jiao)};
}

Real g(const Point &A, const Point &B){
    Real a = atan2(A.y, A.x);
    Real b = atan2(B.y, B.x);
    Real ans = fabs(b - a);
    if(sgn(ans - PI) > 0) ans = PI + PI - ans;
    return ans;
}

Real proc(Real theta){
    auto pab = get(Q, D, theta);
    Real jiao = theta - PI * 0.5;
    
    Point a[2], b[2];
    f(pab.first, jiao, a);
    f(pab.second, jiao, b);

    Real jiao1 = g(a[0], b[0]);
    Real jiao2 = g(a[1], b[1]);
    jiao = max(jiao1, jiao2);
    return jiao * R;
}

Real proc(){
    if(0 == sgn(D)) return 0;

    if(Q.x < 0) Q.x = -Q.x;
    if(Q.y < 0) Q.y = -Q.y;

    if(0 == sgn(Q.x) && 0 == sgn(Q.y)){
        Real alpha = asin(D / R);
        Real ans = 2.0 * alpha * R;
        return ans;
    }
    Real ans = 0., weizhi;
    Real alpha = atan2(Q.y, Q.x);
    // for(Real theta=alpha+PI/2;theta<=alpha+PI;theta+=1E-2){
    //     Real tmp = proc(theta);
    //     if(tmp > ans){
    //         ans = tmp;
    //         weizhi = theta;
    //     }
    // }
    // cout<<"alpah = "<<alpha<<endl;
    // cout<<weizhi<<endl;
    ans = proc(alpha + PI);
    return ans;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif  
    int nofkase = getInt();
    while(nofkase--){
        R = getInt();
        Q.x = getInt(); Q.y = getInt();
        D = getInt();
        cout << fixed << setprecision(12) << proc() << endl;
    }
    return 0;
}