#include <iostream>
#include <cmath>
using namespace std;
typedef long long int ll_t;


int main(){
	ll_t n;

	while( EOF != scanf("%I64d",&n) ){
		if ( n < 0 ) return 0;

		if ( 1 == n ){
			printf("    1\n");
			continue;
		}

		ll_t m = n;
		for(ll_t i=2;m>1;++i){
			if ( i * i > m ){
				printf("    %I64d\n",m);
				break;
			}
			while( m % i == 0 ){
				printf("    %I64d\n",i);
				m /= i;
			}
		}

		printf("\n");
	}
	return 0;
}
