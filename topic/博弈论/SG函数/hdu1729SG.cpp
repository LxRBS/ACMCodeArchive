#include <iostream>
#include <cmath>
using namespace std;
int const MAXSIZE = 10000;

int sg(int a,int b){
	int k;
	if ( a == b || b == 0 ) return 0;
LL:
	k = (int)ceil( ( sqrt(1.+4.*a) - 3. ) / 2. );
	if ( b == k ) return 0;
	if ( b > k )  return a - b;
 	a = k;
	goto LL;
		
}
int main(){
    int i,n,a,k,count=0;
	while ( scanf("%d",&n) && n!=0 ){
		int ans = 0;
		for ( i=0;i<n;i++ ){
            scanf("%d%d",&a,&k);
			ans ^= sg(a,k);
		}		
		printf("Case %d:\n",++count);
		if ( ans ) printf("Yes\n");
		else       printf("No\n");
	}
	return 0;
}
