/*
   给定一条线段和一个矩形（横平竖直），问是否有交点
   转化为线段与线段相交
   另外，要考虑线段完全在矩形内的情形！！！
*/
#include <cmath>
#include <iostream>
using namespace std;
double const INF = 1E200;
double const EPS = 1E-6;
double const PI = acos(-1.);
#define MAX(x,y) ( ( (x) > (y) ) ? (x) : (y) )
#define MIN(x,y) ( ( (x) < (y) ) ? (x) : (y) )
inline bool isZero(double x){return fabs(x)<EPS;}
inline bool isEqual(double x,double y){return fabs(x-y) < EPS;}


struct point_t{
	double x;
	double y;
	point_t(double xx=0.,double yy=0.){x=xx;y=yy;}
};
inline bool isEqual(point_t const &A,point_t const &B){
	double x = A.x - B.x;
	double y = A.y - B.y;
	double s = sqrt( x * x + y * y );
	return fabs(s) < EPS;
}

struct lineseg_t{
	point_t s;
	point_t e;
	lineseg_t(double x1=0.,double y1=0.,double x2=0.,double y2=0.){
		s.x = x1; s.y = y1; e.x = x2; e.y = y2;
	}
};

double cross(point_t const &O,point_t const &A,point_t const &B){
	double xOA = A.x - O.x;
	double yOA = A.y - O.y;
	double xOB = B.x - O.x;
	double yOB = B.y - O.y;
	return xOA * yOB - xOB * yOA;
}
bool isOn(lineseg_t const &u,lineseg_t const &v){
    return MAX(u.s.x,u.e.x) >= MIN(v.s.x,v.e.x)
        && MAX(v.s.x,v.e.x) >= MIN(u.s.x,u.e.x)
        && MAX(u.s.y,u.e.y) >= MIN(v.s.y,v.e.y)
        && MAX(v.s.y,v.e.y) >= MIN(u.s.y,u.e.y)
        && cross(v.s,u.e,v.e) * cross(u.e,v.e,u.s) >= 0
        && cross(u.s,v.e,u.e) * cross(u.s,u.e,v.s) >= 0;
}

lineseg_t ls;
lineseg_t rect[4];

int main(){
    int n;
	double xleft,ytop;
	double xright,ybottom;
	cin>>n;
	while(n--){
        cin>>ls.s.x>>ls.s.y>>ls.e.x>>ls.e.y;
		cin>>xleft>>ytop>>xright>>ybottom;
		if ( ( ls.s.x - xleft ) * ( ls.s.x - xright ) <= 0
			&& ( ls.s.y - ytop ) * ( ls.s.y - ybottom ) <= 0
			&& ( ls.e.x - xleft ) * ( ls.e.x - xright ) <= 0
			&& ( ls.e.y - ytop ) * ( ls.e.y - ybottom ) <= 0
			){
			cout<<"T\n";
			continue;
		}
		if ( isOn(ls,lineseg_t(xleft,ytop,xright,ytop) ) ){
			cout<<"T\n";
			continue;
		}
		if ( isOn(ls,lineseg_t(xleft,ytop,xleft,ybottom) ) ){
			cout<<"T\n";
			continue;
		}
		if ( isOn(ls,lineseg_t(xright,ybottom,xright,ytop) ) ){
			cout<<"T\n";
			continue;
		}
		if ( isOn(ls,lineseg_t(xleft,ybottom,xright,ybottom) ) ){
			cout<<"T\n";
			continue;
		}
		cout<<"F\n";
	}
	return 0;
}
