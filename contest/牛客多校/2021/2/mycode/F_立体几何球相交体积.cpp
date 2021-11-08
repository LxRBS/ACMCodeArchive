/**
    本质上就是求两个球相交的体积
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

#define mp make_pair

typedef long double Real;
Real const EPS = 1E-9;
Real const PI = acos((Real)-1.0);
inline int sgn(Real x){return x>EPS?1:(x<-EPS?-1:0);}
inline bool is0(Real x){return 0==sgn(x);}
inline bool isEq(Real x, Real y){return is0(x-y);}
inline bool isGt(Real x, Real y){return sgn(x-y)>0;}

inline Real mysqrt(Real x){
    if(0==sgn(x)) return 0;
    if(sgn(x)>0) return sqrt(x);
    throw runtime_error("sqrt");
}

inline Real dist2(Real x1, Real y1, Real z1, Real x2, Real y2, Real z2){
    Real x = x1 - x2;
    Real y = y1 - y2;
    Real z = z1 - z2;
    return x*x + y*y + z*z;
}

/// 高度为h球半径为r的球缺的体积公式
inline Real fv(Real r, Real h){
    return PI * h * h * (r - h/3.0);
}

Real inter(Real x1, Real y1, Real z1, Real r1, Real x2, Real y2, Real z2, Real r2){
    Real d2 = dist2(x1, y1, z1, x2, y2, z2);
    Real d = sqrt(d2);
    Real tmp = r1 + r2;
    if(sgn(d-tmp)>=0) return 0.0;

    tmp = r1 - r2;
    if(tmp<0) tmp = -tmp;
    if(sgn(tmp-d)>=0){
        Real r = min(r1, r2);
        return 4.0*PI*r*r*r/3.0;
    }
    /// 相交为球冠
    Real costheta = (r1*r1 + d2 - r2*r2)/(2.0*r1*d);
    Real h = r1 * (1.0 - costheta);
    Real ans = fv(r1, h);
    costheta = (r2*r2+d2-r1*r1)/(2.0*r2*d);
    h = r2 * (1.0 - costheta);
    ans += fv(r2, h);
    return ans;
}

/// 确定球
bool mkSphere(Real ax,Real ay,Real az,Real bx,Real by,Real bz,Real k,Real&x,Real&y,Real&z,Real&r){
    Real k2 = k * k;
    Real x_xishu_a = k2-1;
    Real x_xishu_b = 2.0*ax - 2.0*bx*k2;
    Real x_xishu_c = k2*bx*bx - ax*ax;
    Real x_delta = x_xishu_b * x_xishu_b - 4.0 * x_xishu_a * x_xishu_c;

    Real y_xishu_a = k2-1;
    Real y_xishu_b = 2.0*ay - 2.0*by*k2;
    Real y_xishu_c = k2 * by*by - ay*ay;
    Real y_delta = y_xishu_b * y_xishu_b - 4.0 * y_xishu_a * y_xishu_c;


    Real z_xishu_a = k2-1;
    Real z_xishu_b = 2.0*az - 2.0*bz*k2;
    Real z_xishu_c = k2 * bz*bz - az*az;
    Real z_delta = z_xishu_b * z_xishu_b - 4.0 * z_xishu_a * z_xishu_c;

    Real delta = x_delta / (4.0*x_xishu_a*x_xishu_a)
        + y_delta / (4.0*y_xishu_a*y_xishu_a)
        + z_delta / (4.0*z_xishu_a*z_xishu_a);

    if(sgn(delta)<0) return false;

    x = - x_xishu_b / (x_xishu_a+x_xishu_a);
    y = - y_xishu_b / (y_xishu_a+y_xishu_a);
    z = - z_xishu_b / (z_xishu_a+z_xishu_a);
    r = mysqrt(delta);
    return true;
}

Real Ax,Ay,Az,Bx,By,Bz,Cx,Cy,Cz,Dx,Dy,Dz,K1,K2;

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif
    int nofkase = getInt();
    while(nofkase--){
        Ax = getInt(), Ay = getInt(), Az = getInt();
        Bx = getInt(), By = getInt(), Bz = getInt();
        Cx = getInt(), Cy = getInt(), Cz = getInt();
        Dx = getInt(), Dy = getInt(), Dz = getInt();
        K1 = getInt(), K2 = getInt();

        Real x1,y1,z1,r1,x2,y2,z2,r2;
        if(!mkSphere(Ax,Ay,Az,Bx,By,Bz,K1,x1,y1,z1,r1)){
            printf("0.000000\n");
            continue;
        }
        if(!mkSphere(Cx,Cy,Cz,Dx,Dy,Dz,K2,x2,y2,z2,r2)){
            printf("0.000000\n");
            continue;
        }
        printf("%.8Lf\n", inter(x1,y1,z1,r1,x2,y2,z2,r2));
    }
    return 0;
}
