#include <iostream>
#include <cmath>

double const EPS = 1E-9;
double const PI = acos(-1.0);

#define MAX(a,b) ( ( a ) > ( b ) ? ( a ) : ( b ) )
#define MIN(a,b) ( ( a ) < ( b ) ? ( a ) : ( b ) )

inline bool isLT(double x,double y){
	return x <= y - EPS;
}

double X[101];
double Y[101];

double proc(int index){
	double ans = atan2(Y[index+1],X[index+1]) - atan2(Y[index],X[index]);
	if ( isLT(PI,ans) ) ans -= 2.0*PI;
	if ( isLT(ans,-PI) ) ans += 2.0*PI;
	return ans;
}

int main(){
	double k,h;
	int n;
	int index=0;
	scanf("%lf%lf%d",&k,&h,&n);
	for(int i=0;i<n;++i){
		scanf("%lf%lf",X+i,Y+i);
	}
	Y[n] = Y[0];
	X[n] = X[0];
	
	double _max = 0.0;
	double _min = 0.0;
	double sum = 0.0;
	for(int i=0;i<n;++i){
        sum += proc(i);
		_max = MAX(sum,_max);
		_min = MIN(sum,_min);
	}

	double ans = _max - _min;
	if ( isLT(2.0*PI,ans) ) ans = 2.0*PI;

	printf("%.2lf\n",k*h*ans);

	return 0;
}