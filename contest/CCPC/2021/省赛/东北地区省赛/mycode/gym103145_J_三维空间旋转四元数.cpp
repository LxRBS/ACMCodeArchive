/**
 *  给定点和旋转轴，点绕旋转轴分别旋转正负r角度得到两个点
 *  输出z坐标大的。四元数旋转
 *  用C++输出显著慢于C输出在CF上
 *  1341ms vs 124ms
 */
#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
int const SIZE = 13;
#else
int const SIZE = 2E3+10;
#endif

/**
 * @brief 立体几何，点线面向量模板
 * 1. typedef和常数
 * 2. 处理边界的数学库函数
 * 3. 点与向量的结构体以及基本运算，相等，加减乘，叉积，点积
 * 4. 线面的结构体
 * 5. 位置关系函数，一律用relation做函数名，常数，点线，点面，线线，线面，面面
 * 6. 求距离，一律用dist做函数名，返回Real，点点，点线，点面，线线，线面，面面
 * 7. 相交求公共部分，一律用inter做函数名，线线，线面，面面
 * 8. 求夹角，一律用angle做函数名， 线线，线面，面面
 * 9. 四元数与三维方阵，用于空间旋转，包括旋转，得到旋转表示以及相互转化
 */

/** 1. typdef和常数 **/
using Real = long double;
using llt = long long;
using coordinate_type = Real; // 点坐标的类型，一般都用Real

Real const EPS = 1E-6; // 根据需要调整
Real const PI = acos(-1);

inline int sgn(Real x){return x >= EPS ? 1 : (x <= -EPS ? -1 : 0);}
inline bool is0(Real x){return 0 == sgn(x);}

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
/// 点
struct Point{
    coordinate_type x, y, z;
    Point(coordinate_type a=0, coordinate_type b=0, coordinate_type c=0):x(a),y(b),z(c){}
    Real length() const { // 向量的长度
        return mysqrt(this->x * this->x + this->y * this->y + this->z * this->z);
    }
    bool isZero() const { // 是否为零向量
        return is0(this->x) && is0(this->y) && is0(this->z);
    }
    bool input(){ // 输入函数
        if(cin >> x >> y >> z) return true;
        return false;
    }
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
const Vector operator * (const Vector &a, coordinate_type k){
    return Vector(a.x * k, a.y *k, a.z * k);
}

/// 叉积，右手螺旋
const Vector cross(const Vector &a, const Vector &b){
    return Vector(
        a.y * b.z - a.z * b.y, 
        b.x * a.z - a.x * b.z,
        a.x * b.y - b.x * a.y
    );
}

/// 点积
coordinate_type dot(const Vector &a, const Vector &b){
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

/// 线，空间直线由基点和方向向量构成
struct Line{
    Point base;
    Vector direction; // 如果采用实数坐标，方向向量最好单位化
    Line():base(), direction(){}
    /// 注意是基点、方向向量，而不是两点确定一条直线
    Line(const Point&a, const Vector&b): base(a), direction(b){}
};

/// 面, Ax+By+Cz+D=0
struct Plane{
    coordinate_type A, B, C, D;
    const Point inner; // 平面内一点 
    Plane():A(0), B(0), C(0), D(0), inner(){}
    /// 平面内一点p以及法向量n，确定一个平面， n不能为零向量
    Plane(const Point &p, const Vector&n):inner(p){
        this->create(p, n);
    }    
    /// 异线三点确定一个平面
    Plane(const Point &a, const Point &b, const Point &c):inner(a){
        this->create(a, cross(b - a, c - a));
    }
    /// 给定点和方向向量，生成平面
    void create(const Point &p, const Vector&n){
        assert(!n.isZero());
        this->A = n.x; this->B = n.y; this->C = n.z;
        this->D = -(this->A * p.x + this->B * p.y + this->C * p.z);        
    }
    Vector norm()const{ // 法向量
        return Vector(this->A, this->B, this->C);
    }    
    /// 返回平面内一点
    Point one()const{return this->inner;}
};

/** 5. 位置关系函数 **/
/// 常数
int const OUT = 0; // 表示不在，点线
int const IN = 1;  // 表示在，点线，线面
int const CHONGHE = 2; // 重合，线线，面面
int const PINGXING = 4; // 平行，线线，线面
int const YIMIAN = 8; // 异面,线线
int const INTER = 0x10; // 相交，线线，线面，面面

/// 点线，点p与直线line的位置关系，如果点在直线上，还能返回p在该直线上的参数
/// 即 p = line.base + line.direction * k
/// 注意k是本直线方向向量长度的倍数，不同直线直接比较，必须事先将所有方向向量单位化
/// 如果不想要这个参数值，不传pk即可
int relation(const Point &p, const Line &line, Real *pk=nullptr){
    if(p == line.base) return pk != nullptr ? (*pk = 0, IN) : IN; // 点在直线上

    Vector tmp = p - line.base;
    Real t;
    if(sgn(line.direction.x)) t = tmp.x / line.direction.x;
    else if(sgn(line.direction.y)) t = tmp.y / line.direction.y;
    else if(sgn(line.direction.z)) t = tmp.z / line.direction.z;
    else throw runtime_error("never should be here");

    if(pk != nullptr) *pk = t;
    return p == line.base + line.direction * t ? IN : OUT;
}

/// 点面关系
int relation(const Point &p, const Plane &plane){
    Real tmp = plane.A * p.x + plane.B * p.y + plane.C * p.z + plane.D;
    return is0(tmp) ? IN : OUT;
}

/// 线线关系，重合，平行，相交，异面，其中前三项是共面
int relation(const Line &a, const Line &b){
    Vector chaji = cross(a.direction, b.direction);
    if(chaji.isZero()){
        if(IN == relation(a.base, b)){
            assert(IN == relation(b.base, a));
            return CHONGHE; // 两条直线重合
        }
        return PINGXING; // 两直线平行
    }
    /// 两直线上各取一点，M和N
    Point M = a.base + a.direction;
    Point N = b.base + b.direction;
    if(M == N) return INTER;
    
    /// 计算(MN x a).b，如果为0，说明两直线相交
    /// MN x a 实际上就是两条直线的公垂向量
    Vector MN = N - M;
    if(is0(dot(b.direction, cross(a.direction, MN)))){
        return INTER;
    }
    return YIMIAN;
}

/// 线面关系，在，平行，相交
int relation(const Line &line, const Plane &plane){
    Vector n = plane.norm();
    if(is0(dot(n, line.direction))){ // 说明直线垂直于平面的法向量
        if(IN == relation(line.base, plane)){ 
            return IN; // 直线在平面内
        }
        return PINGXING; // 直线平行于平面
    }
    return INTER; // 直线与平面相交
}

/// 面面关系，重合，平行，相交
int relation(const Plane &a, const Plane &b){
	Vector chaji = cross(a.norm(), b.norm());
	if(chaji.isZero()){
		Real dist(const Point &, const Plane &); // 前置声明
		Real d = dist(a.one(), b);
		if(is0(d)){
			assert(is0(dist(b.one(), b)));
			return CHONGHE;
		}
		return PINGXING;
	}
    return INTER;
}

/** 6. 求距离，一律用dist做函数名，点点，点线，点面，线线，线面，面面 **/
inline Real dist(const Point &a, const Point &b){
    return (a - b).length(); 
}

inline Real dist(const Point &p, const Line &line){
    return cross(p - line.base, line.direction).length() / line.direction.length();
}

/// 点面距离
Real dist(const Point &p, const Plane &plane){
    Real tmp = fabs(plane.A * p.x + plane.B * p.y + plane.C * p.z + plane.D);   
    tmp /= mysqrt(plane.A*plane.A+plane.B*plane.B+plane.C*plane.C);
    return sgn(tmp) ? tmp : 0;
}

/// 重合与相交直线距离为0
/// 异面直线的距离 = 公垂向量 . 连接向量 / |公垂向量|
inline Real dist(const Line &a, const Line &b){
    int r = relation(a, b);
    if(r & (CHONGHE | INTER)) return 0;
    /// 平行直线，任取一点计算点线距离即可
    if(r & PINGXING){
        Real tmp = dist(a.base, b);
        assert(is0(tmp - dist(b.base, a)));
        return tmp;
    }
    /// 异面直线求距离
    Vector gongchui = cross(a.direction, b.direction);
    Vector lianjie = b.base - a.base;
    Real tmp = dot(gongchui, lianjie) / gongchui.length();
    return tmp;
}

/// 线面距离，平行才有距离，相交或者在面内距离为0
inline Real dist(const Line &line, const Plane &plane){
    int r = relation(line, plane);
    if(r & (IN | INTER)){
        return 0;
    }

    Real tmp = dist(line.base, plane);
    return tmp;
}

/// 面面距离
inline Real dist(const Plane &a, const Plane &b){
    int r = relation(a, b);
    if(r & (CHONGHE | INTER)){
        return 0;
    }
    Real tmp = fabs(a.D - b.D);
    tmp /= mysqrt(a.A * a.A + a.B * a.B + a.C * a.C);
    assert(is0(dist(a.one(), b) - tmp));
    return tmp;
}

/** 7. 相交求公共部分，一律用inter做函数名，线线，线面，面面，事先需要保证相交 **/
/// 线线相交求交点
Point inter(const Line &a, const Line &b){
    Real d = dist(b.base, a); // 求出b.base到直线a的距离     
    /// 求两直线的夹角的正弦值
    Real sinvalue = cross(a.direction, b.direction).length() / (a.direction.length() * b.direction.length());
    /// b.base到交点的距离可以求出
    Real tmp = d / sinvalue;
	tmp /= b.direction.length(); // 一定要相对方向向量单位化
    Point p = b.base + b.direction * tmp;
    if(relation(p, a) & IN){ // 如果p也在a上，交点就是p
        return p;
    }
    /// 必须是另一个p点
    p = b.base + b.direction * -tmp;
    assert(relation(p, a) & IN);
    return p;
}

/// 线面求交点，交点的参数 = dot(面法向量, 平面点-直线点) / dot(面法向量，线方向向量)
Point inter(const Line &line, const Plane &plane){
    Real tmp = dot(plane.norm(), plane.one() - line.base) / dot(plane.norm(), line.direction);
    Point p = line.base + line.direction * tmp; 
    assert((IN & relation(p, line)) && (IN & relation(p, plane)));
    return p;
}

/// 面面相交求交线
Line inter(const Plane &a, const Plane &b){
    /// 首先求出交线的方向向量
    Vector d = cross(a.norm(), b.norm());
    /// 然后求出平面a内与交线垂直的某条直线
    Line mou(a.one(), cross(a.norm(), d));
    /// 求出某直线与平面b的交点
    Point jiaodian = inter(mou, b);
    Line line(jiaodian, d);
    assert((IN & relation(line, a)) && (IN & relation(line, b)));
    return line;
}

/** 8. 求夹角，一律用angle做函数名 **/
/// 空间向量夹角，返回在[0, Pi]
inline Real angle(const Vector &a, const Vector &b){
    Real cosvalue = dot(a, b) / (a.length() * b.length());
    return myacos(cosvalue);
}
/// 直线夹角，返回在[0, PI/2]
inline Real angle(const Line &a, const Line &b){
    Real tmp = angle(a.direction, b.direction);
    if(sgn(tmp - 0.5 * PI) > 0) tmp = PI - tmp;
    return tmp;
}
/// 线面夹角，返回在[0, PI/2]
inline Real angle(const Line &a, const Plane &plane){
    Real tmp = angle(a.direction, plane.norm());
    if(sgn(tmp - 0.5 * PI) > 0){
        tmp = PI - 0.5 * PI;
    } 
    tmp = 0.5 * PI - tmp;
    return tmp;
}
/// 面面夹角
inline Real angle(const Plane &a, const Plane &b){
    if(relation(a, b) & (CHONGHE | PINGXING)){
        return 0;
    }
    Vector d = cross(a.norm(), b.norm());
    Line la(a.one(), cross(a.norm(), d));
    Line lb(b.one(), cross(b.norm(), d));
    Real tmp = angle(la, lb);
    return tmp;
}

/** 9. 四元数与三维方阵 **/
struct Matrix{
    Real data[3][3];    
};

/// 绕r轴旋转a角的四元数为[cos(a/2), r.x*sin(a/2), r.y*sin(a/2), r.z*sin(a/2)]
/// 其中r必须是单位向量
struct Quat{
    Real w, x, y, z;
    Quat(Real a=0, Real b=0, Real c=0, Real d=0):w(a),x(b),y(c),z(d){}
    Quat conj()const{ // 返回共轭
        return Quat(w, -x, -y, -z);
    }
    /// 从向量a旋转到向量b，得到表示该旋转的四元数，a、b必须是单位向量
    /// 只转180度及以内的角度
    /// 实际上给定起点和终点有无数种旋转方式，这里只是给出了其中一种
    Quat(const Vector &a, const Vector &b){
        assert(is0(a.length() - 1) && is0(b.length() - 1));
        Real theta = angle(a, b);
        if(is0(theta)){
            w = 1, x = y = z = 0;
        }else if(0 == sgn(theta - PI)){ // 转180度
            Point axis;
			if(is0(a.x)){
				axis.x = 1, axis.y = axis.z = 0;
			}else{
				axis.y = axis.z = 1;
				axis.x = -(axis.y*a.y + axis.z*a.z) / a.x;
			}
			axis.normSelf();
            w = 0; x = axis.x; y = axis.y; z = axis.z;   
        }else{ // 普通旋转
            theta *= 0.5;
			Point axis = cross(a, b); // 首先确定旋转轴			
			axis.normSelf();
            w = cos(theta); 
			x = axis.x * sin(theta);
			y = axis.y * sin(theta);
			z = axis.z * sin(theta);
        }
        return;
    }
};

/// 四元数的乘法
const Quat operator * (const Quat&lhs, const Quat&rhs){
    return Quat(
        lhs.w*rhs.w-lhs.x*rhs.x-lhs.y*rhs.y-lhs.z*rhs.z,
        lhs.w*rhs.x+lhs.x*rhs.w+lhs.y*rhs.z-lhs.z*rhs.y,
        lhs.w*rhs.y-lhs.x*rhs.z+lhs.y*rhs.w+lhs.z*rhs.x,
        lhs.w*rhs.z+lhs.x*rhs.y-lhs.y*rhs.x+lhs.z*rhs.w
    );
}

/// 给定向量v，旋转r后得到的向量
Vector rotate(const Vector &v, const Quat &r){
	assert(is0(r.w*r.w+r.x*r.x+r.y*r.y+r.z*r.z-1));
    Quat origin(0, v.x, v.y, v.z);
    Quat after = r * origin * r.conj();
    assert(is0(after.w));
    return Vector(after.x, after.y, after.z);
}

/// 给定向量v，给定旋转矩阵m，求旋转后的向量
Vector rotate(const Vector &v, const Matrix &m){
    return Vector(
        m.data[0][0] * v.x + m.data[0][1] * v.y + m.data[0][2] * v.z,
        m.data[1][0] * v.x + m.data[1][1] * v.y + m.data[1][2] * v.z,
        m.data[2][0] * v.x + m.data[2][1] * v.y + m.data[2][2] * v.z
    );
}

/// 根据旋转矩阵得到等价的四元数，来自某本书的公式
void matrix2Quat(const Matrix &mat, Quat &q){
    Real tq[4];
    tq[0] = 1. + mat.data[0][0] + mat.data[1][1] + mat.data[2][2];
    tq[1] = 1. + mat.data[0][0] - mat.data[1][1] - mat.data[2][2];
    tq[2] = 1. - mat.data[0][0] + mat.data[1][1] - mat.data[2][2];
    tq[3] = 1. - mat.data[0][0] - mat.data[1][1] + mat.data[2][2];

    int k = 0;
    for(int i=1;i<4;++i)if(tq[k]<tq[i])k=i;

    if ( 0 == k ){
        q.w = tq[0];
        q.x = mat.data[1][2] - mat.data[2][1];
        q.y = mat.data[2][0] - mat.data[0][2];
        q.z = mat.data[0][1] - mat.data[1][0];
    }else if ( 1 == k ){
        q.w = mat.data[1][2] - mat.data[2][1];
        q.x = tq[1];
        q.y = mat.data[0][1] + mat.data[1][0];
        q.z = mat.data[2][0] + mat.data[0][2];
    }else if ( 2 == k ){
        q.w = mat.data[2][0] - mat.data[0][2];
        q.x = mat.data[0][1] + mat.data[1][0];
        q.y = tq[2];
        q.z = mat.data[1][2] + mat.data[2][1];
    }else if ( 3 == k ){
        q.w = mat.data[0][1] - mat.data[1][0];
        q.x = mat.data[2][0] + mat.data[0][2];
        q.y = mat.data[1][2] + mat.data[2][1];
        q.z = tq[3];
    }else{
        while(1);
    }

    Real s = sqrt( 0.25 / tq[k] );
    q.w *= s, q.x *= s, q.y *= s, q.z *= s;    
}

/// 等价旋转的四元数转旋转矩阵
void quat2Matrix(const Quat &q, Matrix &m){
    m.data[0][0] = 1 - 2.0 * (q.y * q.y + q.z * q.z);
    m.data[0][1] = 2.0 * (q.x * q.y + q.w * q.z);
    m.data[0][2] = 2.0 * (q.x * q.z - q.w * q.y);

    m.data[1][0] = 2.0 * (q.x * q.y - q.w * q.z);
    m.data[1][1] = 1 - 2.0 * (q.x * q.x + q.z * q.z);
    m.data[1][2] = 2.0 * (q.y * q.z + q.w * q.x);

    m.data[2][0] = 2.0 * (q.x * q.z + q.w * q.y);    
    m.data[2][1] = 2.0 * (q.y * q.z - q.w * q.x);
    m.data[2][2] = 1 - 2.0 * (q.y * q.y + q.x * q.x);
}

Vector Axis;
Point P;
Real Jiaodu;

void proc(){
	Jiaodu = Jiaodu * PI / 180;
	Jiaodu *= 0.5;

	Real cosvalue = cos(Jiaodu);
	Real sinvalue = sin(Jiaodu);

	Axis.normSelf();

    /// 旋转四元数
	Quat q(cosvalue, Axis.x*sinvalue, Axis.y*sinvalue, Axis.z*sinvalue);
	/// 旋转
	Point p1 = rotate(P, q);
	Point p2 = rotate(P, q.conj());
	/// 输出
	if(sgn(p1.z - p2.z) >= 0){
		return (void)(cout << fixed << setprecision(12) << p1.x << " " << p1.y << " " << p1.z << endl);
	}
	return (void)(cout << fixed << setprecision(12) << p2.x << " " << p2.y << " " << p2.z << endl);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif  
    ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int nofkase; cin >> nofkase; 
	while(nofkase--){
        Axis.input();
		P.input();
		cin >> Jiaodu;
		proc();
	}
    return 0;
}
