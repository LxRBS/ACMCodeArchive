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

};

/// ͹����κ�͹��
template<typename T>struct Convex : public Polygon<T>{

using Dian = Point<T>;
// using Zhixian = Line<T>;
using vt = vector<Dian>;
using Tu = Convex<T>;

Convex():Polygon<T>(){}
Convex(int n):Polygon<T>(n){}

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
    /// ��������0-360 
    ArgCmp<T> cmp;
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

const Point64F ORIGIN(0.L, 0.L);
int N, M;
Convex<Real> Ca, Cb, Cc;
auto & A = Ca.pts;
auto & B = Cb.pts;

Real proc(){
    /// �㲻���������, ����Ҫ������
    /// ע��͹���Ժ�Ľ����һ����N����Ϊ���ߵ�ᱻ�޳�
    Ca.Graham();
    /// ��B��һ��
    for(int i=0;i<M;++i) B[i].x = -B[i].x, B[i].y = -B[i].y;
    Cb.Graham();  
    /// �൱�����ɿɷ�˹����
    Cc = Ca + Cb;
    return Cc.Polygon<Real>::dist(ORIGIN);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    while(1){
        scanf("%d%d", &N, &M);
        if(0 == N && 0 == M) break;
        Ca.init(N); Cb.init(M);
        for(int i=0;i<N;++i) scanf("%Lf%Lf", &A[i].x, &A[i].y);
        for(int i=0;i<M;++i) scanf("%Lf%Lf", &B[i].x, &B[i].y);
        printf("%.12Lf\n", proc());
    }
    return 0;
}
