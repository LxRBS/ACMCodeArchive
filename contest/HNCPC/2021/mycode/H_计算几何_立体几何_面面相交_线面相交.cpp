/**
 *  �ռ�����Բ�����ཻ���߶γ��ȡ�
 *  1 ����ȷ��Բ����ƽ��ķ�����
 *  2 ֪����������������ȷ����ƽ�潻�ߵķ�������
 *  3 ��ʱ����ȷ��ƽ��C1�ڹ�C1���뽻�ߴ�ֱ��һ��ֱ��
 *  3 ���ֱ����C2�Ľ��㣬������˽����ϵ�һ��
 *  4 ��ʱ��ȷ���˽��ߵĲ�������
 *  5 ���ø�ֱ�߷ֱ���Բȥ�ཻ���������4�����㴦��һЩ����
 *  ���ȿ�1E-7��assert��鲻��
 *  ��1E-6������
 */
#include <bits/stdc++.h>
using namespace std;

typedef double Real;
Real const EPS = 1E-6;
Real const PI = acos(-1.0);
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

/// �ռ�������
struct Point{
    Real x, y, z;
    Point(Real a=0,Real b=0,Real c=0):x(a),y(b),z(c){}

    bool input(){return 3 == scanf("%lf%lf%lf", &x, &y, &z);}
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

/// ���������Ĳ��
Point cross(const Vector &a, const Vector &b){
    return Point(a.y * b.z - a.z * b.y, b.x * a.z - a.x * b.z, a.x * b.y - b.x * a.y);
}

/// ���������ĵ��
Real dot(const Vector &a, const Vector &b){
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

/// �ռ������ļн�
Real interAngle(const Vector &a, const Vector &b){
	assert(!a.isZero() && !b.isZero());
    Real cosValue = dot(a, b) / (a.length() * b.length());
	Real ans = myacos(cosValue);
	return ans;
}

/// ��Ԫ��������ⷨ������Ԫ��
struct Quat{
    Real w, x, y, z;
    Quat(Real a=0, Real b=0, Real c=0, Real d=0):w(a),x(b),y(c),z(d){}
    Quat conj()const{return Quat(w, -x, -y, -z);}

	Quat(const Vector&a, const Vector&b):w(0),x(0),y(0),z(0){ // ��a��b����ת��ʾ
        assert(a.isNorm() && b.isNorm()); // ��λ����
        /// ��н�
		Real theta = interAngle(a, b);
		if(is0(theta)){ // ������ת
            w = 1; x = y = z = 0;
		}else if(0==sgn(theta-PI)){ // �պ÷���
            Point axis;
			if(is0(a.x)){
				axis.x = 1, axis.y = axis.z = 0;
			}else{
				axis.y = axis.z = 1;
				axis.x = -(axis.y*a.y + axis.z*a.z) / a.x;
			}
			axis.normSelf();
            w = 0; x = axis.x; y = axis.y; z = axis.z;
		}else{ // ��ͨ��ת��ȷ����ת��
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

/// ��������p�����ߵ�p������r��ת�Ժ������
Point rotate(const Vector &p, const Quat &r){
    Quat origin(0, p.x, p.y, p.z);
    Quat after = r * origin * r.conj();
    assert(is0(after.w));
    return Vector(after.x, after.y, after.z);
}

/// �ռ�ֱ�ߵĲ�������
struct Line{
	Point base;       // ����
	Vector direction; // ����

	Line(const Point &p, const Vector &v):base(p), direction(v){direction.normSelf();}
};

/// ��ά�ռ�ƽ��
struct Plane{
    Real A, B, C, D; // Ax + By + Cz + D = 0
	Plane(Real a=0,Real b=0,Real c=0,Real d=0):A(a),B(b),C(c),D(d){}
    Plane(const Point &p, const Vector &v){ // ����p�Ҵ�ֱ������v��Ψһȷ��һ��ƽ��
        A = v.x; B = v.y; C = v.z;
		D = - (A * p.x + B * p.y + C * p.z);
	}
};

/// �㵽ֱ�ߵ�
inline Real dist(const Point &p, const Plane &plane){
    Real tmp = fabs(plane.A*p.x+plane.B*p.y+plane.C*p.z+plane.D)/sqrt(plane.A*plane.A+plane.B*plane.B+plane.C*plane.C);
	return sgn(tmp) ? tmp : 0;
}

/// ƽ����ֱ���󽻵�
Point inter(const Line &line, const Plane &plane){
    /// ƽ��ķ�����
	Vector n(plane.A, plane.B, plane.C);
	
	Real dotValue = dot(n, line.direction);
	assert(sgn(dotValue)); // ���Ϊ0˵����ֱ��˵��ֱ����ƽ���ڻ���ƽ����ƽ��
	// Real tmp2 = dist(line.base, plane) * n.length() * line.direction.length() / dotValue;

	Real tmp = plane.A * line.base.x + plane.B * line.base.y + plane.C * line.base.z + plane.D;
	tmp /= plane.A * line.direction.x + plane.B * line.direction.y + plane.C * line.direction.z;
	tmp = - tmp;

    // if(!is0(tmp - tmp2)){ // �����ü򵥾�����㣬��Ϊƽ��ķ�������ֱ��������4�ֿ�����
	// 	cout<<tmp<<" "<<tmp2<<endl;
	// 	throw runtime_error("XXXX");
	// }

	return line.base + line.direction * tmp;
}

/// ���Ƿ���ֱ����
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

/// ���Ƿ���ƽ����
inline bool isIn(const Point &p, const Plane &plane){
    return 0 == sgn(plane.A*p.x + plane.B*p.y + plane.C*p.z + plane.D);
}

/// ֱ���Ƿ���ƽ���ϣ�ֱ�ߵķ���������ƽ��ķ�������ֱ�һ�����ƽ����
bool isIn(const Line &line, const Plane &plane){
	return is0(dot(line.direction, Vector(plane.A,plane.B,plane.C)))
	    && is0(plane.A*line.base.x+plane.B*line.base.y+plane.C*line.base.z+plane.D);
}

/// �㵽ֱ�ߵľ���
Real dist(const Point &p, const Line &line){
    if(isIn(p, line)) return 0;

    Vector bp = p - line.base;
	Real touying = dot(bp, line.direction);
	Real d = p.dist(line.base); 
    return mysqrt(d*d - touying*touying);
}

/// ���p��ֱ��line�Ĵ���
Point foot(const Point &p, const Line &line){
    if(isIn(p, line)) return p;

	Real t = dot(Vector(p - line.base), line.direction);
	return line.base + line.direction * t;
}

/// ֱ����ƽ����Բ�ཻ�󽻵�
int inter(const Line &line, const Plane &plane, const Point &center, Real radius, Real ans[]){
    assert(isIn(line, plane) && isIn(center, plane));

    /// Բ�ĵ�ֱ�ߵľ���
	Real d = dist(center, line);
    if(sgn(d-radius) >= 0) return 0;

    /// ��Բ�ĵ�ֱ�ߵĴ���
	Point p = foot(center, line);
	// if(!(isIn(p, line) && is0(dot(line.direction,center-p)))) while(1); // not here
	assert(isIn(p, line) && is0(dot(line.direction,center-p)));

	/// ��ҪҪ֪����������㱾����Բ�����
    Real tfoot = dot(Vector(p - line.base), line.direction);
    Real tmp = mysqrt(radius*radius - d*d);

	ans[0] = tfoot - tmp;
	ans[1] = tfoot + tmp;
	/// ����Ϊ��֤
    Point p1 = line.base + line.direction * ans[0];
	Point p2 = line.base + line.direction * ans[1];

    // if(!(isIn(p1, plane) && is0(radius - center.dist(p1)))) while(1); // not here
	assert(isIn(p1, plane) && is0(radius - center.dist(p1)));

	// if(!(isIn(p2, plane) && is0(radius - center.dist(p2)))) while(1); // not here
	assert(isIn(p2, plane) && is0(radius - center.dist(p2)));

	return 2;
}

Point C1, C2; // Բ��
Vector N1, N2; // ������
Real R1, R2;
const Vector ZP(0, 0, 1); // ָ��z�����������

bool read(){
    if(1 != scanf("%lf", &R1)) return false;

    C1.input(); N1.input();
    scanf("%lf", &R2);
    C2.input(); N2.input();

    Vector tmp = cross(N1, N2);
	// if(tmp.isZero()) while(1);
    assert(!tmp.isZero());
    return true;
}

Real proc(Real a, Real b, Real c, Real d){
    if(sgn(b-c) <= 0) return 0;
    if(sgn(d-a) <= 0) return 0;
    return min(b, d) - max(a, c);	
}

Real proc(){
    if(C1 == C2){
		return 2.0 * min(R1, R2);
	} 

	/// ����ƽ�潻�ߵķ�������
	Vector jiao = cross(N1, N2);	

	/// ����ƽ��C1�ڹ�C1�뽻�ߴ�ֱ��ֱ��
	Vector direction = cross(jiao, N1);
	// if(direction.isZero()) while(1);
	assert(!direction.isZero());
    Line L1(C1, direction);

	/// ƽ��C2
	Plane plane2(C2, N2);

	/// ��L1��C2�Ľ���
	Point p = inter(L1, plane2);
	// if(!(isIn(p, L1) && isIn(p, plane2)))while(1); // here
    assert(isIn(p, L1) && isIn(p, plane2));

	/// ���ھ�ȷ������ƽ��Ľ���
	Line jiaoxian(p, jiao);

	/// �ٿ���ֱ����Բ�ཻ
	Real u[2], v[2];
	if(inter(jiaoxian, plane2, C2, R2, v) != 2) return 0;

	if(inter(jiaoxian, Plane(C1, N1), C1, R1, u) != 2) return 0;

	return proc(u[0], u[1], v[0], v[1]);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    
    while(read()){
        printf("%.12f\n", proc());
    }
	return 0;
}
