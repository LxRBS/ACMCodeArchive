#include <stdlib.h>
#include <stdio.h>

int leq(const void *a,const void *b) { 	return (*(int*)a) - (*(int*)b); }

int ballon[200000];

int main(){
	int n; scanf("%d", &n);
	for(int i = 0; i < n; i++) scanf("%d",ballon+i);
	qsort(ballon,n,sizeof(int),leq);
	
	double mf = 1.0;
	for(int i = 0; i < n; i++) if (ballon[i] > i+1) { printf("impossible\n"); return 0; }
	else if (mf > (double)(ballon[i]) / (i+1)) mf = (double)(ballon[i]) / (i+1);

	printf("%lf\n",mf);

	return 0;
}
