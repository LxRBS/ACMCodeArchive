/**
 * 就是求点到连续线段的最短距离
 * 依次求出点到每个线段的最短距离，取最小即可
 * 会超longlong范围，因此用int128
 * 实际上直接用long double就行，据说double也行
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

typedef __int128_t llt;
typedef long double Real;

#ifndef ONLINE_JUDGE
int const SIZE = 11;
#else
int const SIZE = 200155;
#endif

inline llt ABS(llt x){return x>=0?x:-x;}


struct Point{
    llt x, y;
    Point(llt a=0,llt b=0):x(a),y(b){}
};

inline llt dot(const Point&O, const Point&A, const Point&B){
    llt xoa = A.x - O.x;
    llt yoa = A.y - O.y;
    llt xob = B.x - O.x;
    llt yob = B.y - O.y;
    return xoa * xob + yoa * yob;
}

inline llt cross(const Point&O, const Point&A, const Point&B){
    llt xoa = A.x - O.x;
    llt yoa = A.y - O.y;
    llt xob = B.x - O.x;
    llt yob = B.y - O.y;
    return xoa * yob - xob * yoa;
}

inline Real dist(const Point &A, const Point &B){
    llt x = A.x - B.x, y = A.y - B.y;
    return sqrt((Real)(x*x+y*y));
}

inline Real dist(const Point &P, const Point &A, const Point &B){
    if(dot(A, P, B) < 0) return dist(P, A);
    if(dot(B, P, A) < 0) return dist(P, B);

    return ABS(cross(A, P, B)) / dist(A, B);
}

Point A, B;
Point Guo;
int N;

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    N = getInt();
    A.x = getInt(); A.y = getInt();
    Guo.x = getInt(); Guo.y = getInt();

    Real ans = 1E100;
    for(int i=1;i<=N;++i){
        B.x = A.x + getInt();
        B.y = A.y + getInt();
        if(B.x==A.x && B.y==A.y){
            ans = min(ans, dist(Guo, A));
        }else{
            ans = min(ans, dist(Guo, A, B));
        }        
        A = B;
    } 
    printf("%.12Lf\n", ans); 
    return 0;
}

