/**
 * ͹�������ײ��⣬���ɿɷ�˹���תΪ
 * ����͹�������ײ��������
 * תΪ�߶��������ཻ������
 * ����н��㣬�������С��
 * ����ﵽ1E9, ��longlongֻ�ܶ�30%
 * Ҫ��int128������ʹ��longdouble
 * ����INFҲҪ���õ�1E10, ���õ�1E9ֻ��AC99%
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
using llt = __int128_t;

Real const EPS = 1E-9; // ������Ҫ����
Real const PI = acos(-1);
Real const INF = 1E10;  // ������Ҫ����

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
/// ��������, [0, 36)
template<typename T> struct ArgCmp{
using Dian = Point<T>;

const Dian center; // ���ĵ�, Ĭ����ԭ��

ArgCmp(const Dian &a = Dian()):center(a){}

bool operator () (const Dian &a, const Dian &b) const {
    auto calLoc = [&](const Dian &p)->int{ // ��������        
        if(sgn(p.y) > 0) return 2; // (0, 180)
        if(sgn(p.y) < 0) return 4; // (180, 360)
        if(sgn(p.x) > 0) return 1; // 0��
        if(sgn(p.x) < 0) return 3; // 180��
        return 0; // ԭ��
    };

    const Dian da(a - center);
    const Dian db(b - center);
    const int aloc = calLoc(da);
    const int bloc = calLoc(db);
    if(aloc != bloc) return aloc < bloc;

    const auto chaji = sgn(da.cross(db));
    if(chaji) return chaji > 0; // ��a��b����ʱ�� 
    /// ����˵������һ��, ������
    return sgn(da.square() - db.square()) < 0;
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
    // T aa = a >= 0 ? a : -a;
    // T bb = b >= 0 ? b : -b;
    // T cc = c >= 0 ? c : -c;
    // T g = 0;
    // if(0 == aa){ // bb ��Ȼ��Ϊ0
    //     if(0 == cc) g = bb;
    //     else g = __gcd(bb, cc);
    // }else if(0 == bb){
    //     if(0 == cc) g = aa;
    //     else g = __gcd(aa, cc);
    // }else{
    //     g = __gcd(aa, bb);
    //     if(cc) g = __gcd(g, cc);
    // }
    // this->a /= g, this->b /= g, this->c /= g;
    // if(a < 0 || (0 == a && b < 0)) {a = -a, b = -b, c = -c;}
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

/// �ɿɷ�˹���ͣ�ֻ������͹��
/// ��������͹�����a��b,͹�����c=a+b����a��b�е����е�����
/// ����һ��͹����Σ�Ϊ�ɿɷ�˹���ͣ����ܴ湲�ߵ�
const Tu operator + (const Convex & r) const {
    /// ��������0-360 
    ArgCmp<T> cmp;
    /// ��������
    auto lowleft = [](const Dian &u, const Dian &v)->bool{
        int t = sgn(u.y - v.y);
        if(t) return t < 0;
        return u.x < v.x;
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

using Vector = Point64I;

int N, M;

Convex<llt> Ca, Cb, Cc;

auto & A = Ca.pts;
auto & B = Cb.pts;

Vector SpeedA, SpeedB;
Vector Speed;


void proc(){
    /// ���ɿɷ�˹����
    Cc = Ca + Cb;

    /// ԭ���Ƿ��ڶ������
    static const Point64I origin(0, 0);
    if(IN & Cc.relate(origin)){
        return (void)puts("0");
    }

    /// ��ԭ����ٶ�
    Vector speed(SpeedB - SpeedA);
    /// ȡ�켣�ϵ�����Զ��
    Point64I inf(speed.x * INF, speed.y * INF);
    /// �켣��ֱ�ߺ��߶�
    Line<llt> track(origin, inf);
    LineSeg<llt> xianduan(origin, inf);

    /// ���߶�(origin, inf)�����ε�����Ľ���
    Real ans = -1, tmp;
    Point64F p;
    for(int t,i=0,n=Cc.pts.size();i<n;++i){
        /// ����߶��ཻ����һ������
        if(JIAO & xianduan.relate(Cc.pts[i], Cc.pts[(i+1)%n])){
            t = track.relate(Line<llt>(Cc.pts[i], Cc.pts[(i+1)%n]), &p);
            if(t & JIAO){
                tmp = p.length();
            }else if(t & CHONGHE){
                /// ��ײ���Ȼ��C[i]����C[i+1]
                tmp = min(Cc.pts[i].length(), Cc.pts[(i+1)%n].length());
            }else{
                throw runtime_error("XX");
            }            
            if(ans < 0 || tmp < ans) ans = tmp;
        }
    }
    if(ans < 0) return (void)puts("-1");
    return (void)(cout << fixed << setprecision(12) << ans / speed.length() << endl);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    Ca.init(N = getInt());
    for(int i=0;i<N;++i) A[i].x = getInt(), A[i].y = getInt();
    Cb.init(M = getInt());
    for(int i=0;i<M;++i) B[i].x = -getInt(), B[i].y = -getInt();

    SpeedA.x = getInt(), SpeedA.y = getInt();
    SpeedB.x = getInt(), SpeedB.y = getInt();

    proc();
    return 0;
}
