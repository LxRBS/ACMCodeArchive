/**
 * 求三维空间两个圆相交
 * 坐标系变换，将第一个圆的圆心作为原点，法向量作为z轴正方向
 * 第二个圆的平面方程为Ax+By+Cz+D=0
 * 于是交线必在xy平面上且方程为Ax+By+D=0
 * 于是变为了二维平面内直线和圆相交。求出交点后，再做一个逆变换回到原始坐标系
 * 这样就能求到4个交点，再处理一下即可
 */ 
#include <bits/stdc++.h>
using namespace std;

typedef long double Real;
Real const EPS = 1E-8;
Real const PI = acos((Real)-1.);
inline int sgn(Real x){return x>EPS?1:(x<-EPS?-1:0);}
inline bool is0(Real x){return 0==sgn(x);}
inline Real myacos(Real x){
    if(x>1) x=1;
    if(x<-1) x=-1;
    return acos(x);
}
inline Real mysqrt(Real x){
	if(is0(x)) return 0;
	return sqrt(x);
}

/// 空间点和向量
struct Point{
    Real x, y, z;
    Point(Real a=0,Real b=0,Real c=0):x(a),y(b),z(c){}

    bool input(){
        int a, b, c;
        if(3 != scanf("%d%d%d", &a, &b, &c)) return false;
        x = a, y = b, z = c;
        return true;
    }
    bool isZero()const{return is0(x) && is0(y) && is0(z);}
	void output(ostream&os=cout)const{cout<<"("<<x<<", "<<y<<", "<<z<<")"<<endl;}

    const Point operator + (const Point&b)const{
        return Point(x+b.x, y+b.y, z+b.z);
    }
    const Point operator - (const Point&b)const{
        return Point(x-b.x, y-b.y, z-b.z);
    }
    const Point operator * (Real c)const{
		return Point(x*c, y*c, z*c);
	}

    bool operator == (const Point&b)const{
        return is0(x-b.x) && is0(y-b.y) && is0(z-b.z);
    }
        
	Real length()const{return sqrt(x*x+y*y+z*z);}
	bool isNorm()const{return 0 == sgn(length()-1);}
	void normSelf(){Real t = length(); x /= t, y /= t, z /= t;}	
	Real dist(const Point &b)const{
		Real tx = x - b.x, ty = y - b.y, tz = z - b.z;
		return sqrt(tx*tx+ty*ty+tz*tz);
	}
};

typedef Point Vector;

/// 空间直线的参数方程
struct Line{
	Point base;       // 基点
	Vector direction; // 方向
    Line(){}
	Line(const Point &p, const Vector &v):base(p), direction(v){direction.normSelf();}
    Line(Real a, Real b, Real c):direction(b,-a,0){ // 确定ax+by+c=0的直线
        direction.normSelf();
        if(is0(a)){
            base.x = 0, base.y = -c / b, base.z = 0;
        }else{
            base.x = -c / a, base.y = 0, base.z = 0;
        }
    }
    Real getT(const Point&p)const{
        if(p == base) return 0;

        Real ans;
        if(!is0(direction.x)) ans = (p.x - base.x) / direction.x;
        else if(!is0(direction.y)) ans = (p.y - base.y) / direction.y;
        else if(!is0(direction.z)) ans = (p.z - base.z) / direction.z;
        else while(1);

        assert(p == base + direction*ans);
        return ans;
    }
};

/// 三维空间平面
struct Plane{
    Real A, B, C, D; // Ax + By + Cz + D = 0
	Plane(Real a=0,Real b=0,Real c=0,Real d=0):A(a),B(b),C(c),D(d){}
    Plane(const Point &p, const Vector &v){ // 过点p且垂直于向量v，唯一确定一个平面
        A = v.x; B = v.y; C = v.z;
		D = - (A * p.x + B * p.y + C * p.z);
	}
};

/// 两个向量的叉积
Point cross(const Vector &a, const Vector &b){
    return Point(a.y * b.z - a.z * b.y, b.x * a.z - a.x * b.z, a.x * b.y - b.x * a.y);
}

/// 两个向量的点积
Real dot(const Vector &a, const Vector &b){
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

/// 空间向量的夹角
Real interAngle(const Vector &a, const Vector &b){
	assert(!a.isZero() && !b.isZero());
    Real cosValue = dot(a, b) / (a.length() * b.length());
	Real ans = myacos(cosValue);
	return ans;
}

/// 点是否在直线上
bool isIn(const Point &p, const Line &line){
    if(p == line.base) return true;

	Vector tmp = p - line.base;

    Real t;
	if(!is0(line.direction.x)) t = tmp.x / line.direction.x;
	else if(!is0(line.direction.y)) t = tmp.y / line.direction.y;
	else if(!is0(line.direction.z)) t = tmp.z / line.direction.z;
	else assert(false); // not here

	return p == line.base + line.direction * t; 
}

/// 直线是否在平面上，直线的方向向量与平面的法向量垂直且基点在平面内
bool isIn(const Line &line, const Plane &plane){
	return is0(dot(line.direction, Vector(plane.A,plane.B,plane.C)))
	    && is0(plane.A*line.base.x+plane.B*line.base.y+plane.C*line.base.z+plane.D);
}

/// 点是否在平面上
inline bool isIn(const Point &p, const Plane &plane){
    return 0 == sgn(plane.A*p.x + plane.B*p.y + plane.C*p.z + plane.D);
}

/// 四元数
struct Quat{
    Real w, x, y, z;
    Quat(Real a=0, Real b=0, Real c=0, Real d=0):w(a),x(b),y(c),z(d){}
    Quat conj()const{return Quat(w, -x, -y, -z);}

	Quat(const Vector&a, const Vector&b):w(0),x(0),y(0),z(0){ // 从a到b的旋转表示
        assert(a.isNorm() && b.isNorm()); // 单位向量
        /// 求夹角
		Real theta = interAngle(a, b);
		if(is0(theta)){ // 不用旋转
            w = 1; x = y = z = 0;
		}else if(0==sgn(theta-PI)){ // 刚好反向
            Point axis;
			if(is0(a.x)){
				axis.x = 1, axis.y = axis.z = 0;
			}else{
				axis.y = axis.z = 1;
				axis.x = -(axis.y*a.y + axis.z*a.z) / a.x;
			}
			axis.normSelf();
            w = 0; x = axis.x; y = axis.y; z = axis.z;
		}else{ // 普通旋转，确定旋转轴
            theta *= 0.5;
			Point axis = cross(a, b);			
			axis.normSelf();
            w = cos(theta); 
			x = axis.x * sin(theta);
			y = axis.y * sin(theta);
			z = axis.z * sin(theta);
		}
	}
};

const Quat operator * (const Quat&lhs, const Quat&rhs){
    return Quat(
            lhs.w*rhs.w-lhs.x*rhs.x-lhs.y*rhs.y-lhs.z*rhs.z,
            lhs.w*rhs.x+lhs.x*rhs.w+lhs.y*rhs.z-lhs.z*rhs.y,
            lhs.w*rhs.y-lhs.x*rhs.z+lhs.y*rhs.w+lhs.z*rhs.x,
            lhs.w*rhs.z+lhs.x*rhs.y-lhs.y*rhs.x+lhs.z*rhs.w
        );
}

/// 给定向量p，或者点p，经过r旋转以后的向量
Point rotate(const Vector &p, const Quat &r){
    Quat origin(0, p.x, p.y, p.z);
    Quat after = r * origin * r.conj();
    assert(is0(after.w));
    return Vector(after.x, after.y, after.z);
}

/// 解一元二次方程
int f(Real a, Real b, Real c, Real&x1, Real&x2){
    Real d = b*b - 4.0*a*c;
    int t = sgn(d);
    if(t<0) return 0;
    if(0==t){
        x1 = x2 = -b / (a+a);
        return 1;
    }
    d = sqrt(d);
    x1 = (-b-d)/(a+a);
    x2 = (-b+d)/(a+a);
    return 2;
}

int proc(Point tobeO, Vector tobeZ, Point circle, Vector n, Real radius, Point &p1, Point &p2){
    static const Vector ZPOS(0, 0, 1);

    tobeZ.normSelf();
    Quat ro(tobeZ, ZPOS);

    circle = circle - tobeO;
    circle = rotate(circle, ro);
    n = rotate(n, ro);

    Plane plane2(circle, n);
    Line line(plane2.A, plane2.B, plane2.D);

    Real t1, t2;
    int cnt = f(1, 2.0*(line.base.x*line.direction.x+line.base.y*line.direction.y),line.base.x*line.base.x+line.base.y*line.base.y-radius*radius,t1,t2);
    if(cnt < 2) return 0;

    p1 = line.base + line.direction * t1;
    p2 = line.base + line.direction * t2;

    /// 逆变换
    ro = ro.conj();
    p1 = rotate(p1, ro);
    p1 = p1 + tobeO;
    p2 = rotate(p2, ro);
    p2 = p2 + tobeO;

    return 2;
}

Real proc(const Point&p1, const Point&p2, const Point&p3, const Point&p4){
    /// 首先确定直线
    Vector direction(p1 - p2); // p1 p2肯定不相等
    
    Line line(p1, direction);
    assert(isIn(p3, line));
    assert(isIn(p4, line));

    Real t1 = 0;
    Real t2 = line.getT(p2);
    Real t3 = line.getT(p3);
    Real t4 = line.getT(p4);

    if(t1 > t2) swap(t1, t2);
    if(t3 > t4) swap(t3, t4);

    if(sgn(t2 - t3) <= 0) return 0;
    if(sgn(t4 - t1) <= 0) return 0;

    return min(t2, t4) - max(t1, t3);
}

Point C1, C2; // 圆心
Vector N1, N2; // 法向量
Real R1, R2;

bool read(){
    int r;
    if(1 != scanf("%d", &r)) return false;
    R1 = r;

    C1.input(); N1.input();
    scanf("%d", &r);
    R2 = r;
    C2.input(); N2.input();

    Point tmp = cross(N1, N2);
    assert(!is0(tmp.x) || !is0(tmp.y) || !is0(tmp.z));
    return true;
}

Real proc(){
    if(C1 == C2){
        return 2.0 * min(R1, R2);
    }
    
    Point p1, p2;
    int cnt1 = proc(C1, N1, C2, N2, R1, p1, p2);
    if(cnt1 < 2) return 0;

    Point p3, p4;
    int cnt2 = proc(C2, N2, C1, N1, R2, p3, p4); 
    if(cnt2 < 2) return 0;

    return proc(p1, p2, p3, p4);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif
    while(read()){
        // printf("%.12f\n", proc());
        printf("%.12Lf\n", proc());
    }
    return 0;
}