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

/** 1. typdef和常数 **/
using Real = long double;
using llt = long long;
using T = llt;

Real const EPS = 1E-9;

inline int sgn(Real x) {return x>EPS?1:(x<-EPS?-1:0);}
inline bool is0(Real x) {return 0 == sgn(x);}

inline int sgn(llt x) {return x>0?1:(x<0?-1:0);}
inline bool is0(llt x) {return 0 == sgn(x);}

/** 2. 处理边界的数学库函数 **/
inline Real mysqrt(Real x){
    assert(sgn(x) >= 0);
    if(0 == sgn(x)) return 0;
    return sqrt(x);
}

inline Real myacos(Real x){
    assert(sgn(fabs(x) - 1) <= 0);
    if(0 == sgn(x - 1)) x = 1;
    else if(0 == sgn(x + 1)) x = -1;
    return acos(x);
}

inline Real myasin(Real x){
    assert(sgn(fabs(x) - 1) <= 0);
    if(0 == sgn(x - 1)) x = 1;
    else if(0 == sgn(x + 1)) x = -1;
    return asin(x);
}


/** 3. 点与向量的结构体以及基本运算，相等，加减乘，叉积，点积 **/
struct Point{

T x, y, z;
Point() = default;
Point(T a, T b, T c):x(a),y(b),z(c){}

void input(){
    x = getInt(); y = getInt(); z = getInt();
}

Real length() const {
    return mysqrt(x * x + y * y + z * z);
}

bool isZero() const {return is0(x) && is0(y) && is0(z);}

void normSelf(){ // 单位化，坐标类型必须是Real才能调用这个函数
    assert(!this->isZero());
    Real tmp = this->length();
    this->x /= tmp;
    this->y /= tmp;
    this->z /= tmp;
}

};

/// 向量，就是点
using Vector = Point;

bool operator == (const Point &a, const Point &b){
    return is0(a.x - b.x) && is0(a.y - b.y) && is0(a.z - b.z);
}

const Vector operator + (const Vector &a, const Vector &b){
    return Vector(a.x + b.x, a.y + b.y, a.z + b.z);
}

const Vector operator - (const Vector &a, const Vector &b){
    return Vector(a.x - b.x, a.y - b.y, a.z - b.z);
}

/// 倍乘，就是缩放
const Vector operator * (const Vector &a, T k){
    return Vector(a.x * k, a.y *k, a.z * k);
}

/**
 * @brief 向量a与向量b的叉积
 * @return 令结果为r，则r方向符合右手螺旋定则，长度为平行四边形的面积
 */
const Vector cross(const Vector &a, const Vector &b){
    return Vector(
        a.y * b.z - a.z * b.y, 
        b.x * a.z - a.x * b.z,
        a.x * b.y - b.x * a.y
    );
}

/**
 * @brief a与b的点积
 * @return 令点积结果为r，则 cos(theta) = r / (|a|·|b|)
 *   因此，r为0，说明a垂直b, 
 */
T dot(const Vector &a, const Vector &b){
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
