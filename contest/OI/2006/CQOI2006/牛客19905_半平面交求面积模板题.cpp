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
int const SIZE = 23;
#else
int const SIZE = 1010;
#endif

HalfPlane<Real> Hp[SIZE];
Point64F P[SIZE];
int N;

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int k = 0;
    /// ��Χ��
    Hp[k++] = {Point64F(-INF, 1), Point64F(-INF, 0)}; // ��
    Hp[k++] = {Point64F(+INF, 0), Point64F(+INF, 1)}; // ��
    Hp[k++] = {Point64F(1, +INF), Point64F(0, +INF)}; // ��
    Hp[k++] = {Point64F(0, -INF), Point64F(1, -INF)}; // ��
    N = getInt();
    for(int m,i=0;i<N;++i){
        m = getInt();
        for(int j=0;j<m;++j) P[j].x=getInt(), P[j].y=getInt();
        P[m] = P[0];
        for(int j=0;j<m;++j) Hp[k++] = {P[j], P[j+1]};
    }
    
    int bot, top;
    int n = HalfPlane<Real>::sandi(Hp, k, bot, top);
    if(n <= 2) {
        puts("0.000"); return 0;
    }
    /// �󽻵�
    Point64F p;
    bool b = Hp[top].inter(Hp[bot], p);
    assert(b);
    vector<Point64F> vec(1, p);
    for(int i=bot; i<top;++i){
        bool b = Hp[i].inter(Hp[i+1], p);
        assert(b);        
        vec.emplace_back(p);
    }
    Real ans = 0;
    for(int i=0,n=vec.size();i<n-1;++i){
        ans += vec[0].cross(vec[i], vec[i+1]);
    }
    cout << fixed << setprecision(3) << 0.5 * ans << endl;
    return 0;
}
