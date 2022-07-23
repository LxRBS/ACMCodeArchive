#include <cstdio>
#include <cmath>
#define MN 1000000

int n,a[MN+5];

void solve(){
	scanf("%d",&n);
	int B = ceil(sqrt(n));
	int b = n%B;
	for(int i=B;i<=n;i+=B){
		for(int j=1;j<=B;j++){
			a[i-B+j] = i-j+1;
		}
	}
	for(int i=1;i<=b;i++){
		a[n-b+i] = n-i+1;
	}
	for(int i=1;i<=n;i++){
		printf("%d%c",a[i]," \n"[i==n]); 
	}
}

int main(){
	int T;
	scanf("%d",&T);
	while(T--) solve();
}
