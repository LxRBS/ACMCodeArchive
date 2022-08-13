/**
 * һ��͹����Σ�˳ʱ�����������2���������߶�����
 * ����ָ���������߶β�����
 * �ʴ�1��N����̾���
 * ��Ȼ���1-N���ߵĻ���ֱ���߾����ˣ�������ȻҪ�����ܵ���N�����
 * ��˶�ÿ����ֻȡ���ܹ�ֱ�ӵ���������ŵ��߶�
 * ������һ��͹��ͼ�Σ����ϰ벿���ܳ�����
 * ��ƽ�潻
 */
#include <bits/stdc++.h>
using namespace std;

/**
 * @brief ��άƽ�漸��
 * @version 20220812, ģ����, ����������Ϊ��Ա����, ������дģ�����
 * 1. typedef�ͳ���
 * 2. ����߽����ѧ�⺯��
 * 3. ���������Ľṹ���Լ��������㣬��������, ��ϵ����, ����Ͳ��
 * 4. ֱ�ߵĽṹ��
 * 5. �߶εĽṹ�壬�߶���ʱҲ�������ʾ
 * 6. �������͹�����, ͹��, �ɿɷ�˹��������ת���Ƿ�
 * 7. ��ƽ�潻����������
 * ��������...
 * ��Ŀ�б�:
 * ��������
 * LuoguP1355: ������������
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

Real const EPS = 1E-9; // ������Ҫ����
Real const PI = acos(-1);
Real const INF = 1E9;  // ������Ҫ����

inline int sgn(Real x){return x >= EPS ? 1 : (x <= -EPS ? -1 : 0);}
inline bool is0(Real x){return 0 == sgn(x);}

inline int sgn(llt x){return x > 0 ? 1 : (x < 0 ? -1 : 0);}
inline bool is0(llt x){return 0 == x;}

/// ��λ�ù�ϵ�ĳ���
int const OUT = 0; // û�й����㣬�����ཻ
int const IN = 1; // ���ڸ���ͼ����
int const JIAO = 2; // ֱ����ֱ�ߣ��߶����߶Σ�ֱ�����߶�
int const PINGXING = 4; // ֱ����ֱ��
int const CHONGHE = 8; // ֱ����ֱ��
int const VERTEX = 0x10; // ��ʾ�㻹��ͼ�εĶ˵���
int const EDGE = 0x20; // ��ʾ�㻹��ͼ�εı���

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
/// ģ����, ����ʵ���������ͻ���ʵ��
template<typename T>struct Point{

T x, y;
Point(T a=0, T b=0):x(a),y(b){}
/// ����ע���п��ܳ���Χ
T square() const {return x * x + y * y;}
/// ���ȱ�����ʵ��
Real length() const {return sqrt((Real)this->square());}
void normSelf() { // ��λ��, ������ʵ��
    T tmp = this->square();
    if(is0(tmp - 1)) return;
    Real t = sqrt((Real)tmp);
    this-> x /= t, this->y /= t;
}
bool isZero() const {return is0(x) && is0(y);}
/// ��������Ӽ���
const Point operator + (const Point & r) const {return Point(x + r.x, y + r.y);}
const Point operator - (const Point & r) const {return Point(x - r.x, y - r.y);}
const Point operator * (T k) const {return Point(x * k, y * k);}
/// ��ϵ����
bool operator == (const Point & r) const {return is0(x - r.x) && is0(y - r.y);}
/// �������, this �� r
T cross(const Point & r) const {return x * r.y - y * r.x;}
/// �������
T dot(const Point & r) const {return x * r.x + y * r.y;}
/// ��Ĳ��, this��Ϊ��O, OA �� OB
T cross(const Point &A, const Point &B) const {return (A - *this).cross(B - *this);}
/// ��ĵ��
T dot(const Point &A, const Point &B) const {return (A - *this).dot(B - *this);}
/// �����ƽ��
T dist2(const Point & r) const {return (*this-r).square();}
/// ����, ������ʵ��
Real dist(const Point & r) const {return (*this-r).length();}
/// this���߶�AB��λ�ù�ϵ
int relate(const Point &A, const Point &B) const {
    assert(!(A == B));
    if(A == *this || B == *this) return IN | VERTEX;
    if(sgn(this->dot(A, B)) <= 0 && 0 == sgn(this->cross(A, B))){
        return IN | EDGE;
    }
    return OUT;
}
/// this���߶�AB�ľ���
Real dist(const Point &A, const Point &B) const {
    if(IN & this->relate(A, B)) return 0;
    if(sgn(A.dot(*this, B)) <= 0) return this->dist(A);
    if(sgn(B.dot(*this, A)) <= 0) return this->dist(B);
    /// ����Ϊ��
    return fabs(this->cross(A, B)) / (A - B).length();
}


};

/** 4. ֱ�ߵĽṹ�� **/
template<typename T>struct Line{

using Dian = Point<T>;
using Zhixian = Line<T>;

T a, b, c; // �����������, ��Ȼ��������������abcΪ����

Line() = default;

/// ����ȷ��һ��ֱ��
Line(const Dian &A, const Dian &B, bool needNorm=false){
    assert(!(A == B));
    /// �÷�����������
    this->a = A.y - B.y;
    this->b = B.x - A.x;
    this->c = A.x * B.y - B.x * A.y; 
    
    if(needNorm) normSelf();
}

/// ��������p�ͷ�������d, ����ֱ��
static Zhixian create(const Dian &p, const Dian &d, bool needNorm=false){
    return Zhixian(p, p+d, needNorm);
}

/// ��һ��, ��������stl�����ݽṹ, ����������
void normSelf() {
    T aa = a >= 0 ? a : -a;
    T bb = b >= 0 ? b : -b;
    T cc = c >= 0 ? c : -c;
    T g = 0;
    if(0 == aa){ // bb ��Ȼ��Ϊ0
        if(0 == cc) g = bb;
        else g = __gcd(bb, cc);
    }else if(0 == bb){
        if(0 == cc) g = aa;
        else g = __gcd(aa, cc);
    }else{
        g = __gcd(aa, bb);
        if(cc) g = __gcd(g, cc);
    }
    this->a /= g, this->b /= g, this->c /= g;
    if(a < 0 || (0 == a && b < 0)) {a = -a, b = -b, c = -c;}
}

T eval(const Dian &p) const {return a * p.x + b * p.y + c;}

/// ����ֱ�ߵ�λ�ù�ϵ, �ཻ���ܷ��ؽ���, ����ֻ����ʵ�� 
int relate(const Line & r, Point<Real> *pk=nullptr) const {
    T x = b * r.c - c * r.b; // �����п������
    T y = r.a * c - r.c * a;
    T t = a * r.b - b * r.a;
    if(is0(t)){
        if(is0(x) && is0(y)) return CHONGHE;
        return PINGXING;
    }
    if(pk) pk->x = (Real)x / t, pk->y = (Real)y / t;
    return JIAO;
}

/// ֱ������λ�ù�ϵ
int relate(const Dian & p) const {
    return is0(a * p.x + b * p.y + c) ? IN : OUT;
}

/// ֱ�����߶�AB��λ�ù�ϵ
int relate(const Dian & A, const Dian & B) const {
    int ra = sgn(this->eval(A));
    int rb = sgn(this->eval(B));
    if(0 == ra && 0 == rb) return JIAO & CHONGHE;
    if(0 == ra || 0 == rb) return JIAO & VERTEX;
    return ra * rb < 0 ? JIAO : OUT;
}

/// �㵽ֱ�ߵľ���
Real dist(const Dian & p) const {
    return this->eval(p) / sqrt(a * a + b * b);
}

};

/** 5. �߶εĽṹ�壬�߶���ʱҲ�������ʾ **/
template<typename T>struct LineSeg{

/// Ϊ�˽�Լģ�����, ������
using Dian = Point<T>;
using Xianduan = LineSeg<T>;
Dian s, e; // s��e������˳��

LineSeg(const Dian &A, const Dian &B):s(A),e(B){}

/// �����߶ε�λ�ù�ϵ
int relate(const Dian & p) const {
    return p.relate(this->s, this->e);
}

/// �����߶εľ���
Real dist(const Dian & p) const {
    return p.dist2(this->s, this->e);
}

/// �߶����߶ε�λ�ù�ϵ, ֻ����JIAO����OUT
/// Ҫ�ж��Ƿ��ڶ˵���Ҫ�����ж�
int relate(const Dian &A, const Dian &B) const {
    return sgn(min(s.x, e.x) - max(A.x, B.x)) <= 0
        && sgn(min(s.y, e.y) - max(A.y, B.y)) <= 0
        && sgn(min(A.x, B.x) - max(s.x, e.x)) <= 0
        && sgn(min(A.y, B.y) - max(s.y, e.y)) <= 0
        && sgn(s.cross(A, e)) * sgn(s.cross(e, B)) >= 0
        && sgn(A.cross(s, B)) * sgn(A.cross(B, e)) >= 0
        ? JIAO : OUT;
}

/// �߶����߶ε�λ�ù�ϵ, ֻ����JIAO����OUT
/// Ҫ�ж��Ƿ��ڶ˵���Ҫ�����ж�
int relate(const Xianduan & r) const {
    return this->relate(r.s, r.e);         
}

};

/** 6. �����, �򵥶���κ�͹����κ�͹�� **/
/// �򵥶����
template<typename T>struct Polygon{

using Dian = Point<T>;
using Xianduan = LineSeg<T>;
using vt = vector<Dian>;

vt pts; // �˵�����, ��֤û�ж���ĳ���, ��size() == n

Polygon() = default;
Polygon(int n):pts(n, Dian()){}

void init(int n){pts.resize(n);}

/// ����򵥶����λ�ù�ϵ, O(N), ˳ʱ����ʱ�붼����
int relate(const Dian & p) const {
    int n = pts.size();

    /// ����Զ�㹹�ɵ��߶� 
    Xianduan ls(p, Dian(INF, p.y));
    int ans = 0;
    for(int r,nxt,i=0;i<n;++i){
        nxt = (i+1) % n;
        /// ���ȿ��㱾����ߵ�λ�ù�ϵ
        r = p.relate(pts[i], pts[nxt]);
        if(r) return r;

        /// ˮƽ�ߺ���
        int t = sgn(pts[nxt].y - pts[i].y);
        if(0 == t) continue;

        /// �߶���߲���Ҳ����
        r = ls.relate(pts[i], pts[nxt]);
        if(OUT == r) continue;

        /// ���ڽϸߵĵ�Ҳ����
        if(t > 0 && ls.relate(pts[nxt])) continue;
        if(t < 0 && ls.relate(pts[i])) continue;

        ++ans;
    }
    /// ����ż��
    return (ans & 1) ? IN : OUT;
}

/// �㵽�򵥶���ε�, O(N)
Real dist(const Dian & p, Real const inf=INF) const {
    if(this->relate(p)) return 0;

    int n = pts.size();
    Real ans = inf;
    for(int i=0;i<n;++i){
        ans = min(ans, p.dist(pts[i], pts[(i+1)%n]));
    }
    return ans;
}

/// ��������Ķ���
T area2() const {
    int n = pts.size();    
    T ans = 0;
    for(int i=1;i<n-1;++i){
        ans += pts[0].cross(pts[i], pts[(i+1)%n]);
    }
    return ans;
}

/// �ܳ�, ��ȻΪʵ��
Real circum() const {
    Real ans = 0.0;
    for(int i=0,n=pts.size();i<n;++i){
        ans += pts[i].dist(pts[(i+1)%n]);
    }
    return ans;
}

/// �淶��, ɾ�����ߵ�
void normSelf(){
    auto &p = pts;
    int n = pts.size();
    if(n <= 2) return;
    
    int top = 1;
    int k = 1;
    while(1){
        while(k < n && is0(p[top-1].cross(p[k], p[(k+1)%n]))) ++k;
        if(k == n) {p[top++] = p[n-1]; break;}
        p[top++] = p[k++];
        if(k == n) break;
    }

    /// ɾ��
    p.erase(p.begin() + top, p.end());
    if(p.size() <= 2) return;

    // ����0�� 
    if(is0(p[0].cross(p[p.size()-1], p[1]))) p.erase(p.begin());
    /// assert
    assert([&]()->bool{
        int n = p.size();
        for(int i=0;i<n;++i){
            if(is0(p[i].cross(p[(i-1+n)%n], p[(i+1)%n]))){
                return false;
            }
        }
        return true;
    }());
}

};

/// ͹����κ�͹��
template<typename T>struct Convex : public Polygon<T>{

using Dian = Point<T>;
using Zhixian = Line<T>;
using vt = vector<Dian>;
using Tu = Convex<T>;

Convex():Polygon<T>(){}
Convex(int n):Polygon<T>(n){}

/// ���Ƿ���͹�������, log�㷨, ��������ʱ��
int relate(const Dian & p) const {
    const auto & pts = this->pts;
    int n = pts.size();

    /// ����
    if(1 == n) return (p == pts[0]) ? (IN | VERTEX) : OUT;
    if(2 == n) return p.relate(pts[0], pts[1]);
    /// һ��㱣֤
    assert(sgn(pts[0].cross(pts[1], pts[2])) >= 0);
    /// p����1����ʱ�룬��p��Ȼ������
    if(sgn(pts[0].cross(p, pts[1])) > 0) return OUT;
    /// p����n-1��˳ʱ�룬��p��Ȼ������
    if(sgn(pts[0].cross(p, pts[n-1])) < 0) return OUT;
    // ����
    int left = 1, right = n - 2, mid;
    do{
        mid = (left + right) >> 1;
        assert(mid > 0 && mid + 1 < n);
        T t1 = pts[0].cross(pts[mid], p);
        T t2 = pts[0].cross(pts[mid+1], p);
        /// p ��Ȼ��(mid, mid+1)֮��
        if(sgn(t1) >= 0 && sgn(t2) <= 0){
            /// Ҫ�����Ƿ���(0,1)����
            if(1 == mid){
                int r = p.relate(pts[0], pts[1]);
                if(r != OUT) return r;
            }
            /// Ҫ�����Ƿ���(n-1, 0)����
            if(mid + 1 == n - 1){
                int r = p.relate(pts[n-1], pts[0]);
                if(r != OUT) return r;
            }
            /// ����
            T chaji = p.cross(pts[mid], pts[mid+1]);
            int r = sgn(chaji);
            if(r > 0) return IN;
            if(r < 0) return OUT;
            /// ��ʱ��Ȼ��(mid, mid+1)����
            r = p.relate(pts[mid], pts[mid+1]);
            assert(r == (IN | VERTEX) || r == (IN | EDGE));
            return r;
        }
        /// ����
        if(t1 < 0) right = mid - 1;
        else left = mid + 1;         
    }while(left <= right);
    return OUT;
}

/// Graham͹���㷨, 
/// ���Ȱѵ㼯����pts��, ��ı�㼯������
/// ���㷨��֤�����û���������㹲�ߣ���һ��Լ���������ܳ���ʵû��
/// nlogn
int Graham(){    
    auto & pts = this->pts;
    int n = pts.size();

    /// ���� 
    if(1 == n) return 1;

    /// �����������
    auto lowleft = min_element(pts.begin(), pts.end(), [](const Dian&a, const Dian &b)->bool{
        int tmp = sgn(a.y - b.y);
        if(tmp) return tmp < 0;
        return a.x < b.x;
    });

    /// �������������Ϊpts[0]
    swap(*lowleft, pts[0]);

    /// ���������������������
    sort(++pts.begin(), pts.end(), [&](const Dian&a, const Dian&b)->bool{
        const int tmp = sgn(pts[0].cross(a, b));
        if(tmp) return tmp > 0; // �Ƕ�С������ǰ��
        /// �Ƕ�һ��������С������ǰ��
        return sgn((a - pts[0]).square() - (b - pts[0]).square()) < 0;
    });

    /// ������Grahamѭ������������һ��ջ
    int top = 2;
    for(int i=2;i<n;++i){
        while(top > 1 && sgn(pts[top-2].cross(pts[top-1], pts[i])) <= 0){
            --top;
        }
        pts[top++] = pts[i];
    }
    /// ȥ�����һ�������п��ܹ��ߵĵ�
    if(top >= 3 && 0 == sgn(pts[0].cross(pts[top-1], pts[top-2]))){
        --top;
    }
    pts.erase(pts.begin()+top, pts.end());
    return top; // һ��Ҫ��ֵ    
}

/// �ɿɷ�˹���ͣ�ֻ������͹��
/// ��������͹�����a��b,͹�����c=a+b����a��b�е����е�����
/// ����һ��͹����Σ�Ϊ�ɿɷ�˹���ͣ����ܴ湲�ߵ�
const Tu operator + (const Convex & r) const {
     
    /// ��������
    auto lowleft = [](const Dian &u, const Dian &v)->bool{
        int t = sgn(u.y - v.y);
        if(t) return t < 0;
        return u.x < v.x;
    };
    /// ��������
    auto loc = [](const Dian &p)->int{
        if(is0(p.y)) return p.x > 0 ? 0 : 4;
        if(is0(p.x)) return p.y > 0 ? 2 : 6;
        if(p.x > 0) return p.y > 0 ? 1 : 7;
        return p.y > 0 ? 3 : 5;
    };
    /// ��������0-360 
    auto cmp = [&](const Dian &u, const Dian &v)->bool{
        int uloc = loc(u), vloc = loc(v);
        if(uloc != vloc) return uloc < vloc;
        /// ͬһ�����������
        auto chaji = sgn(u.x * v.y - v.x * u.y);
        return chaji > 0;
    };
    /// ��������̣�������Ķ����p��ֳ�����,����ans
    /// ans�е��������հ��ռ�������, ������������ı��
    auto calc = [&](const vt &p, int n, Dian ans[])->int{
        int kll = 0; // ��������
        int jll = 0; // ��С��
        for(int i=0;i<n;++i){
            ans[i] = p[(i+1)%n] - p[i];
            if(lowleft(p[i], p[kll])) kll = i;
            if(cmp(ans[i], ans[jll])) jll = i;
        }
        rotate(ans, ans+jll, ans+n);
        return kll;
    };
    
    /// ����
    const auto & pa = this->pts;
    const auto & pb = r.pts;
    int na = pa.size(), nb = pb.size();

    /// ����ֵ
    Tu ret(na+nb);
    auto & pc = ret.pts;
    int nc = pc.size();    

    /// �Ȳ�pa, �ٲ�pb
    int ka = calc(pa, na, pc.data());
    int kb = calc(pb, nb, pc.data()+na);
    /// �鲢
    inplace_merge(pc.begin(), pc.begin()+na, pc.begin()+na+nb, cmp);
    /// �ٽ�pc���������������ɣ�pc�п��ܴ��ڹ��ߵĵ�
    pc[0].x += pa[ka].x + pb[kb].x;
    pc[0].y += pa[ka].y + pb[kb].y;

    for(int i=1;i<nc;++i){
        pc[i].x += pc[i-1].x;
        pc[i].y += pc[i-1].y;
    }
    return ret;    
}
/// ͹����ε�ֱ������͹�����������߶�, O(N), ��ת���Ƿ�
/// ����ֱ���ĳ��ȵ�ƽ����pans�ﱣ�湹��ֱ���������˵�����, �����кܶ��, ֻ��������һ��
T rcDiameter2(int pans[] = nullptr) const {
     
    auto f = [](const Dian &u, const Dian &v)->T{
        auto x = u.x - v.x, y = u.y - v.y;
        return x * x + y * y;
    };
    
    const auto & p = this->pts;
    int const n = p.size();

    T d = 0;
    int k1 = 0, k2 = 1;
    for(k1=0;k1<n;++k1){
        while(sgn(p[(k1+1)%n].cross(p[(k2+1)%n], p[k1]) - p[(k1+1)%n].cross(p[k2], p[k1])) > 0){
            k2 = (k2+1)%n;
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

/// ��ת���Ƿ���͹������е����������, O(N^2)
/// ����������������
T rcTriangle2(int pans[] = nullptr) const {
    const auto & p = this->pts;
    int const n = p.size();
     

    T edge = 0;
    T ans = 0;
    for(int k,j,i=0;i<n-2;++i){
        j = i + 1;
        k = j + 1;
LL_rcTriangle:
        edge = 0;
        while(k < n){
            auto chaji = cross(p[i], p[j], p[k]);
            if(chaji < 0) chaji = -chaji;
            if(edge > chaji) break;
            edge = chaji;
            ++k;
        }
        /// edge��¼������ijΪ��"���ܴﵽ�����������"
        if(ans < edge) {
            ans = edge;
            if(pans){
                pans[0] = i, pans[1] = j, pans[2] = k;
            }
        }
        /// ����j,����ѭ��
        --k, ++j;
        if(n - 1 == j) continue;
        goto LL_rcTriangle;
    }
    assert(is0(fabs(p[pans[0]].cross(p[pans[1]], p[pans[2]]) - ans)));
    sort(pans, pans+3);
    return ans;
}

/// ��ת���Ƿ�����С���Ǿ���, 
/// ���ҵ�һ��������ȫ��ס͹�����p, �Ҹþ����������С��
/// ������С���, pans�м�¼4���㣬Ϊ����, �������ʵ��
/// p��֤����ʱ��, ˳ʱ����Ҫ����while�еĹ�ϵ����
Real rcRectangle(Point<Real> pans[] = nullptr, const Real inf=INF) const {
    const auto & p = this->pts;
    int const n = p.size();

    if(1 == n){ // һ������������
        return 0;
    }
    if(2 == n){ // ��������������
        return 0;
    }
    /// ����ȷ�����ϵ�
    int t = 1; // �ֱ����������ҡ����ϵ�
    while(t < n && sgn(p[0].cross(p[1], p[t]) - p[0].cross(p[1], p[(t+1)%n])) <= 0){
        ++t;
    }
    if(t == n){ /// ˵������һ��ֱ����
        return 0;
    }
    /// �������������
    int l = t, r = 1;
    Real ans = inf;
    for(int i=0;i<n;++i){
        /// ��������������
        const auto vec = p[(i+1)%n] - p[i];
        while(vec.dot(p[(r+1)%n]-p[r]) >= 0){
            r = (r + 1) % n;
        }
        while(sgn(p[i].cross(p[(i+1)%n], p[t]) - p[i].cross(p[(i+1)%n], p[(t+1)%n])) <= 0){
            t = (t + 1) % n;
        }
        while(vec.dot(p[(l+1)%n]-p[l]) <= 0){
            l = (l + 1) % n;
        }
        /// ����Ϊ(i,i+1)�����ڵ�ֱ���ҿ�סt,l,r������
        /// ���ε��������t��(i,i+1)�ľ����������(l, r)��(i,i+1)��ͶӰ�ĳ���
        Real chang = fabs(p[i].cross(p[(i+1)%n], p[t]) / vec.length()); 
        Real kuan = fabs(vec.dot(p[r] - p[l]) / vec.length());
        Real tmp = chang * kuan;
        if(tmp < ans){
            ans = tmp;
            /// ��¼��
            if(pans != nullptr){
                /// �ײ��ķ�������, �����ҵķ�������
                Dian diDirection(p[(i+1)%n] - p[i]);
                Dian zuoDirection(-diDirection.y, diDirection.x);
                /// �ײ���ֱ��, ע�����ﲻ���ù��캯��
                Zhixian bLine = Zhixian::create(p[i], diDirection);
                /// �Ҳ��ֱ��
                Zhixian rLine = Zhixian::create(p[r], zuoDirection);
                /// �ϲ�ֱ��
                Zhixian tLine = Zhixian::create(p[t], diDirection);
                /// ���ֱ��
                Zhixian lLine = Zhixian::create(p[l], zuoDirection);
                /// 4������
                int c919 = bLine.relate(rLine, pans);
                c919 &= rLine.relate(tLine, pans+1);
                c919 &= tLine.relate(lLine, pans+2);
                c919 &= lLine.relate(bLine, pans+3);
                assert(JIAO & c919);
            }
        }
    }
    return ans;
}

/// ����ĳһ�������ϵļ�ֵ��, �����õ��Ը÷�����һ����ƽ��
/// ͹����ε����е㶼�ڸð�ƽ����
/// ����ֵΪ����͹������е����
/// ���Ҫ�õ�ƽ��ֱ�ߵĵ��, ��Ҫ������������
/// ��֤͹����α�������ʱ��
/// https://codeforces.com/blog/entry/48868
/// O(logN), dirΪ���㷽��ĺ���
int extreme(function<Dian(const Dian &)> dir) const {
    const auto &p=this->pts;
    int const n = p.size(); 
    
    const auto check=[&](const size_t i){return sgn(dir(p[i]).cross(p[(i+1)%n]-p[i]))>=0;};
    const auto dir0=dir(p[0]); const auto check0=check(0);
    if (!check0 && check(p.size()-1)) return 0;
    const auto cmp=[&](const Dian &v){
        const int vi=&v-p.data();
        const auto checkv=check(vi);
        const auto t=sgn(dir0.cross(v-p[0]));
        return checkv^(checkv==check0 && ((!check0 && t<=0) || (check0 && t<0)));
    };
    return partition_point(p.begin(),p.end(),cmp)-p.begin();
}

/// ��֤��p��͹�������, ������������
/// ��[first, second]֮��ĵ�Ϊp�Ŀɼ���
pair<int, int> qiexian(const Dian &p) const{
    int a = this->extreme([&](const Dian &q){return q - p;});
    int b = this->extreme([&](const Dian &q){return p - q;});
    return {a, b};
}

/// ����ֱ��ABƽ�е����ߵ��е�
pair<int, int> qiexian(const Dian &A, const Dian &B) const{
    int a = this->extreme([&](const Dian &q){return B - A;});
    int b = this->extreme([&](const Dian &q){return A - B;});
    return {a, b};
}

/// �㵽͹����εľ���, O(logN)
/// ����������пɼ���, Ȼ������
Real dist(const Dian & p) const {
    const auto & pts = this->pts;
    int const n = pts.size();

    /// ����
    if(1 == n) return p.dist(pts[0]);
    if(2 == n) return p.dist(pts[0], pts[1]);
    /// ������, ��Ҳ��log�㷨
    int r = this->relate(p);
    if(r & IN) return 0;

    /// ��ɼ��㷶Χ
    auto pp = this->qiexian(p);

    /// ��������
    int left = pp.first, right = pp.second, m1, m2;
    do{
        m1 = left + (right - left) / 3;
        m2 = right - (right - left) / 3;
        if(sgn(p.dist(pts[m1], pts[(m1+1)%n]) - p.dist(pts[m2], pts[(m2+1)%n])) <= 0){
            right = (m2 - 1 + n) % n;
        }else{
            left = (m1+1)%n; 
        }
    }while(left <= right);
    /// left�Ǵ�
    return p.dist(pts[left], pts[left+1]);    
}

};

/** 7 ��ƽ��Ͱ�ƽ�潻���������� **/
template<typename T>struct HalfPlane{

using Dian = Point<T>;
using Banpm = HalfPlane<T>;

/// ax+by+c >= 0, (a, b)���Ƿ�����
T a, b, c; // ��������γ�������ƽ��

HalfPlane(T aa=0, T bb=0, T cc=0):a(aa),b(bb),c(cc){}
/// ��������һ����ƽ�棬��u��v����ʱ�룬����ƽ����uv�����ֱ�
HalfPlane(const Dian &u, const Dian &v){
    /// ��ֱ������һģһ��
    assert(!(u == v));
    this->a = u.y - v.y;
    this->b = v.x - u.x;
    this->c = u.x * v.y - v.x * u.y;    
}

T eval(const Dian &p) const {return a * p.x + b * p.y + c;}
/// �����ƽ��Ĺ�ϵ, ��, �߽�, ��
int relate(const Dian &p) const {
    int r = sgn(eval(p));
    if(0 == r) return IN & EDGE;
    if(r > 0) return IN;
    return OUT;
}

/// ��ƽ���ཻ�󽻵㣬��֤�ཻ
/// ֻ��һ�������Ҫ���У����Ƿ������෴���ҽ���Ϊ�յ����
/// �����������������������ֱ�ӵõ���ƽ�潻Ϊ�ռ�
/// �������ʾ������Ч������false��ʾ�������
/// ����ֻ����ʵ��
bool inter(const Banpm & r, Point<Real> &p) const {
    const T xishu = a * r.b - b * r.a;
    if(is0(xishu)) return false;
    Real tmp = xishu;
    p = {(b * r.c - c * r.b) / tmp, (c * r.a - a * r.c) / tmp};
    return true;
}

/// ��ƽ�����ŷ����������ƶ�����d, Ϊ������ʾ���ŷ������������ƶ�
/// ֻ����ʵ��
Banpm move(T d) const {
    return Banpm(a, b, c - d * sqrt(a * a + b * b));
}

/// ��ƽ�潻������������
/// ��֤��������޵ģ�������Ҫ�Ӱ�Χ�У����n�϶�����4
/// ��ı�hp�����ݣ�0-index
/// ���������hp[bot..top]��
/// ����top-bot+1������ƽ������������С��3��˵��ԭ����Ϊ�ռ�
static int sandi(Banpm hp[], int n, int&bot, int&top){
    /// ���ݷ���������(-180,180]�Ƚϴ�С���Ƕ���ͬԽ����������ԽС
    sort(hp, hp+n, [](const Banpm&u, const Banpm&v)->bool{
        /// �������ֱ�λ��x�����£�����ֱ�ӵõ����
        int ly = sgn(u.b) >= 0 ? 1 : -1;
        int ry = sgn(v.b) >= 0 ? 1 : -1;
        if(ly != ry) return ly < ry;
        
        /// �������x���ϣ���һ��һ��
        if(is0(u.b) && is0(v.b) && sgn(u.a * v.a) < 0) return u.a > v.a;
        
        /// ����������������Ϊ��
        int chaji = sgn(u.a * v.b - u.b * v.a);
        if(chaji) return chaji > 0;
        
        /// ���˴�˵��ƽ��, ��a����0
        if(sgn(u.a) > 0){
            /// ��hp1��hp2�������������������a1x+b1y+c1=0��a2x+b2y+c2>0
            return u.c * v.a < u.a * v.c;
        }
        if(sgn(u.a) < 0){ // С��0���Ƿ�����
            return u.c * v.a > u.a * v.c;
        }
        /// aΪ0��b�ز�Ϊ0
        if(sgn(u.b) > 0){
            return u.c * v.b < u.b * v.c;
        }
        return u.c * v.b > u.b * v.c;
    });

    /// ��ȫƽ�еķ�����ֻȡһ��
    n = unique(hp, hp+n, [](const Banpm&u, const Banpm&v)->bool{
        int ly = sgn(u.b) >= 0 ? 1 : -1;
        int ry = sgn(v.b) >= 0 ? 1 : -1;
        if (ly != ry) return false;
        if (is0(u.b) && is0(v.b)) return u.a * v.a > 0;
        return is0(u.a * v.b - v.a * u.b);        
    }) - hp;

    /// ��ѭ��
    bot = 0, top = 1;
    Point<Real> p; // ���������ʵ��
    for(int i=2;i<n;++i){
        /// ��ǰ�˵�������ƽ���ཻ
        while(bot < top){
            bool b = hp[top-1].inter(hp[top], p);
            if(!b) return bot = top = -1, 0; // ֱ�ӷ��ؿռ�����

            /// �����ڵ�ǰ��ƽ���������            
            if(hp[i].relate(p)){
                break;
            }else{
                --top;
            }
        }
        /// ��׶˵�������ƽ���ཻ
        while(bot < top){
            bool b = hp[bot].inter(hp[bot+1], p);
            if(!b) return bot = top = -1, 0;

            if(hp[i].relate(p)){
                break;
            }else{
                ++bot;
            }
        }
        /// ��ֵ
        hp[++top] = hp[i];
    }

    /// ����
    while(bot < top){
        bool b = hp[top-1].inter(hp[top], p);
        if(!b) return bot = top = -1, 0;        
        if(hp[bot].relate(p)){
            break;
        }else{
            --top;
        }
    }
    while(bot < top){
        bool b = hp[bot].inter(hp[bot+1], p);
        if(!b) return bot = top = -1, 0;  
            
        if(hp[top].relate(p)){
            break;
        }else{
            ++bot;
        }
    }

    return top - bot + 1;
}

};

using Point64I = Point<llt>;
using Point64F = Point<Real>;

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
int M;
Point64F P[SIZE];
HalfPlane<Real> Hp[SIZE];
set<int> Set[SIZE];

Real proc(){
    if(0 == Set[1].count(N)){
        return P[1].dist(P[N]);
    }
    
    auto f = [](int pos)->int{
        const auto & s = Set[pos];
        if(s.empty()) return N;
        if(s.size() == N - pos) return 0;
        int ret = N;
        auto it = s.end();
        while(1){
            if(*--it != ret){
                return ret;
            }
            --ret;
            if(it == s.begin()){
                return (*it) - 1;
            }
        }
    };

    int k = 0;
    Hp[k++] = {P[1], P[N]};
    for(int t,i=1;i<N;++i){
        if(t = f(i)){
            assert(i < t && t <= N);
            Hp[k++] = {P[t], P[i]};             
        }

    }

    int bot, top;
    int n = HalfPlane<Real>::sandi(Hp, k, bot, top);
    assert(n >= 3);

    Point64F p;
    vector<Point64F> vec;
    Hp[top+1] = Hp[bot];
    for(int i=bot;i<=top;++i){
        bool b = Hp[i].inter(Hp[i+1], p);
        assert(b);
        vec.emplace_back(p);
    }
    vec.push_back(vec[0]);

    Real ans = 0;
    for(int i=0,n=vec.size();i<n-1;++i){
        ans += vec[i].dist(vec[i+1]);
    }
    ans -= P[1].dist(P[N]);
    return ans;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif  
    N = getInt(); M = getInt();
    for(int i=1;i<=N;++i) P[i].x = getInt(), P[i].y = getInt();
    for(int a,b,i=0;i<M;++i){
        a = getInt(); b = getInt();
        if(a > b) swap(a, b);
        Set[a].insert(b);
    }
    cout << fixed << setprecision(12) << proc() << endl;
    return 0;
}

