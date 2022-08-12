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
 * ţ��220476: �߶��ཻ
 * ţ��207032: ֱ�ߵ�λ�ù�ϵ
 * ţ��232575: �߶���򵥶�����ཻ
 * ţ��233135: ͹�����ܳ�
 * ţ��233136: ͹����ת������ֱ��
 * ţ��20057: ͹����С���θ��������
 * ţ��232791: ͹����С���θ��������
 * ţ��233186: ͹����εľ��룬�ɿɷ�˹���ͣ�GJK�㷨
 * ţ��2022���3G: ͹�������ײ���, �ɿɷ�˹����, GJK�㷨
 * ţ��233737: ����͹������ڣ�log�㷨
 * ţ��19905: ��ƽ�潻�����
 * ţ��233170UVA1396UVALive3890: ��ƽ���ƶ�, ��ƽ�潻, ����
 * ţ��233171: ��ƽ�潻���ܳ�
 * ţ��234015: ��ƽ�潻����
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

/** 4. �߶Ρ�ֱ�ߡ������ߵĽṹ�� **/
struct LineSeg{
    Point s, e; // �����ֶ˵��˳��
    LineSeg(){}
    LineSeg(const Point &a, const Point &b):s(a), e(b){
        assert(!(a == b));
    }
};

struct Line{
    coor a, b, c; // ax+by+c=0, ������ɵ�������, ��abc����������
    Point s, e; // �����������ɵ�
    Line(){}
    /// ����ȷ��һ��ֱ�ߣ���֤u!=v
    /// ���������Ȼ��������abcȷ��ֱ��
    Line(const Point &u, const Point &v):s(u),e(v){
        assert(!(u == v));
        /// �÷�����������
        this->a = u.y - v.y;
        this->b = v.x - u.x;
        this->c = u.x * v.y - v.x * u.y;
    }
};

/// ֱ�ߵĲ�������
/// ֱ���ϵĵ� p = b + d * t
/// ����������ʵ��, ������ʵ��
/// �������ھ���Ҫ���ر�ߵĵط�������
/// �����׳����������: ͨ��ֱ��u��ֱ��v�������p, ������pȴ����u����v��
/// ���Կ���ʹ����������Ϊ����
struct ArgLine{
    Point base;
    Vector direction; // ��������
    /// ���������Ƿ���Ҫ��λ��, ����Ƚϲ�ֱͬ��, ��õ�λ��
    ArgLine(const Point &b, const Vector &d, bool needNorm=true):base(b),direction(d){
        assert(!d.isZero());
        if(needNorm) {
            this->direction.normSelf();
        }
    }
};

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

/// ��p�Ƿ����߶�ls��
int relation(const Point &p, const LineSeg &ls){
    return relation(p, ls.s, ls.e);
}

/// ��p�Ƿ���ֱ��line��
int relation(const Point &p, const Line &line){
    // return 0 == p.x * line.a + p.y * line.b + line.c ? IN : OUT;
    return is0(p.x * line.a + p.y * line.b + line.c) ? IN : OUT;
}

/// ��p�����ֱ��line�Ĺ�ϵ, �����ֱ���ϻ��ܷ��ز���, ������ʵ������
int relation(const Point &p, const ArgLine &line, Real *pk=nullptr){
    Real tmp;
    if(fabs(line.direction.x) >= fabs(line.direction.y)){
        assert(sgn(line.direction.x));
        tmp = (p.x - line.base.x) / line.direction.x;
        /// ���yҲ���
        if(is0(line.base.y + line.direction.y * tmp - p.y)){
            if(pk != nullptr) *pk = tmp;
            return IN;
        }
        return OUT;
    }
    

    assert(sgn(line.direction.y));
    tmp = (p.y - line.base.y) / line.direction.y;
    /// ���xҲ���
    if(is0(line.base.x + line.direction.x * tmp - p.x)){
        if(pk != nullptr) *pk = tmp;
        return IN;        
    }
    return OUT;
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

/// ���Ƿ��ڼ򵥶����poly��, ��֤poly[n] == poly[0]
/// �򵥵�˵�����߶�(p, inf)�����εĽ��������, O(n)
int relationSimple(const Point &p, const Point poly[], int n){
    assert(poly[n] == poly[0]);
    /// ����Զ��
    Point inf(INF, p.y);
    int ans = 0;
    /// �����ཻ
    for(int t,r,i=0;i<n;++i){
        r = relation(p, poly[i], poly[i+1]);
        if(r) return r; // ��ʾ���ڸñ���

        /// �����ˮƽ��, ����
        t = sgn(poly[i].y - poly[i+1].y);
        if(0 == t) continue;

        /// ���ཻ����
        r = relation(p, inf, poly[i], poly[i+1]);
        if(OUT == r) continue;

        /// ��������Ǹñ߱Ƚϸߵ��Ǹ���Ҳ����
        if(t > 0 && relation(poly[i], p, inf) != OUT) continue;
        if(t < 0 && relation(poly[i+1], p, inf) != OUT) continue;

        /// ������Ҫ����
        ++ans;
    }
    /// ��������, ż������
    return (ans & 1) ? IN : OUT;
}

/// �߶�a��b�Ƿ��ཻ
int relation(const LineSeg &a, const LineSeg &b){
    return relation(a.s, a.e, b.s, b.e);
}

/// �߶κ�ֱ���Ƿ��ཻ����������
int relation(const LineSeg &ls, const Line &line){
    if((IN & relation(ls.s, line)) && (IN & relation(ls.e, line))){
        return IN; // ����߶ε������㶼��ֱ���ϣ����߶�Ҳ��ֱ����
    }
    return sgn(cross(line.s, ls.s, line.e)) * sgn(cross(line.s, line.e, ls.e)) >= 0 ? INTER : OUT;
}

/// �߶���͹����εĹ�ϵ
/// poly��n͹�����,�ұ��뱣֤poly[n]==poly[0]!!!
int relation(const LineSeg &ls, const Point poly[], int n){
    int rs = relation(ls.s, poly, n);
    int re = relation(ls.e, poly, n);
    if(IN & rs){
        if(IN & re) return IN; // �����ڲ������߶ο϶����ڲ�
        return INTER; // һ��һ�����ཻ
    }else if(IN & re){ // ��Ȼ��һ��һ��
        return INTER;
    }
    /// ��������
    for(int i=0;i<n;++i){
        if(INTER & relation(ls.s, ls.e, poly[i], poly[i+1])){
            return INTER; // �ཻ
        }
    }
    return OUT; // û�й�����
}

/// ֱ��u��v��λ�ù�ϵ������ཻ�������Է��ؽ���
/// ֱ�߿���������, �����㲻�ܱ�֤����, ��һ��pair������
/// ���������㷨
int relation(const Line &u, const Line &v, pair<Real, Real> *pk=nullptr){
    const auto x = u.b * v.c - v.b * u.c;
    const auto y = v.a * u.c - u.a * v.c;
    const auto t = u.a * v.b - v.a * u.b;
    if(is0(t)){
        if(is0(x) && is0(y)) return CHONGHE; // �غ�
        return PINGXING; // ƽ��
    } 
    if(pk != nullptr) pk->first = (Real)x / (Real)t, pk->second = (Real)y / (Real)t;
    return INTER; // �ཻ
}

/// ����ֱ��u��v��λ�ù�ϵ������ཻ�������Է��ؽ���
int relation(const ArgLine &u, const ArgLine &v, Point * pk=nullptr){
    if(is0(cross(u.direction, v.direction))){
        if(IN & relation(u.base, v)){
            assert(IN & relation(v.base, u));
            return CHONGHE;
        }
        return PINGXING;
    }
    /// �󽻵�
    if(pk != nullptr){
        const auto ua = -u.direction.y;
        const auto ub = u.direction.x;
        const auto uc = u.base.x * u.direction.y - u.direction.x * u.base.y;
        const auto va = -v.direction.y;
        const auto vb = v.direction.x;
        const auto vc = v.base.x * v.direction.y - v.direction.x * v.base.y;
        const auto x = ub * vc - vb * uc;
        const auto y = va * uc - ua * vc;
        const auto t = ua * vb - va * ub;
        assert(sgn(t));   
        pk->x = x / t, pk->y = y / t; 
        assert(IN & relation(*pk, u) & relation(*pk, v));    
    }
    return INTER;
}

/** 6 ����� dist���� **/
/// �������ƽ��, �п��ܳ���Χ
coor dist2(const Point &u, const Point &v){
    const auto x = u.x - v.x;
    const auto y = u.y - v.y;
    return x * x + y * y;
}

/// ���֮��ľ���
Real dist(const Point &u, const Point &v){
    return sqrt(Real(dist2(u, v)));
}

/// ��p���߶�AB�ľ���
Real dist(const Point &p, const Point &A, const Point &B){
    assert(!(A == B));
    if(IN & relation(p, A, B)) return 0;
    /// ������
    auto tmp = dot(A, B, p);
    if(sgn(tmp) < 0) return dist(A, p);
    tmp = dot(B, A, p);
    if(sgn(tmp) < 0) return dist(B, p);
    /// ���˴�˵���Ǵ�ֱ����
    return fabs(cross(p, A, B)) / dist(A, B);
}

/// �㵽�߶εľ���
Real dist(const Point &p, const LineSeg &ls){
    return dist(p, ls.s, ls.e);
}

/// �㵽ֱ�ߵľ���
Real dist(const Point &p, const Line &line){
    return fabs(cross(p, line.s, line.e)) / dist(line.s, line.e);
}

/// �㵽͹����εľ���
/// poly��͹����Σ���֤poly[n]==poly[0]!!!
Real dist(const Point &p, const Point poly[], int n){
    assert(poly[n] == poly[0]);
    
    if(IN & relation(p, poly, n)) return 0;
    /// ����˵���ǵ㵽����ıߵľ���
    Real ans = 1E100;
    /// �㵽�ߵľ���ĺ�����͹�ģ�����������������O(n)����Ϊlog
    for(int i=0;i<n;++i){
        ans = min(dist(p, poly[i], poly[i+1]), ans);
    }
    return ans;
}

/** 7 Graham͹���㷨 **/
/// ��㼯p��͹������ı�p������
/// �������p[0..r)�У�����r�Ƿ���ֵ����ʾ͹���ĵ����������ʱ������
/// ���㷨��֤�����û���������㹲�ߣ���һ��Լ���������ܳ���ʵû��
/// nlogn
int Graham(Point p[], int n){
    if(1 == n) return 1;
    /// �����������
    Point * lowleft = min_element(p, p+n, [](const Point&a, const Point &b)->bool{
        int tmp = sgn(a.y - b.y);
        if(tmp) return tmp < 0;
        return a.x < b.x;
    });
    /// �������������Ϊp[0]
    swap(*lowleft, *p);
    /// ���������������������
    sort(p+1, p+n, [&](const Point&a, const Point&b)->bool{
        const auto chaji = cross(*p, a, b);
        const int tmp = sgn(chaji);
        if(tmp) return tmp > 0; // �Ƕ�С������ǰ��
        /// �Ƕ�һ��������С������ǰ��
        const auto xa = a.x - p->x, ya = a.y - p->y;
        const auto xb = b.x - p->x, yb = b.y - p->y;
        return xa * xa + ya * ya < xb * xb + yb * yb;
    });
    /// ������Grahamѭ������������һ��ջ
    int top = 2;
    for(int i=2;i<n;++i){
        while(top > 1 && sgn(cross(p[top-2], p[top-1], p[i])) <= 0){
            --top;
        }
        p[top++] = p[i];
    }
    /// ȥ�����һ�������п��ܹ��ߵĵ�
    if(top >= 3 && 0 == sgn(cross(p[0], p[top-1], p[top-2]))){
        --top;
    }
    return top;
}

/** 10 ��ת���Ƿ� **/
/// ͹����ε�ֱ������͹�����������߶�, O(N), ��ת���Ƿ�
/// p��֤��͹��, 0-index, ��֤p[n] == p[0], p��֤����ʱ��
/// ����ֱ���ĳ��ȵ�ƽ����pans�ﱣ�湹��ֱ���������˵�����, �����кܶ��, ֻ��������һ��
coor rcDiameter(const Point p[], int n, int pans[] = nullptr){
    auto f = [](const Point &u, const Point &v)->coor{
        auto x = u.x - v.x, y = u.y - v.y;
        return x * x + y * y;
    };
    /// ��֤
    assert(p[n] == p[0]);
    coor d = 0;
    int k1 = 0, k2 = 1;
    for(k1=0;k1<n;++k1){
        while(cross(p[k1+1], p[k2+1], p[k1]) > cross(p[k1+1], p[k2], p[k1])){
            k2 = (k2 + 1) % n;
        }
        auto tmp = f(p[k1], p[k2]);
        if(tmp > d){
            d = tmp;
            if(pans){
                pans[0] = k1;
                pans[1] = k2;
                if(k1 > k2) swap(pans[0], pans[1]);
            }
        }
    }
    return d;
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

int N;
Point P[SIZE];

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    N = getInt();
    for(int i=0;i<N;++i) P[i].x = getInt(), P[i].y = getInt();
    N = Graham(P, N);
    P[N] = P[0];
    auto ans = rcDiameter(P, N);
    cout << ans << endl;
    return 0;
}