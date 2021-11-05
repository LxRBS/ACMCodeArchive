#include <cstdio>
#include <cmath>

char Input[100];
double X[3],Y[3];
double L[3],A[3];//边长及角

double const PI = acos(-1.0);
double const EPS = 1E-6;
#define is0(x) ( -EPS < (x) && (x) < EPS )

inline double dist(double x1,double y1,double x2,double y2){
	double x = x1 - x2;
	double y = y1 - y2;
	return sqrt( x * x + y * y );
}

int main(){
	while( scanf("%s",Input) ){
        if ( 'E' == *Input ) return 0;
		sscanf(Input,"%lf",X);
		scanf("%lf",Y);
		scanf("%lf%lf",X+1,Y+1);
		scanf("%lf%lf",X+2,Y+2);
        
		//求边长
		L[0] = dist(X[1],Y[1],X[2],Y[2]);
		L[1] = dist(X[0],Y[0],X[2],Y[2]);
		L[2] = dist(X[0],Y[0],X[1],Y[1]);

		//求角
		A[0] = acos((L[1]*L[1]+L[2]*L[2]-L[0]*L[0])/(2.0*L[1]*L[2]));
		if ( A[0] < 0 ) A[0] += PI;

		A[1] = acos((L[0]*L[0]+L[2]*L[2]-L[1]*L[1])/(2.0*L[0]*L[2]));
		if ( A[1] < 0 ) A[1] += PI;

		A[2] = PI - A[0] - A[1];

		int n;

		//枚举
		for(n=3;n<1001;++n){
            double t0 = A[0] * (double)n / PI;
			double t1 = A[1] * (double)n / PI;
            double t2 = A[2] * (double)n / PI;
            int a = (int)( t0 + 0.5 );
			int b = (int)( t1 + 0.5 );
			int c = (int)( t2 + 0.5 );
			if ( is0(t0-a) && is0(t1-b) ) break;
		}

		printf("%d\n",n);
	}
	return 0;
}