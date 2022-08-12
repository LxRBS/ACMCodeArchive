#include <bits/stdc++.h>
using namespace std;

/**
 * @brief ��άƽ�漸��
 * @version 20220810
 * 1. typedef�ͳ���
 * 2. ����߽����ѧ�⺯��
 * 3. ���������Ľṹ���Լ��������㣬��ȣ���������
 * 4. �߶Ρ�ֱ�ߡ������ߵĽṹ�壬�߶���ʱҲ���������ʾ, �����һ���õ�������ʾ
 * 5. λ�ù�ϵ������һ����relation����������
 * 6. ����룬һ����dist��������
 * 7. Graham͹���㷨
 * 8. ��ƽ�潻����������
 * 9. �ɿɷ�˹���ͣ�͹�����֮��ľ���
 * 10. ��ת���Ƿ���͹����ε�ֱ����͹����ε���������Σ�͹����ε���С���θ��ǣ�����������rc��ͷ
 * ��������...
 * ��Ŀ�б�:
 * ��������
 * ţ��207032: ֱ�ߵ�λ�ù�ϵ, 2������
 * ţ��220476: �߶��ཻ, 2������
 * ţ��233186: ͹����εľ��룬�ɿɷ�˹���ͣ�GJK�㷨
 * ţ��233737: ����͹������ڣ�log�㷨
 * ��ƽ��
 * ţ��233170UVA1396UVALive3890: ��ƽ���ƶ�, ��ƽ�潻, ����
 * ţ��234015: ��ƽ�潻����
 * ͹��
 * ţ��233135: ͹�����ܳ�
 * ��ת����
 * ţ��232791: ͹����С���θ��������
 * ţ��233136: ͹����ת������ֱ��
 * contest
 * ţ��20057: ͹����С���θ��������
 * ţ��19905: ��ƽ�潻�����
 * ţ��233171: ��ƽ�潻���ܳ�
 * ţ��2022���3G: ͹�������ײ���, �ɿɷ�˹����, GJK�㷨
 */

/** 1. typdef�ͳ��� **/
using Real = long double;
using llt = long long;
using coor = llt;  // Ĭ������������
// using coor = Real; // ��ʱ��Ҫʹ��ʵ������

Real const EPS = 1E-9; // ������Ҫ����
Real const PI = acos(-1);
coor const INF = 1E9;  // ������Ҫ����

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

/** 3. ���������Ľṹ���Լ��������㣬��ȣ��������� **/
struct Point{
    coor x, y;
    Point(coor a=0, coor b=0):x(a),y(b){}
    coor square() const { // ��ʱ���ݻᳬ��Χ, ��ʹʹ��longlong
        return this->x * this->x + this->y * this->y;
    }
    Real length() const { // �㳤�ȿ϶���ʵ��
        return sqrt((Real)this->square());
    }
    void normSelf() { // ��λ��, ֻ��ʵ��������ܵ�λ��
        Real tmp = this->square();
        if(is0(tmp - 1)) return;
        tmp = sqrt(tmp);
        this->x /= tmp, this->y /= tmp;
    }
    bool isZero()const{
        return is0(x) && is0(y);
    }
};
using Vector = Point;

/// ���
bool operator == (const Vector & a, const Vector & b){
    // return a.x == b.x && a.y == b.y;
    return is0(a.x - b.x) && is0(a.y - b.y);
}

/// �����ļӷ�
const Vector operator + (const Vector &u, const Vector &v){
    return Vector(u.x + v.x, u.y + v.y);
}

/// �����ļ��� 
const Vector operator - (const Vector &u, const Vector &v){
    return Vector(u.x - v.x, u.y - v.y);
}

/// �����ı���
const Vector operator * (const Vector &u, coor k){
    return Vector(u.x * k, u.y * k);
}

/// OA �� OB
coor cross(const Point &O, const Point &A, const Point &B){
    auto xoa = A.x - O.x, yoa = A.y - O.y;
    auto xob = B.x - O.x, yob = B.y - O.y;
    return xoa * yob - xob * yoa;
}

/// OA �� OB
coor dot(const Point &O, const Point &A, const Point &B){
    auto xoa = A.x - O.x, yoa = A.y - O.y;
    auto xob = B.x - O.x, yob = B.y - O.y;
    return xoa * xob + yoa * yob;
}

/// �����ĵ��
coor dot(const Vector &u, const Vector &v){
    return u.x * v.x + u.y * v.y;
}

/// �����Ĳ��
coor cross(const Vector &u, const Vector &v){
    return u.x * v.y - v.x * u.y;
}

/** 5 λ�ù�ϵ���� **/
int const OUT = 0; // û�й����㣬�����ཻ
int const IN = 1; // ���ڸ���ͼ����
int const INTER = 2; // ֱ����ֱ�ߣ��߶����߶Σ�ֱ�����߶�
int const PINGXING = 4; // ֱ����ֱ��
int const CHONGHE = 8; // ֱ����ֱ��
int const VERTEX = 0x10; // ��ʾ�㻹��ͼ�εĶ˵���
int const EDGE = 0x20; // ��ʾ�㻹��ͼ�εı���

/// ��p�Ƿ����߶�AB��, ����IN��ʾ��, ������VERTEX|EDGE��ʾ�ڵ��ϻ��߱���
/// ����OUT��ʾ�����߶�ABû�й�����
int relation(const Point &p, const Point &A, const Point &B){
    assert(!(A == B));
    if(p == A || p == B) return VERTEX | IN;
    return 0 == cross(p, A, B)
        && sgn(min(A.x, B.x) - p.x) <= 0 && sgn(p.x - max(A.x, B.x)) <= 0
        && sgn(min(A.y, B.y) - p.y) <= 0 && sgn(p.y - max(A.y, B.y)) <= 0
        ? (IN | EDGE) : OUT;
}

/// ��p�Ƿ���͹������ڣ�����һ��O(logN)���㷨
/// ע��log�㷨Ҫ��poly��������ʱ��
/// �����˳ʱ����Ҫ�ı������ж�
/// ����IN | VERTEX | EDGE, ����OUT
int relation(const Point &p, const Point poly[], int n){
    /// ����
    if(1 == n) return p == poly[0] ? (IN | VERTEX) : OUT;
    if(2 == n) return relation(p, poly[0], poly[1]);

    /// p��poly[1]����ʱ�룬p��Ȼ������
    if(sgn(cross(poly[0], p, poly[1])) > 0) return OUT;
    /// ͬ��
    if(sgn(cross(poly[0], poly[n-1], p)) > 0) return OUT;
    
    int left = 1, right = n - 2, mid;
    do{
        mid = (left + right) >> 1;
        assert(mid > 0 && mid + 1 < n);
        const auto t1 = cross(poly[0], poly[mid], p);
        const auto t2 = cross(poly[0], poly[mid+1], p);
        if(sgn(t1) >= 0 && sgn(t2) <= 0){ // ˵��p��Ȼ��(mid,mid+1)֮��
            /// Ҫ�����Ƿ���(0,1)����
            if(1 == mid){
                int r = relation(p, poly[0], poly[1]);
                if(r != OUT) return r;
            }
            /// Ҫ�����Ƿ���(n-1, 0)����
            if(mid + 1 == n - 1){
                int r = relation(p, poly[n-1], poly[0]);
                if(r != OUT) return r;
            }
            /// ����
            const auto chaji = cross(p, poly[mid], poly[mid+1]);
            int r = sgn(chaji);
            if(r > 0) return IN;
            if(r < 0) return OUT;
            /// ��ʱ��Ȼ��(mid, mid+1)����
            r = relation(p, poly[mid], poly[mid+1]);
            assert(r == (IN | VERTEX) || r == (IN | EDGE));
            return r;
        }
        if(t1 < 0) right = mid - 1;
        else left = mid + 1; 
    }while(left <= right);
    return OUT;
}

/// �߶�AB��CD�Ƿ��ཻ, �����ų�Ϳ���, Real�汾
int relation(const Point &A, const Point &B, const Point &C, const Point &D){
    return sgn(min(A.x, B.x) - max(C.x, D.x)) <= 0
        && sgn(min(A.y, B.y) - max(C.y, D.y)) <= 0
        && sgn(min(C.x, D.x) - max(A.x, B.x)) <= 0
        && sgn(min(C.y, D.y) - max(A.y, B.y)) <= 0
        && sgn(cross(A, C, B)) * sgn(cross(A, B, D)) >= 0
        && sgn(cross(C, B, D)) * sgn(cross(C, D, A)) >= 0
        ? INTER : OUT;
}

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
int const SIZE = 7;
#else
int const SIZE = 1E5+10;
#endif

Point Poly[4], P;

int proc(){    
    if(cross(Poly[0], Poly[1], Poly[2]) < 0) swap(Poly[1], Poly[2]);
    int r = relation(P, Poly, 3);
    if(r & VERTEX) return 4;
    if(r & EDGE) return 3;
    if(r & IN) return 1;
    assert(OUT == r);
    return 2;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif  
    for(int i=0;i<3;++i){
        Poly[i].x = getInt();
        Poly[i].y = getInt();
    }
    P.x = getInt(), P.y = getInt();
    cout << proc() << endl;
    return 0;
}

