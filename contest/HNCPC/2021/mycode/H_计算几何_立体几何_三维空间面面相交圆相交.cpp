/**
 * ��ά�ռ��ڸ�������Բ�����ߵĳ���
 * ��������Բ����ƽ��Ľ���
 * Ȼ��ֱ�����ý���������Բ�Ľ��㣬Ȼ����ݽ����������һ��
 */
#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
int const SIZE = 13;
#else
int const SIZE = 2E3+10;
#endif

/**
 * @brief ���弸�Σ�����������ģ��
 * 1. typedef�ͳ���
 * 2. ����߽����ѧ�⺯��
 * 3. ���������Ľṹ���Լ��������㣬��ȣ��Ӽ��ˣ���������
 * 4. ����Ľṹ��
 * 5. λ�ù�ϵ������һ����relation�������������������ߣ����棬���ߣ����棬����
 * 6. ����룬һ����dist��������������Real����㣬���ߣ����棬���ߣ����棬����
 * 7. �ཻ�󹫹����֣�һ����inter�������������ߣ����棬����
 * 8. ��нǣ�һ����angle���������� ���ߣ����棬����
 * 9. ��Ԫ������ά�������ڿռ���ת��������ת���õ���ת��ʾ�Լ��໥ת��
 */

/** 1. typdef�ͳ��� **/
using Real = long double;
using llt = long long;
using coordinate_type = Real; // ����������ͣ�һ�㶼��Real

Real const EPS = 1E-6; // ������Ҫ����
Real const PI = acos(-1);

inline int sgn(Real x){return x >= EPS ? 1 : (x <= -EPS ? -1 : 0);}
inline bool is0(Real x){return 0 == sgn(x);}

/** 2. ����߽����ѧ�⺯�� **/
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

/** 3. ���������Ľṹ���Լ��������㣬��ȣ��Ӽ��ˣ��������� **/
/// ��
struct Point{
    coordinate_type x, y, z;
    Point(coordinate_type a=0, coordinate_type b=0, coordinate_type c=0):x(a),y(b),z(c){}
    Real length() const { // �����ĳ���
        return mysqrt(this->x * this->x + this->y * this->y + this->z * this->z);
    }
    bool isZero() const { // �Ƿ�Ϊ������
        return is0(this->x) && is0(this->y) && is0(this->z);
    }
    bool input(){ // ���뺯��
        if(cin >> x >> y >> z) return true;
        return false;
    }
    void normSelf(){ // ��λ�����������ͱ�����Real���ܵ����������
        assert(!this->isZero());
        Real tmp = this->length();
        this->x /= tmp;
        this->y /= tmp;
        this->z /= tmp;
    }
};
/// ���������ǵ�
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

/// ���ˣ���������
const Vector operator * (const Vector &a, coordinate_type k){
    return Vector(a.x * k, a.y *k, a.z * k);
}

/// �������������
const Vector cross(const Vector &a, const Vector &b){
    return Vector(
        a.y * b.z - a.z * b.y, 
        b.x * a.z - a.x * b.z,
        a.x * b.y - b.x * a.y
    );
}

/// ���
coordinate_type dot(const Vector &a, const Vector &b){
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

/// �ߣ��ռ�ֱ���ɻ���ͷ�����������
struct Line{
    Point base;
    Vector direction; // �������ʵ�����꣬����������õ�λ��
    Line():base(), direction(){}
    /// ע���ǻ��㡢��������������������ȷ��һ��ֱ��
    Line(const Point&a, const Vector&b): base(a), direction(b){}
};

/// ��, Ax+By+Cz+D=0
struct Plane{
    coordinate_type A, B, C, D;
    const Point inner; // ƽ����һ�� 
    Plane():A(0), B(0), C(0), D(0), inner(){}
    /// ƽ����һ��p�Լ�������n��ȷ��һ��ƽ�棬 n����Ϊ������
    Plane(const Point &p, const Vector&n):inner(p){
        this->create(p, n);
    }    
    /// ��������ȷ��һ��ƽ��
    Plane(const Point &a, const Point &b, const Point &c):inner(a){
        this->create(a, cross(b - a, c - a));
    }
    /// ������ͷ�������������ƽ��
    void create(const Point &p, const Vector&n){
        assert(!n.isZero());
        this->A = n.x; this->B = n.y; this->C = n.z;
        this->D = -(this->A * p.x + this->B * p.y + this->C * p.z);        
    }
    Vector norm()const{ // ������
        return Vector(this->A, this->B, this->C);
    }    
    /// ����ƽ����һ��
    Point one()const{return this->inner;}
};

/** 5. λ�ù�ϵ���� **/
/// ����
int const OUT = 0; // ��ʾ���ڣ�����
int const IN = 1;  // ��ʾ�ڣ����ߣ�����
int const CHONGHE = 2; // �غϣ����ߣ�����
int const PINGXING = 4; // ƽ�У����ߣ�����
int const YIMIAN = 8; // ����,����
int const INTER = 0x10; // �ཻ�����ߣ����棬����

/// ���ߣ���p��ֱ��line��λ�ù�ϵ���������ֱ���ϣ����ܷ���p�ڸ�ֱ���ϵĲ���
/// �� p = line.base + line.direction * k
/// ע��k�Ǳ�ֱ�߷����������ȵı�������ֱͬ��ֱ�ӱȽϣ��������Ƚ����з���������λ��
/// �������Ҫ�������ֵ������pk����
int relation(const Point &p, const Line &line, Real *pk=nullptr){
    if(p == line.base) return pk != nullptr ? (*pk = 0, IN) : IN; // ����ֱ����

    Vector tmp = p - line.base;
    Real t;
    if(sgn(line.direction.x)) t = tmp.x / line.direction.x;
    else if(sgn(line.direction.y)) t = tmp.y / line.direction.y;
    else if(sgn(line.direction.z)) t = tmp.z / line.direction.z;
    else throw runtime_error("never should be here");

    if(pk != nullptr) *pk = t;
    return p == line.base + line.direction * t ? IN : OUT;
}

/// �����ϵ
int relation(const Point &p, const Plane &plane){
    Real tmp = plane.A * p.x + plane.B * p.y + plane.C * p.z + plane.D;
    return is0(tmp) ? IN : OUT;
}

/// ���߹�ϵ���غϣ�ƽ�У��ཻ�����棬����ǰ�����ǹ���
int relation(const Line &a, const Line &b){
    Vector chaji = cross(a.direction, b.direction);
    if(chaji.isZero()){
        if(IN == relation(a.base, b)){
            assert(IN == relation(b.base, a));
            return CHONGHE; // ����ֱ���غ�
        }
        return PINGXING; // ��ֱ��ƽ��
    }
    /// ��ֱ���ϸ�ȡһ�㣬M��N
    Point M = a.base + a.direction;
    Point N = b.base + b.direction;
    if(M == N) return INTER;
    
    /// ����(MN x a).b�����Ϊ0��˵����ֱ���ཻ
    /// MN x a ʵ���Ͼ�������ֱ�ߵĹ�������
    Vector MN = N - M;
    if(is0(dot(b.direction, cross(a.direction, MN)))){
        return INTER;
    }
    return YIMIAN;
}

/// �����ϵ���ڣ�ƽ�У��ཻ
int relation(const Line &line, const Plane &plane){
    Vector n = plane.norm();
    if(is0(dot(n, line.direction))){ // ˵��ֱ�ߴ�ֱ��ƽ��ķ�����
        if(IN == relation(line.base, plane)){ 
            return IN; // ֱ����ƽ����
        }
        return PINGXING; // ֱ��ƽ����ƽ��
    }
    return INTER; // ֱ����ƽ���ཻ
}

/// �����ϵ���غϣ�ƽ�У��ཻ
int relation(const Plane &a, const Plane &b){
	Vector chaji = cross(a.norm(), b.norm());
	if(chaji.isZero()){
		Real dist(const Point &, const Plane &); // ǰ������
		Real d = dist(a.one(), b);
		if(is0(d)){
			assert(is0(dist(b.one(), b)));
			return CHONGHE;
		}
		return PINGXING;
	}
    return INTER;
}

/** 6. ����룬һ����dist������������㣬���ߣ����棬���ߣ����棬���� **/
inline Real dist(const Point &a, const Point &b){
    return (a - b).length(); 
}

inline Real dist(const Point &p, const Line &line){
    return cross(p - line.base, line.direction).length() / line.direction.length();
}

/// �������
Real dist(const Point &p, const Plane &plane){
    Real tmp = fabs(plane.A * p.x + plane.B * p.y + plane.C * p.z + plane.D);   
    tmp /= mysqrt(plane.A*plane.A+plane.B*plane.B+plane.C*plane.C);
    return sgn(tmp) ? tmp : 0;
}

/// �غ����ֱཻ�߾���Ϊ0
/// ����ֱ�ߵľ��� = �������� . �������� / |��������|
inline Real dist(const Line &a, const Line &b){
    int r = relation(a, b);
    if(r & (CHONGHE | INTER)) return 0;
    /// ƽ��ֱ�ߣ���ȡһ�������߾��뼴��
    if(r & PINGXING){
        Real tmp = dist(a.base, b);
        assert(is0(tmp - dist(b.base, a)));
        return tmp;
    }
    /// ����ֱ�������
    Vector gongchui = cross(a.direction, b.direction);
    Vector lianjie = b.base - a.base;
    Real tmp = dot(gongchui, lianjie) / gongchui.length();
    return tmp;
}

/// ������룬ƽ�в��о��룬�ཻ���������ھ���Ϊ0
inline Real dist(const Line &line, const Plane &plane){
    int r = relation(line, plane);
    if(r & (IN | INTER)){
        return 0;
    }

    Real tmp = dist(line.base, plane);
    return tmp;
}

/// �������
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

/** 7. �ཻ�󹫹����֣�һ����inter�������������ߣ����棬���棬������Ҫ��֤�ཻ **/
/// �����ཻ�󽻵�
Point inter(const Line &a, const Line &b){
    Real d = dist(b.base, a); // ���b.base��ֱ��a�ľ���     
    /// ����ֱ�ߵļнǵ�����ֵ
    Real sinvalue = cross(a.direction, b.direction).length() / (a.direction.length() * b.direction.length());
    /// b.base������ľ���������
    Real tmp = d / sinvalue;
	tmp /= b.direction.length(); // һ��Ҫ��Է���������λ��
    Point p = b.base + b.direction * tmp;
    if(relation(p, a) & IN){ // ���pҲ��a�ϣ��������p
        return p;
    }
    /// ��������һ��p��
    p = b.base + b.direction * -tmp;
    assert(relation(p, a) & IN);
    return p;
}

/// �����󽻵㣬����Ĳ��� = dot(�淨����, ƽ���-ֱ�ߵ�) / dot(�淨�������߷�������)
Point inter(const Line &line, const Plane &plane){
    Real tmp = dot(plane.norm(), plane.one() - line.base) / dot(plane.norm(), line.direction);
    Point p = line.base + line.direction * tmp; 
    assert((IN & relation(p, line)) && (IN & relation(p, plane)));
    return p;
}

/// �����ཻ����
Line inter(const Plane &a, const Plane &b){
    /// ����������ߵķ�������
    Vector d = cross(a.norm(), b.norm());
    /// Ȼ�����ƽ��a���뽻�ߴ�ֱ��ĳ��ֱ��
    Line mou(a.one(), cross(a.norm(), d));
    /// ���ĳֱ����ƽ��b�Ľ���
    Point jiaodian = inter(mou, b);
    Line line(jiaodian, d);
    assert((IN & relation(line, a)) && (IN & relation(line, b)));
    return line;
}

/** 8. ��нǣ�һ����angle�������� **/
/// �ռ������нǣ�������[0, Pi]
inline Real angle(const Vector &a, const Vector &b){
    Real cosvalue = dot(a, b) / (a.length() * b.length());
    return myacos(cosvalue);
}
/// ֱ�߼нǣ�������[0, PI/2]
inline Real angle(const Line &a, const Line &b){
    Real tmp = angle(a.direction, b.direction);
    if(sgn(tmp - 0.5 * PI) > 0) tmp = PI - tmp;
    return tmp;
}
/// ����нǣ�������[0, PI/2]
inline Real angle(const Line &a, const Plane &plane){
    Real tmp = angle(a.direction, plane.norm());
    if(sgn(tmp - 0.5 * PI) > 0){
        tmp = PI - 0.5 * PI;
    } 
    tmp = 0.5 * PI - tmp;
    return tmp;
}
/// ����н�
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

/** 9. ��Ԫ������ά���� **/
struct Matrix{
    Real data[3][3];    
};

struct Quat{
    Real w, x, y, z;
    Quat(Real a=0, Real b=0, Real c=0, Real d=0):w(a),x(b),y(c),z(d){}
    Quat conj()const{ // ���ع���
        return Quat(w, -x, -y, -z);
    }
    /// ������a��ת������b���õ���ʾ����ת����Ԫ����a��b�����ǵ�λ����
    /// ֻת180�ȼ����ڵĽǶ�
    /// ʵ���ϸ��������յ�����������ת��ʽ������ֻ�Ǹ���������һ��
    Quat(const Vector &a, const Vector &b){
        assert(is0(a.length() - 1) && is0(b.length() - 1));
        Real theta = angle(a, b);
        if(is0(theta)){
            w = 1, x = y = z = 0;
        }else if(0 == sgn(theta - PI)){ // ת180��
            Point axis;
			if(is0(a.x)){
				axis.x = 1, axis.y = axis.z = 0;
			}else{
				axis.y = axis.z = 1;
				axis.x = -(axis.y*a.y + axis.z*a.z) / a.x;
			}
			axis.normSelf();
            w = 0; x = axis.x; y = axis.y; z = axis.z;   
        }else{ // ��ͨ��ת
            theta *= 0.5;
			Point axis = cross(a, b); // ����ȷ����ת��			
			axis.normSelf();
            w = cos(theta); 
			x = axis.x * sin(theta);
			y = axis.y * sin(theta);
			z = axis.z * sin(theta);
        }
        return;
    }
};

/// ��Ԫ���ĳ˷�
const Quat operator * (const Quat&lhs, const Quat&rhs){
    return Quat(
        lhs.w*rhs.w-lhs.x*rhs.x-lhs.y*rhs.y-lhs.z*rhs.z,
        lhs.w*rhs.x+lhs.x*rhs.w+lhs.y*rhs.z-lhs.z*rhs.y,
        lhs.w*rhs.y-lhs.x*rhs.z+lhs.y*rhs.w+lhs.z*rhs.x,
        lhs.w*rhs.z+lhs.x*rhs.y-lhs.y*rhs.x+lhs.z*rhs.w
    );
}

/// ��������v����תr��õ�������
Vector rotate(const Vector &v, const Quat &r){
    Quat origin(0, v.x, v.y, v.z);
    Quat after = r * origin * r.conj();
    assert(is0(after.w));
    return Vector(after.x, after.y, after.z);
}

/// ��������v��������ת����m������ת�������
Vector rotate(const Vector &v, const Matrix &m){
    return Vector(
        m.data[0][0] * v.x + m.data[0][1] * v.y + m.data[0][2] * v.z,
        m.data[1][0] * v.x + m.data[1][1] * v.y + m.data[1][2] * v.z,
        m.data[2][0] * v.x + m.data[2][1] * v.y + m.data[2][2] * v.z
    );
}

/// ������ת����õ��ȼ۵���Ԫ��������ĳ����Ĺ�ʽ
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

/// �ȼ���ת����Ԫ��ת��ת����
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

Point A;   // A��Բ��
Vector Na; // A�ķ�����
Point B;
Vector Nb;
Real Ra, Rb;

bool read(){
	if(cin >> Ra){
		A.input(); Na.input();
		cin >> Rb;
		B.input(); Nb.input();
		return true;
	} 
    return false;
}

/// ����ά�ռ乲��Բ��ֱ�ߵĽ��㣬���ؽ�����ֱ���ϵĲ���
int inter(const Point & center, Real r, const Vector &n, const Line &line, Real ans[]){
    /// ������Բ�ĵ�ֱ�ߵľ���
	Real d = dist(center, line);
	int t = sgn(d - r);
	if(t > 0){ // û�н���
		return 0;
	}
    /// ��ͬһ��ƽ��������Բ����ֱ�ߴ�ֱ��ֱ��
	Line chui(center, cross(n, line.direction));
	/// ������ֱ�ߵĽ���
	Point zhongdian = inter(chui, line);
	/// ��ý�����ֱ���ϵĲ���
	Real k;
	if(OUT == relation(zhongdian, line, &k)){
		throw runtime_error("sth must be wrong.");
	}
	if(0 == t){
		ans[0] = k;
		return 1;
	}
	/// �����������Ĳ���
	Real tmp = mysqrt(r * r - d  * d);
	tmp /= line.direction.length();

	ans[0] = k - tmp;
	ans[1] = k + tmp;
	return 2;
}

inline Real proc(Real a, Real b, Real c, Real d){
	if(sgn(b - c) <= 0) return 0;
	if(sgn(d - a) <= 0) return 0;
	return min(b, d) - max(a, c);
}

Real proc(){
	/// ȷ��A��B����ƽ�棬��Ŀ��֤���غ�Ҳ��ƽ��
	Plane pa(A, Na), pb(B, Nb);
	/// ������ƽ��Ľ���
	Line line = inter(pa, pb);
	line.direction.normSelf();
	/// ������Բ�Ľ���Ĳ���
	Real a[2], b[2];
	int ka = inter(A, Ra, Na, line, a);
	if(ka != 2){ // û��2�����㣬�϶�Ϊ0
		return 0;
	}
	int kb = inter(B, Rb, Nb, line, b);
	if(kb != 2){
        return 0;
	}

	/// �����غ϶εľ���	
	return proc(a[0], a[1], b[0], b[1]);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif  
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	while(read()){
		cout << fixed << setprecision(12) << proc() << endl;
	}
    return 0;
}
