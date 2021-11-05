#include <cstdio>
#include <cmath>

double const PI = acos(-1.0);
double const DELTA = 1E-6;
double R,H,D;

double integral(){
	return (2.0*D*R*R+4.0*D*D*D/3.0+D*D*R*PI) * PI;
}

double integral2(){
	return 4.0*PI*D*D + 2.0*PI*PI*R*D;
}

int main(){
	int nofkase;
	scanf("%d",&nofkase);
	while( nofkase-- ){
		scanf("%lf%lf%lf",&R,&H,&D);
		double v = integral() + PI * ( R + D ) * ( R + D ) * H;
		double s = integral2() + 2.0 * PI * ( R + D ) * H + 2.0 * PI * R * R;
		printf("%.12lf %.12lf\n",v,s);
	}
	return 0;
}
