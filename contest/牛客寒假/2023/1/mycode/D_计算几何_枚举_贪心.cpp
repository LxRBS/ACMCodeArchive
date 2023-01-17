/**
 * 第一象限给两个点，A和P。其中点A与原点构成一个横平竖直的矩形。
 * 求点P为顶点的横平竖直的矩形，使得两个矩形的交除以两个矩形的并最大
 * 首先，点P分为4种情况，在矩形里面，右边，上边，和右上。
 * 以右边为例，显然（不解释）P有两种可能，一种是与原点构成矩形，另一种是与(0, yA)构成矩形
 * 挨个枚举求最大即可。
 */
#include <bits/stdc++.h>
using namespace std;
 
char *__abc147, *__xyz258, __ma369[1000000];
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
int const SIZE = 5500;
#endif

using Real = long double;
using llt = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

pii A;
pii P;

inline bool isIn(){
    return 0 <= P.first && P.first <= A.first && 0 <= P.second && P.second <= A.second;
}

Real procIn(){
    int a[4] = {
        P.second * P.first,
        (A.second - P.second) * P.first,
        (A.second - P.second) * (A.first - P.first),
        (A.first - P.first) * P.second
    }; 
    sort(a, a + 4);
    return (Real)a[3] / (Real)(A.first * A.second);
}

Real procOut(){
    return (Real)(A.first*A.second) / (Real)(P.first * P.second);
}

Real procRight(){
    // assert(A.second > P.second);
    int fenzi1 = P.second * A.first;
    int fenmu1 = A.first * A.second + P.first * P.second - fenzi1;
    Real t1 = (Real)fenzi1 / (Real)fenmu1;
    
    int fenzi2 = (A.second - P.second) * A.first;
    int fenmu2 = A.first * A.second + P.first * (A.second - P.second) - fenzi2;
    Real t2 = (Real)fenzi2 / (Real)fenmu2;

    return t1 >= t2 ? t1 : t2;
}

Real procTop(){
    // assert(A.first > P.first);

    int fenzi1 = P.first * A.second;
    int fenmu1 = A.first * A.second + P.first * P.second - fenzi1;
    Real t1 = (Real)fenzi1 / (Real)fenmu1;
    
    int fenzi2 = (A.first - P.first) * A.second;
    int fenmu2 = A.first * A.second + (A.first - P.first) * P.second - fenzi2;
    Real t2 = (Real)fenzi2 / (Real)fenmu2;

    return t1 >= t2 ? t1 : t2;
}

Real proc(){
    if(isIn()) return procIn();
    if(P.first > A.first && P.second > A.second) return procOut();
    if(P.first > A.first) return procRight();
    // assert(P.second > A.second);
    return procTop();
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    // ios::sync_with_stdio(0);
    // cin.tie(0); cout.tie(0);
    int nofkase = getInt();
    while(nofkase--){
        A.first = getInt();
        A.second = getInt();
        P.first = getInt();
        P.second = getInt();
        printf("%.12Lf\n", proc());
    }

    return 0;
}


