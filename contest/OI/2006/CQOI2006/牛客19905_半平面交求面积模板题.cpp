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
using coor = Real;  // Ĭ������������
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

/** 8 ��ƽ�潻���������� **/
/// ��ƽ�潻��Ҫ�󽻵�����ƶ���ֱ��ʹ��ʵ��������Ϊ����
struct HalfPlane{
    Real a, b, c; // ax+by+c >= 0, ������Ϊ(a, b), 
    HalfPlane(Real aa=0, Real bb=0, Real cc=0):a(aa),b(bb),c(cc){}
    /// ��������һ����ƽ�棬��u��v����ʱ�룬����ƽ����uv�����ֱ�
    HalfPlane(const Point &u, const Point &v){
        /// ��ֱ������һģһ��
        assert(!(u == v));
        this->a = u.y - v.y;
        this->b = v.x - u.x;
        this->c = u.x * v.y - v.x * u.y;
    }
    /// ��p�Ƿ��ڰ�ƽ����
    bool contains(const Point &p) const {
        return sgn(a * p.x + b * p.y + c) >= 0;
    }
    /// ��ƽ���ཻ�󽻵㣬��֤�ཻ
    /// ֻ��һ�������Ҫ���У����Ƿ������෴���ҽ���Ϊ�յ����
    /// �����������������������ֱ�ӵõ���ƽ�潻Ϊ�ռ�
    /// �������ʾ������Ч������false��ʾ�������
    bool inter(const HalfPlane &r, Point &p) const {
        const auto xishu = a * r.b - r.a * b;
        if(is0(xishu)) return false;
        p = {(b * r.c - r.b * c) / xishu, (c * r.a - r.c * a) / xishu};
        return true;
    }
    /// ��ƽ�����ŷ����������ƶ�����d, Ϊ������ʾ���ŷ������������ƶ�
    HalfPlane move(Real d) const {
        return HalfPlane(a, b, c - d * sqrt(a*a+b*b));
    }
};

/// ��ƽ�潻������������
/// ��֤��������޵ģ�������Ҫ�Ӱ�Χ�У����n�϶�����4
/// ��ı�hp�����ݣ�0-index
/// ���������hp[bot..top]��
/// ����top-bot+1������ƽ������������С��3��˵��ԭ����Ϊ�ռ�
int sandi(HalfPlane hp[], int n, int&bot, int &top){
    /// ���ݷ���������(-180,180]�Ƚϴ�С���Ƕ���ͬԽ����������ԽС
    sort(hp, hp+n, [](const HalfPlane&u, const HalfPlane&v)->bool{
        /// �������ֱ�λ��x�����£�����ֱ�ӵõ����
        int ly = sgn(u.b) >= 0 ? 1 : -1;
        int ry = sgn(v.b) >= 0 ? 1 : -1;
        if(ly != ry) return ly < ry;
        
        /// �������x���ϣ���һ��һ��
        if(is0(u.b) && is0(v.b) && sgn(u.a * v.a) < 0) return u.a > v.a;
        
        /// ����������������Ϊ��
        int chaji = sgn(u.a * v.b - u.b * v.a);
        if(chaji) return chaji > 0;
        
        /// ���˴�˵��ƽ�� 
        /// ��a����0
        if(sgn(u.a) > 0){
            /// ��hp1��hp2�������������������a1x+b1y+c1=0��a2x+b2y+c2>0
            return u.c * v.a < u.a * v.c;
        }
        if(sgn(u.a) < 0){ // С��0���Ƿ�����
            return u.c * v.a > u.a * v.c;
        }
        /// aΪ0��b�ز�Ϊ0
        if(sgn(u.b > 0)){
            return u.c * v.b < u.b * v.c;
        }
        return u.c * v.b > u.b * v.c;
    });

    /// ��ȫƽ�еķ�����ֻȡһ��
    n = unique(hp, hp+n, [](const HalfPlane&u, const HalfPlane&v)->bool{
        int ly = sgn(u.b) >= 0 ? 1 : -1;
        int ry = sgn(v.b) >= 0 ? 1 : -1;
        if (ly != ry) return false;
        if (is0(u.b) && is0(v.b)) return u.a * v.a > 0;
        return is0(u.a * v.b - v.a * u.b);        
    }) - hp;

    /// ��ѭ��
    bot = 0, top = 1;
    Point p;
    for(int i=2;i<n;++i){
        /// ��ǰ�˵�������ƽ���ཻ
        while(bot < top){
            bool b = hp[top-1].inter(hp[top], p);
            if(!b) return bot = top = -1, 0; // ֱ�ӷ��ؿռ�����

            /// �����ڵ�ǰ��ƽ���������            
            if(hp[i].contains(p)){
                break;
            }else{
                --top;
            }
        }
        /// ��׶˵�������ƽ���ཻ
        while(bot < top){
            bool b = hp[bot].inter(hp[bot+1], p);
            if(!b) return bot = top = -1, 0;

            if(hp[i].contains(p)){
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
        if(hp[bot].contains(p)){
            break;
        }else{
            --top;
        }
    }
    while(bot < top){
        bool b = hp[bot].inter(hp[bot+1], p);
        if(!b) return bot = top = -1, 0;  
            
        if(hp[top].contains(p)){
            break;
        }else{
            ++bot;
        }
    }

    return top - bot + 1;
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
int const SIZE = 23;
#else
int const SIZE = 1010;
#endif

HalfPlane Hp[SIZE];
Point P[SIZE];
int N;

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int k = 0;
    /// ��Χ��
    Hp[k++] = {Point(-INF, 1), Point(-INF, 0)}; // ��
    Hp[k++] = {Point(+INF, 0), Point(+INF, 1)}; // ��
    Hp[k++] = {Point(1, +INF), Point(0, +INF)}; // ��
    Hp[k++] = {Point(0, -INF), Point(1, -INF)}; // ��
    N = getInt();
    for(int m,i=0;i<N;++i){
        m = getInt();
        for(int j=0;j<m;++j) P[j].x=getInt(), P[j].y=getInt();
        P[m] = P[0];
        for(int j=0;j<m;++j) Hp[k++] = {P[j], P[j+1]};
    }
    
    int bot, top;
    int n = sandi(Hp, k, bot, top);
    if(n <= 2) {
        puts("0.000"); return 0;
    }
    /// �󽻵�
    Point p;
    bool b = Hp[top].inter(Hp[bot], p);
    assert(b);
    vector<Point> vec(1, p);
    for(int i=bot; i<top;++i){
        bool b = Hp[i].inter(Hp[i+1], p);
        assert(b);        
        vec.emplace_back(p);
    }
    Real ans = 0;
    for(int i=0,n=vec.size();i<n-1;++i){
        ans += cross(vec[0], vec[i], vec[i+1]);
    }
    cout << fixed << setprecision(3) << 0.5 * ans << endl;
    return 0;
}
