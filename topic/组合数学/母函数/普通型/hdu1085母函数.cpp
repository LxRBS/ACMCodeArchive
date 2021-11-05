#include <iostream>
using namespace std;

#define SIZE  8001

int main(){
	int a[3];
	int xishu[SIZE];
	int tmp[SIZE];

	while( scanf("%d%d%d",a,a+1,a+2) ){
		if ( 0 == *a && 0 == a[1] && 0 == a[2] ) return 0;

		int n = a[0] + a[1] + a[1] + 5 * a[2];
		for(int i=0;i<=a[0];++i) xishu[i] = 1, tmp[i] = 0;
        for(int i=a[0]+1;i<=n;++i) xishu[i] = tmp[i] = 0;
        
		for(int i=0;i<=a[0];++i)for(int j=0;j<=a[1];++j) 
			tmp[i+j+j] += xishu[i];

		for(int i=0;i<=a[0]+a[1]+a[1];++i) xishu[i] = tmp[i],tmp[i] = 0;

		for(int i=0;i<=a[0]+a[1]+a[1];++i)for(int j=0;j<=a[2];++j)
			tmp[i+5*j] += xishu[i];

		int ans = n+1;
		for(int i=1;i<=n;++i)if( 0 == tmp[i] ){
			ans = i;
			break;
		}
		printf("%d\n",ans);
	}
}
