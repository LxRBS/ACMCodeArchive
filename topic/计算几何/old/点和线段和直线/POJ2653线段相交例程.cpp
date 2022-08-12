/*
    依次给定线段，如果后来的线段与前面的线段相交，则称后来者在上面
	问，直到最后都处于最上面位置的线段，可能不止一条
	线段相交的问题
*/
#include <cmath>
#include <cstdio>
#include <cstring>
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
        && cross(v.s,u.e,v.e) * cross(v.s,v.e,u.s) >= 0
        && cross(u.s,v.e,u.e) * cross(u.s,u.e,v.s) >= 0;
}
int const MAXSIZE = 100000;
lineseg_t ls[MAXSIZE];
bool flag[MAXSIZE];
void disp(int n){
	int i;
	for(i=0;i<n;i++)
		printf("%.1lf %.1lf %.1lf %.1lf\n",ls[i].s.x,ls[i].s.y,ls[i].e.x,ls[i].e.y);
}
int main(){
	int n,i,j;
	while(scanf("%d",&n) && n){
		memset(flag,0,sizeof(flag));
		for(i=0;i<n;i++){
            scanf("%lf%lf%lf%lf",&ls[i].s.x,&ls[i].s.y,&ls[i].e.x,&ls[i].e.y);
		}
		for(i=0;i<n-1;i++)for(j=i+1;j<n;j++){
			if ( isOn(ls[i],ls[j]) ){
					flag[i] = true;
					break;
			}
		}
		printf("Top sticks: ");
		for(i=0;i<n-1;i++){
            if( !flag[i] ){
				printf("%d, ",i+1);
			}
		}
		printf("%d.\n",n);
	}
	return 0;
}
