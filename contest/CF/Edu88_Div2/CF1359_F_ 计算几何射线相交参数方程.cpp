/**
     ������������㡢�ٶȺͷ��򣬳���ʱ���Զ����ʴ���������ײ��һ������ʱ���Ƕ���
     ���ȣ�Ҫ��������û�н��㡣����н��㣬���������
     1 ������У����������ٶȺ�
     2 �����������������ｻ�����õĽ϶���Ǹ�ʱ��
     �ò������̱�ʾ���ߣ�X = P + Dt �� t>=0
     �������Ӱ���Σ���ֱ�߲���������ֱ���ཻ�ͻᳬʱ��
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
int const SIZE = 11;
#else
int const SIZE = 30010;
#endif

typedef int llt;
typedef double Real;
Real const EPS = 1E-10;
inline int sgn(Real x){return x>EPS?1:(x<-EPS?-1:0);}
inline bool is0(Real x){return 0 == sgn(x);}
inline bool isEq(Real x, Real y){return is0(x-y);}

int N;
struct Point{
    llt x, y;
    Point(llt a=0, llt b=0):x(a),y(b){}
}P[SIZE], D[SIZE];

llt Speed[SIZE];

inline llt cross(const Point &a, const Point &b){
    return a.x * b.y - b.x * a.y;
}

inline llt dot(const Point &a, const Point &b){
    return a.x * b.x + a.y * b.y;
}

inline Real dist(const Point &a, const Point &b){
    Real x = a.x - b.x, y = a.y - b.y;
    return sqrt(x*x+y*y);
}

inline Real dist(Real x, Real y, const Point &b){
    x -= b.x; y -= b.y;
    return sqrt(x*x+y*y);
}

/// ��idx�Ƿ��ڵ�jdx�Ĺ켣��
inline bool isIn(int idx, int jdx){
    Real t;
    if(is0(D[jdx].x)){
        t = (P[idx].y - P[jdx].y) / (Real)D[jdx].y;
        if(sgn(t)<0 || !isEq(D[jdx].x*t+P[jdx].x, P[idx].x)) return false;
    }else{ // else Ӧ�ý�����
        t = (P[idx].x - P[jdx].x) / (Real)D[jdx].x;
        if(sgn(t)<0 || !isEq(D[jdx].y*t+P[jdx].y, P[idx].y)) return false;
    } 
    return true; 
}

inline bool isInter(int idx, int jdx, Real &ans){
    /// ƽ�е����
    llt cc = cross(D[idx], D[jdx]);
    if(!cc){
        int status = (isIn(idx, jdx) ? 2 : 0) | (isIn(jdx, idx) ? 1 : 0);
        if(!status) return false;

        if(status == 3){
            ans = dist(P[idx], P[jdx]) / (Speed[jdx] + Speed[idx]);
        }else if(status & 1){
            ans = dist(P[idx], P[jdx]) / Speed[idx];
        }else{
            ans = dist(P[idx], P[jdx]) / Speed[jdx];
        }
        return true;
    }

    /// ���㽻��
    Real ti, tj;
    tj = (cross(P[jdx], D[idx]) - cross(P[idx], D[idx])) / (Real)cc;
    ti = (cross(P[jdx], D[jdx]) - cross(P[idx], D[jdx])) / (Real)cc;
    // assert(isEq(p.x, P[jdx].x+D[jdx].x*tj) && isEq(p.y, P[jdx].y+D[jdx].y*tj));
    if(sgn(tj) < 0 || sgn(ti) < 0) return false;
    
    Real x = P[idx].x+D[idx].x*ti, y = P[idx].y+D[idx].y*ti;       
    ans = max(dist(x, y, P[idx]) / Speed[idx], dist(x, y, P[jdx]) / Speed[jdx]);
    return true;
}

void proc(){
    Real ans = -1, tmp;
    for(int i=1;i<N;++i)for(int j=i+1;j<=N;++j){
        if(isInter(i, j, tmp)){
            // printf("%d %d: %.8f\n", i, j, tmp);
            if(ans < 0 || ans > tmp) ans = tmp;
        }
    }
    if(ans < 0) printf("No show :(\n");
    else printf("%.10f\n", ans);
}

int main(){    
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif
    N = getInt();
    for(int i=1;i<=N;++i){
        P[i].x = getInt();
        P[i].y = getInt();
        D[i].x = getInt();
        D[i].y = getInt();
        Speed[i] = getInt();
    }
    proc();
    return 0;
}