#include <stdio.h>

int main(){
	int n;
	int y,m,d;

	scanf("%d",&n);

	while(n--){
        scanf("%d%d%d",&y,&m,&d);
        if ( ( 0 == ( m + d ) % 2 )
			|| ( 9 == m && 30 == d )
			|| ( 11 == m && 30 == d ) )
			printf("YES\n");
		else
			printf("NO\n");
	}

	return 0;
}