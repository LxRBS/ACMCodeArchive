#include<bits/stdc++.h>
using namespace std;
int main(){
	double r,a,b,h;
	scanf("%lf%lf%lf%lf",&r,&a,&b,&h);
	assert (r*2!=b);
	if (r*2<b) return puts("Drop"),0;
	double w=sqrt((a-b)/2.0*(a-b)/2.0+h*h)*r/h;
	double ans=(w-b/2)*h/(a/2-b/2);
	printf("Stuck\n%.10f\n",ans);
} 