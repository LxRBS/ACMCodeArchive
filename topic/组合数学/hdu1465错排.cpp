#include <iostream>
using namespace std;

int main(){
	long long int a[21] = {0,0,1,2};
	for(long long int i=4;i<21;++i) 
		a[i] = (i-1)*(a[i-1]+a[i-2]);

	int n;
	while( EOF != scanf("%d",&n) ) printf("%I64d\n",a[n]);

	return 0;
}
