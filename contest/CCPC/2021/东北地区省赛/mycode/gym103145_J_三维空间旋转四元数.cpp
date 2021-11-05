/**
  给定旋转轴，给定角度，求旋转以后的点
  直接套四元数公式
  罗德里格旋转公式本质上与四元数是一致的
*/
#include<bits/stdc++.h>
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

typedef long double Real;
Real const PI =acos((Real)-1.0);
Real const EPS = 1E-8;

inline int sgn(Real x){return x>EPS?1:(x<-EPS?-1:0);}
inline bool is0(Real x){return 0==sgn(x);}
inline bool isEq(Real x, Real y){return is0(x-y);}

struct Point{
    Real x, y, z;
    Point(Real a=0,Real b=0,Real c=0):x(a),y(b),z(c){}
    Real norm()const{return sqrt(x*x+y*y+z*z);}
    void output(){
        printf("%.8Lf %.8Lf %.8Lf\n", x, y, z);
    }
    Real dot(const Point &p)const{
        return x*p.x + y*p.y + z*p.z;
    }
    Point cross(const Point &p)const{
        return Point(
            y*p.z - z*p.y,
            z*p.x - x*p.z,
            x*p.y - y*p.x
        );
    }
    Point operator * (Real r)const{
        return Point(x*r, y*r, z*r);
    }
    Point operator + (const Point &p)const{
        return Point(x+p.x, y+p.y, z+p.z);
    }
}A, B;

int R;

struct Quat{ // 四元数
    Real w, x, y, z;
    Quat(Real a=0,Real b=0,Real c=0,Real d=0):w(a),x(b),y(c),z(d){}
    Quat conj()const{return Quat(w,-x,-y,-z);} // 共轭
    Real norm()const{return sqrt(w*w+x*x+y*y+z*z);}
};

const Quat operator * (const Quat&lhs, const Quat&rhs){
    return Quat(
            lhs.w*rhs.w-lhs.x*rhs.x-lhs.y*rhs.y-lhs.z*rhs.z,
            lhs.w*rhs.x+lhs.x*rhs.w+lhs.y*rhs.z-lhs.z*rhs.y,
            lhs.w*rhs.y-lhs.x*rhs.z+lhs.y*rhs.w+lhs.z*rhs.x,
            lhs.w*rhs.z+lhs.x*rhs.y-lhs.y*rhs.x+lhs.z*rhs.w
        );
}

/// 给定点p，求经过旋转r之后的点
Point rotate(const Point &p, const Quat &r){
    assert(isEq(r.norm(), 1));
    Quat origin(0, p.x, p.y, p.z);
    Quat after = r * origin * r.conj();
    assert(is0(after.w));
    return Point(after.x, after.y, after.z);
}

void proc(){
    /// 角度
    Real theta = R * PI / 180;
    Real costheta = cos(theta*0.5);
    Real sintheta = sin(theta*0.5);
    /// 旋转轴
    Real len = A.norm();
    A.x /= len, A.y /= len, A.z /= len;
    assert(isEq(A.norm(),1));
    Quat rot(costheta, A.x*sintheta, A.y*sintheta, A.z*sintheta);
    Point z1 = rotate(B, rot);
    rot.x = -rot.x, rot.y = -rot.y, rot.z = -rot.z;
    Point z2 = rotate(B, rot);
    if(z1.z>=z2.z){
        z1.output();
        // z2.output();
    }else{
        // z1.output();
        z2.output();
    }
}

int main(){
    // freopen("1.txt","r",stdin);
    int nofkase = getUnsigned();
    while(nofkase--){
        A.x = getUnsigned();
        A.y = getUnsigned();
        A.z = getUnsigned();
        B.x = getUnsigned();
        B.y = getUnsigned();
        B.z = getUnsigned();
        R = getUnsigned();
        proc();
    }
    return 0;
}

