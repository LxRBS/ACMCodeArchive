/**
 * 平面若干个点，看做光源。每个点发出最多k种方向的光域。对第i种光域，范围为[a, b]，
 * 意思为与x轴正方向顺时针夹角，问每个点一共被其他多少个点照到。每种光域的范围不重叠
 * 如果考虑只有一种光域，将光线的两个范围看做是两根坐标轴，
 * 则某个点能够被照到的次数，显然就是其“左下”方点的数量，显然是一个二维偏序的问题
 * KNlog(N)可以解决，感觉数据没有很多，一发过
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
int const SIZE = 15;
#else
int const SIZE = 1E5+5;
#endif

struct bit_t{

int n;
int c[SIZE];

void init(int nn){fill(c, c+(n=nn)+1, 0);}
int lowbit(int x){return x&-x;}    
void modify(int pos, int d){ // pos位置加d
    while(pos<=n) c[pos] += d, pos += lowbit(pos);
}
int query(int pos){
    int ans = 0;
    while(pos) ans += c[pos], pos -= lowbit(pos);
    return ans;
}

}Tree;

using pii = pair<int, int>;
using vpii = vector<pii>;
using Real = long double;
using pdd = pair<Real, Real>;
using pddi = pair<pdd, int>;

Real const PI = acos(-1.0);
Real const EPS = 1E-9;
inline int sgn(Real x){return x>=EPS?1:(x<=-EPS?-1:0);}
inline bool is0(Real x){return 0 == sgn(x);}

int N, K;
vpii A, B;
pddi C[SIZE];
Real Y[SIZE];
int Ans[SIZE];

/// 坐标转换
void proc(Real alpha, Real beta){
    Real cosa = cos(alpha), sina = sin(alpha);
    Real cosb = cos(beta), sinb = sin(beta);
    Real sinbma = sin(beta - alpha);
    Real sinamb = -sinbma;

    for(int i=0;i<N;++i){
        Real x = A[i].first, y = A[i].second;
        C[i].first.first = (x * sinb - y * cosb) / sinbma;
        Y[i] = C[i].first.second = (x * sina - y * cosa) / sinamb;
        C[i].second = i;
    }
}

/// 光域是一条竖直直线
void ttproc(){
    using vi = vector<int>;
    vpii x[50000+5];
    for(int i=0;i<N;++i){
        x[A[i].first].emplace_back(A[i].second, i);
    }
    for(int i=0;i<=50000;++i){
        if(x[i].empty()) continue;
        sort(x[i].begin(), x[i].end());
        for(int j=x[i].size()-1;j>=0;--j){
            Ans[x[i][j].second] += j;
        }
    }
}

/// 光域只有一条直线
void teproc(int pos){
    if(90 == B[pos].first) return ttproc();

    Real k = tan(-B[pos].first*PI/180);
    vector<Real> vec;
    for(int i=0;i<N;++i){
        Real x = A[i].first, y = A[i].second;
        vec.push_back(y - k * x);
    }

    sort(vec.begin(), vec.end());
    int n = unique(vec.begin(), vec.end(), [](Real a, Real b){return is0(a-b);}) - vec.begin();
    vpii x[n];
    for(int i=0;i<N;++i){
        Real b = A[i].second - A[i].first * k;
        int t = lower_bound(vec.begin(), vec.end(), b, [](Real a, Real b){return sgn(a - b) <= 0;}) - vec.begin();
        x[t].emplace_back(A[i].second, i);
    }
    for(int i=0;i<n;++i){
        if(x[i].empty()) continue;
        sort(x[i].begin(), x[i].end());
        for(int j=x[i].size()-1;j>=0;--j){
            Ans[x[i][j].second] += j;
        }        
    }
}

/// 处理第pos个光线
void proc(int pos){
    if(B[pos].first == B[pos].second) return teproc(pos);

    Real alpha = -B[pos].first * PI / 180;
    Real beta = -B[pos].second * PI / 180;
    proc(alpha, beta);

    /// 对C求每个点有多少点在它的左下方即可
    sort(Y, Y+N);
    int n = unique(Y, Y+N, [](Real a, Real b){return is0(a-b);}) - Y;

    sort(C, C+N, [](pddi &a, pddi &b){
        int t = sgn(a.first.first - b.first.first);
        if(t) return a.first.first < b.first.first;
        t = sgn(a.first.second - b.first.second);
        if(t) return a.first.second < b.first.second;
        return a.second < b.second;
    });
    Tree.init(N);
    for(int i=0;i<N;++i){
        int y = lower_bound(Y, Y+n, C[i].first.second, [](Real a, Real b){return sgn(a - b) <= 0;}) - Y;
        Ans[C[i].second] += Tree.query(y);
        Tree.modify(y, 1);
    }
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    N = getInt(); K = getInt();
    A.reserve(N);
    for(int x,y,i=0;i<N;++i){
        x = getInt(); y = getInt();
        A.emplace_back(x, y);
    }
    B.reserve(K);
    for(int x,y,i=0;i<K;++i){
        x = getInt(); y = getInt();
        B.emplace_back(x, y);
    }
    for(int i=0;i<K;++i){
        proc(i);
    }
    for(int i=0;i<N;++i)printf("%d ", Ans[i]);
    return 0;
}
