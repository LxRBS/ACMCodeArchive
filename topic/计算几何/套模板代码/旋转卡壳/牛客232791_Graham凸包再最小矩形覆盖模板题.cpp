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
    if(A == *this || B == *this) return IN & VERTEX;
    if(sgn(this->dot(A, B)) <= 0 && 0 == sgn(this->cross(A, B))){
        return IN & EDGE;
    }
    return OUT;
}
/// this���߶�AB�ľ���
Real dist(const Point &A, const Point &B) const {
    if(IN & this->relate(A, B)) return 0;
    if(sgn(A.dot(*this, B)) <= 0) return this->dist(A);
    if(sgn(B.dot(*this, A)) <= 0) return this->dist(B);
    /// ����Ϊ��
    return sqrt(this->cross(A, B) / (A - B).square());
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
    // T bb = b >= 0 ? b : -c;
    // T cc = c >= 0 ? b : -c;
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

};

/** 5. �߶εĽṹ�壬�߶���ʱҲ�������ʾ **/
template<typename T>struct LineSeg{

/// Ϊ�˽�Լģ�����, ������
using Dian = Point<T>;
using Xianduan = LineSeg<T>;
Dian s, e; // s��e������˳��


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

/// ǰһ����ͺ�һ����ı��, �������������pts[n] == pts[0]
int next(int i) const {return this->pts.size() == ++i ? 0 : i;}
int prev(int i) const {return -1 == --i ? this->pts.size() - 1 : i;}

void init(int n){pts.resize(n);}


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
    if(1 == n) return (p == pts[0]) ? (IN & VERTEX) : OUT;
    if(2 == n) return p.relate(pts[0], pts[1]);
    /// һ��㱣֤
    assert(sgn(pts[0].cross(pts[1], pts[2])) >= 0);
    /// p����1����ʱ�룬��p��Ȼ������
    if(sgn(pts[0].cross(p, pts[1])) >= 0) return OUT;
    /// p����n-1��˳ʱ�룬��p��Ȼ������
    if(sgn(pts[0].cross(p, pts[n-1])) <= 0) return OUT;
    // ����
    int left = 0, right = n - 2, mid;
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

/// ��ת���Ƿ�����С���Ǿ���, 
/// ���ҵ�һ��������ȫ��ס͹�����p, �Ҹþ����������С��
/// ������С���, pans�м�¼4���㣬Ϊ����, �������ʵ��
/// p��֤����ʱ��, ˳ʱ����Ҫ����while�еĹ�ϵ����
Real rcRecatangle(Point<Real> pans[] = nullptr, const Real inf=INF) const {
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
                Dian diDirection(p[(i+1)%n].x - p[i].x, p[(i+1)%n].y - p[i].y);
                Dian zuoDirection(-diDirection.y, -diDirection.x);
                /// �ײ���ֱ��
                Zhixian bLine(p[i], diDirection);
                /// �Ҳ��ֱ��
                Zhixian rLine(p[r], zuoDirection);
                /// �ϲ�ֱ��
                Zhixian tLine(p[t], diDirection);
                /// ���ֱ��
                Zhixian lLine(p[l], zuoDirection);
                /// 4������
                int c919 = bLine.relate(rLine, pans);
                c919 &= rLine.relate(tLine, pans+1);
                c919 &= tLine.relate(lLine, pans+2);
                c919 &= lLine.relate(bLine, pans+3);
                assert(IN & c919);
            }
        }
    }
    return ans;
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
Convex<Real> Con;

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    scanf("%d", &N);
	Con.init(N);
	auto & P = Con.pts;
    for(int i=0;i<N;++i)scanf("%Lf%Lf", &P[i].x, &P[i].y);
    
    int n = Con.Graham();
    Real ans = Con.rcRecatangle();
    cout << fixed << setprecision(12) << ans << endl;
    return 0;
}

