/**
 * ����һ��͹�������״�ı�ľ�壬�����кܶ�Բ����Բ�����ܻ��ص�
 * ��ľ���ʼλ����ֱƽ���ڣ�����ÿ��������꣬����Բ����Բ�ĺͰ뾶
 * ���ڽ���ľ��ĵ�V����̶�ס��Ȼ�����������������´ﵽƽ��λ��
 * �ʴ�ʱ͹����ε�N�����������
 * ֻ������������꣬����һ������任���ɡ�
 * ���ȿ����������͹����ε����ģ��ٿ������Բ�������ģ����ǿ��������ľ�����������
 * Բ�����������꼰�����ʹ�ø��ֹ�ʽ���������ת��Ϊ·�����ֽ��м���
 * ���н���ԭ����������ֱ�����
 */
#include <bits/stdc++.h>
using namespace std;

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
int const SIZE = 2010;
#endif

using Real = double;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<Real, Real>;
using vpii = vector<pii>;

Real const EPS = 1E-8;
Real const PI = acos(-1.0);
inline int sgn(Real x){return x>EPS?1:(x<-EPS?-1:0);}
inline bool is0(Real x){return 0 == sgn(x);} 
inline Real sqr(Real x){return x * x;}
inline Real cub(Real x){return x * x * x;}
inline Real myacos(Real x){
    if(x > 1) x = 1.0;
    if(x < -1) x = -1.0;
    return acos(x);
}

struct Point{
    Real x, y;
    Real dist(const Point &b)const{
        Real u = x - b.x, v = y - b.y;
        return sqrt(u*u+v*v);
    }
};

struct Circle{
    Point center;
    Real radius;
    /// ����Բ�ཻ������Բ���Ƕȵ�����,������һ�Σ�Ҳ����������
    /// �Ƕȷ�ΧΪ[-Pi, Pi)
    vpii inter(const Circle &b)const{
        Real d123 = center.dist(b.center);
        Real u111 = fabs(radius - b.radius);
        Real u222 = radius + b.radius;
        assert(sgn(u222-d123) > 0 && sgn(d123 - u111) > 0);

        Real cosvalue = (radius * radius + d123 * d123 - b.radius * b.radius) / (2.0 * radius * d123);
        Real jiao = myacos(cosvalue);
        Real anchor = atan2(b.center.y - center.y, b.center.x - center.x);
        Real from = anchor - jiao, to = anchor + jiao;

        vpii ans;
        if(sgn(to - PI) >= 0){ // ������
            ans.emplace_back(-PI, to-PI-PI);
            ans.emplace_back(from, PI);
            return ans;
        }
        if(sgn(from+PI) < 0){ // ������
            ans.emplace_back(-PI, to);
            ans.emplace_back(from+PI+PI, PI);
            return ans;
        }
        ans.emplace_back(from, to);
        return ans;
    }
};

Real cross(const Point &O, const Point &A, const Point &B){
    Real xoa = A.x - O.x, yoa = A.y - O.y;
    Real xob = B.x - O.x, yob = B.y - O.y;
    return xoa * yob - xob * yoa;
}

/// ԭ�������ֵ
inline Real diff(Real (*f)(const Circle&, Real), const Circle&c, Real alpha, Real beta){
    return  f(c, beta) - f(c, alpha); 
}

/// ������ĺ�����ȱһ��0.5������
Real f(const Circle &c, Real theta){
    return c.radius * (c.radius * theta + c.center.x * sin(theta) - c.center.y * cos(theta));
}

/// �����ĵ�x�����ԭ������ȱһ��0.5������
Real fx(const Circle &c, Real theta){
    Real sint = sin(theta);
    Real r2 = sqr(c.radius);
    return c.radius * ((sqr(c.center.x)+r2)*sint + c.radius*c.center.x*(theta+0.5*sin(theta+theta)) - r2*cub(sint)/3.0);
}

/// �����ĵ�y�����ԭ������ȱһ��0.5������
Real fy(const Circle &c, Real theta){
    Real cost = cos(theta);
    Real r2 = sqr(c.radius);
    return c.radius * (r2*cub(cost)/3.0 + c.radius*c.center.y*(theta-0.5*sin(theta+theta)) - (r2+sqr(c.center.y))*cost);
}

/// ��Բ����������0��ʼ
tuple<Real, Real, Real> unite_circles(const Circle c[], int n){
    /// �������Բ�ཻ�����
    vvi status(n, vi());
    vi han(n, 0);
    for(int i=0;i<n;++i){
        if(han[i]) continue; // i������
        auto ci = c + i;
        if(is0(ci->radius)){
            han[i] = 1; continue;
        }

        for(int j=i+1;j<n;++j){
            auto cj = c + j;
            if(is0(cj->radius)){
                han[j] = 1; continue;
            }
            Real u = ci->center.dist(cj->center);
            Real v1 = fabs(ci->radius - cj->radius);
            Real v2 = ci->radius + cj->radius;
            if(sgn(v1-u) >= 0){ // ����
                if(sgn(ci->radius - cj->radius) >= 0){
                    han[j] = 1; // j������
                }else{
                    han[i] = 1; // i��j������i�Ͳ���������
                    break;
                }
            }else if(sgn(v2-u) > 0){ // �ཻ
                status[i].push_back(j);
                status[j].push_back(i);
            }
        }        
    }
    /// ����ÿ��Բ
    Real ans = 0, ansx = 0, ansy = 0;
    vpii vec;
    for(int i=0;i<n;++i){
        if(han[i]) continue; // ˵���Ǳ�������
        const Circle * ci = c + i;
        const vi & st = status[i];
        if(st.empty()){ // ˵������Բ���Ǳ߽�
            ans += diff(f, *ci, -PI, PI);
            ansx += diff(fx, *ci, -PI, PI);
            ansy += diff(fy, *ci, -PI, PI);
            continue;
        }
        vec.clear(); 
        vec.reserve(st.size());
        /// ��ÿ���ཻ��Բ���ཻ����
        for(int j: st){
            auto tmp = ci->inter(c[j]);
            vec.insert(vec.end(), tmp.begin(), tmp.end());
        }
        /// �ཻ��������
        sort(vec.begin(), vec.end());
        /// ��ÿһ��¶�������Բ��������
        Real left = -PI;
        for(const auto &p: vec){
            if(left < p.first){ // ˵����һ�α�Ե
                ans += diff(f, *ci, left, p.first);  
                ansx += diff(fx, *ci, left, p.first);
                ansy += diff(fy, *ci, left, p.first);
                left = p.second;
            }else if(left < p.second){ // ���±߽�����
                left = p.second;
            }
        }
        /// ����ټ���һ�Σ�������û��
        ans += diff(f, *ci, left, PI);
        ansx += diff(fx, *ci, left, PI);
        ansy += diff(fy, *ci, left, PI);
    }
    return {ans, ansx, ansy}; // ������0.5�������
}

int N, C, V;
Circle Cir[SIZE];
Point P[SIZE];

void proc(){
    /// ��Բ��������
    auto ans = unite_circles(Cir, C);
    /// �����ε����ĺ����
    Real cgx = 0, cgy = 0, area = 0;
    for(int i=2;i<N;++i){
        Real tmp = cross(P[0], P[i-1], P[i]);
        area += tmp;
        cgx += tmp * (P[0].x+P[i-1].x+P[i].x)/3.0;
        cgy += tmp * (P[0].y+P[i-1].y+P[i].y)/3.0;
    }
    /// ��ľ�������
    Real leftarea = area - get<0>(ans);
    Real leftx = (cgx - get<1>(ans)) / leftarea;
    Real lefty = (cgy - get<2>(ans)) / leftarea;
    /// ͹�������һ������ƽ��
    Point origin = P[V];
    for(int i=0;i<N;++i) P[i].x -= origin.x, P[i].y -= origin.y;
    leftx -= origin.x, lefty -= origin.y;
    /// ��ת
    Real theta = atan2(lefty, leftx);
    theta = -0.5 * PI - theta;
    Real ca = cos(theta), sa = sin(theta);
    for(int i=0;i<N;++i){
        Real x = P[i].x, y = P[i].y;
		P[i].x = x * ca - y * sa + origin.x;
		P[i].y = y * ca + x * sa + origin.y; 
    }
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    N = getInt(); C = getInt(); V = getInt() - 1;
    for(int i=0;i<N;++i) P[i].x = getInt(), P[i].y = getInt();
    for(int i=0;i<C;++i) Cir[i].center.x = getInt(), Cir[i].center.y = getInt(), Cir[i].radius = getInt();
    proc();
    for(int i=0;i<N;++i) printf("%.7f %.7f\n", P[i].x, P[i].y);
    return 0;
}

