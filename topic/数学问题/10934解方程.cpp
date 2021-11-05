#include <iostream>
double const EPS = 1E-4;
#define isPos(x) ( (x) >= EPS )
#define isNeg(x) ( (x) <= -EPS )
#define isZero(x) ( (x) < EPS && (x) > -EPS )
int CF[11];
double f(double x,int n){
    double sum = (double)(CF[0]);
	double ratio = 1.0 + x;
	double fac = 1.0;
	for(int i=1;i<=n;++i){
		fac = fac * ratio;
		sum += (double)(CF[i])/fac;
	}
	return sum;
}
int main(){
	int n;
	while(scanf("%d",&n)&&n){
       for(int i=0;i<=n;++i)scanf("%d",CF+i);

	   double left,right,mid;
	   double t = f(0.0,n);
	   if ( isZero(t) ){
		   printf("0.00\n");
		   continue;
	   }

	   if( isPos(t) ){
		   left = 0.0;
		   right = 20000.0;
	   }else{
		   left = -1.0 + EPS;
		   right = 0.0;
	   }

	   while(1){
           mid = ( left + right ) / 2.0;
		   t = f(mid,n);
		   if ( isZero(t) ) break;
		   if ( isPos(t) ){
		       left = mid;
		   }else{
			   right = mid;
		   }
	   }

	   printf("%.2lf\n",mid);
	}
	return 0;
}