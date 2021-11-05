#include <iostream>

int Ans[1001]={0};
int gcd(int a,int b){
	int r = a % b;
	while( r ){
		a = b;
		b = r;
		r = a % b;
	}
	return b;
}
int fun(int n){
	if ( Ans[n] ) return Ans[n];

	if ( Ans[n-1] ){
        int x = n;
		int y = 1;
		int cnt = 0;
		for(y=1;y<n;++y){
            if ( 1 == gcd(x,y) )
				++cnt;
		}
		return Ans[n] = Ans[n-1] + cnt + cnt;
	}

	int t = n - 1;
	while( 0 == Ans[t] ) --t;
    for(;t<n;++t)fun(t);
	return fun(n);
}

int main(){
	Ans[1] = 3;
	Ans[2] = 5;
	
    int Kase;
	scanf("%d",&Kase);
	for(int kase=1;kase<=Kase;++kase){
		int n;
		scanf("%d",&n);
        printf("%d %d %d\n",kase,n,fun(n));
	}

	return 0;
}