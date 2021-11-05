#include <stdio.h>
#include <math.h>

double const Arr[] = {
	0,
	0,
	log10(2.0),
	log10(3.0),
	log10(4.0),
	log10(5.0),
	log10(6.0),
	log10(7.0),
	log10(8.0),
	log10(9.0),
	1.0
};

int main(){
	int i,n,nofcase;
	scanf("%d",&nofcase);
	while(nofcase--){
		scanf("%d",&n);
		double t = n * log10((double)n);
		t = t - (long long int)t;
		i = 1;
		while( t >= Arr[i] ) i++;
		printf("%d\n",i-1);
	}
	return 0;
}
