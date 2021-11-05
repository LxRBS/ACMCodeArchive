#include <cstdio>
#include <cmath>
using namespace std;

double const PI = acos(-1.0);
double const EPS = 1E-6;

inline bool is0(double x){return -EPS<=x&&x<=EPS;}
inline bool isEq(double x,double y){return is0(x-y);}

double X[205],Y[205],R[205];
int N;

bool read(){
	scanf("%d",&N);
	if ( 0 == N ) return false;
	for(int i=0;i<N;++i)scanf("%lf%lf%lf",X+i,Y+i,R+i);
	return true;
}
//求线段theta与圆idx交线的长度
//线段参数为(tcos(theta),tsin(theta)),0<=t<=500
//给定theta就可以确定一根线段
//两个t之差就是线段与圆交线的长度
double proc(int idx,double theta){
	double a = 1.0;
	double b = - 2.0 * ( X[idx] * cos(theta) + Y[idx] * sin(theta) );
	double c = X[idx] * X[idx] + Y[idx] * Y[idx] - R[idx] * R[idx];
    double delta = b * b - 4.0 * a * c;
    if ( delta <= 0.0 ) return 0.0;
    delta = sqrt(delta);
    //只需检查t2即可，题目数据保证t1不会超过500
    //double t1 = ( -b + delta ) / 2.0;
    double t2 = ( -b - delta ) / 2.0;
    if ( t2 < 0.0 ) return 0.0;
    return delta;
}
double proc(){
    double ret = -1.0;
    double eps = 2.0 * PI / (double)(24*60);
    for(double d=0.0;d<=2.0*PI;d+=eps){
    	double t = 0.0;
    	for(int i=0;i<N;++i) t += proc(i,d);
    	if ( t > ret ) ret = t;
    }
    return ret;
}
int main() {
    while( read() ) printf("%.3lf\n",proc());
	return 0;
}
