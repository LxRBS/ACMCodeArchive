/*
     首先判多边形是不是凸的
     然后判圆是否在多边形内
*/
#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;

int const SIZE = 1010;

double const EPS = 1E-9;
inline bool is0(double x){return -EPS<=x&&x<=EPS;}
//return true iff x > y
inline bool isGT(double x,double y){return x-y>EPS;}
//return true iff x < y
inline bool isLT(double x,double y){return x-y<-EPS;}

struct point_t{
    double x,y;
    point_t(double a=0.0,double b=0.0):x(a),y(b){}
};

double dot(point_t const&O,point_t const&A,point_t const&B){
    double xoa = A.x - O.x;
    double yoa = A.y - O.y;
    double xob = B.x - O.x;
    double yob = B.y - O.y;
    return xoa * xob + yob * yoa;
}

double cross(point_t const&O,point_t const&A,point_t const&B){
    double xoa = A.x - O.x;
    double yoa = A.y - O.y;
    double xob = B.x - O.x;
    double yob = B.y - O.y;
    return xoa * yob - xob * yoa;
}

inline double dist(point_t const&A,point_t const&B){
    double x = A.x - B.x;
    double y = A.y - B.y;
    return sqrt(x*x+y*y);
}

//点O是否在线段AB上
inline bool isInter(point_t const&O,point_t const&A,point_t const&B){
	return 0LL == cross(O,A,B)
		&& O.x <= max(A.x,B.x)
		&& O.x >= min(A.x,B.x)
		&& O.y <= max(A.y,B.y)
		&& O.y >= min(A.y,B.y) ;
}

//点O到线段AB的距离
inline double dist(point_t const&O,point_t const&A,point_t const&B){
	if ( isInter(O,A,B) ) return 0.0;

    //计算AO·AB
	double daob = dot(A,O,B);
    if ( isLT(daob,0.0) ) return dist(A,O);

	//计算BO·BA
	double dboa = dot(B,O,A);
	if ( isLT(dboa,0.0) ) return dist(B,O);

	//计算叉积
	double area = cross(O,A,B);
	if ( area < 0 ) area = -area;
	return area / dist(A,B);
}

//点O是否在凸多边形P[n]上
bool isInter(point_t const&O,point_t P[],int n){
	double t = cross(O,P[n-1],P[0]);
	if ( is0(t) ) return min(P[n-1].x,P[0].x) <= O.x
		              && O.x <= max(P[n-1].x,P[0].x)
					  && min(P[n-1].y,P[0].y) <= O.y
					  && O.y <= max(P[n-1].y,P[0].y);

	t = t > 0 ? 1 : -1;
	for(int i=0;i<n-1;++i){
		double tt = cross(O,P[i],P[i+1]);
		if ( is0(tt) ) return min(P[i].x,P[i+1].x) <= O.x
			               && O.x <= max(P[i].x,P[i+1].x)
			               && min(P[i].y,P[i+1].y) <= O.y
			               && O.y <= max(P[i].y,P[i+1].y);

		tt = tt > 0 ? 1 : -1;
		if ( t * tt < 0 ) return false;
	}
	return true;
}

//判断多边形是否为凸的且没有退化
bool isCon(point_t P[],int n){
    P[n] = P[0];P[n+1] = P[1];

    int a[] = {0,0};
    for(int i=0;i<n;++i){
        double tmp = cross(P[i],P[i+1],P[i+2]);
        if ( isLT(tmp,0) ) a[0] = 1;
        if ( isGT(tmp,0) ) a[1] = 1;
    }
    return a[0] ^ a[1];
}

struct circle_t{
    point_t center;
    double radius;
    circle_t(point_t const&p=point_t(),double b=0.0):center(p),radius(b){}
};

//判断圆cir是否在凸多边形P[n]内
inline bool isIn(circle_t const&cir,point_t P[],int n){
    if ( !isInter(cir.center,P,n) ) return false;

    //计算圆心到每个边的距离
    P[n] = P[0];
    for(int i=0;i<n;++i){
        if ( isGT(cir.radius,dist(cir.center,P[i],P[i+1])) ){
            return false;
        }
    }
    return true;
}

int N;
point_t P[SIZE];
circle_t Cir;

bool read(){
    scanf("%d",&N);
    if ( N < 3 ) return false;

    scanf("%lf%lf%lf",&Cir.radius,&Cir.center.x,&Cir.center.y);

    for(int i=0;i<N;++i)scanf("%lf%lf",&P[i].x,&P[i].y);
    return true;
}

int main(){
    //freopen("1.txt","r",stdin);

    while( read() ){
        if ( !isCon(P,N) ){
            puts("HOLE IS ILL-FORMED");
        }else{
            puts(isIn(Cir,P,N)?"PEG WILL FIT":"PEG WILL NOT FIT");
        }
    }
    return 0;
}
