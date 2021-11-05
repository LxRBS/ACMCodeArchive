/**
  三维空间旋转，套公式
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

Point rotate(const Point &p, const Point &r, Real theta){
    Real costheta = cos(theta);
    Real sintheta = sin(theta);
    return p * costheta + r * r.dot(p) * (1-costheta) + r.cross(p) * sintheta;  
}

void proc(){
    /// 角度
    Real theta = R * PI / 180;
    Real costheta = cos(theta);
    Real sintheta = sin(theta);
    /// 旋转轴
    Real len = A.norm();
    A.x /= len, A.y /= len, A.z /= len;
    assert(isEq(A.norm(),1));

    Point z3 = rotate(B, A, theta);
    Point z4 = rotate(B, A, -theta);
    if(z3.z>=z4.z){
        z3.output();
        // z4.output();
    }else{
        // z3.output();
        z4.output();
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

