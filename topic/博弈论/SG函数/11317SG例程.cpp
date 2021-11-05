#include <cstdio>
int A[2049] = {0};
void init(){
	A[1] = 1;
	int k = 2;
	for(int x=1;x<11;++x)for(int i=0;i<(1<<x);++i)
		A[k++] = x + 1;
    A[2048] = 12;
}
int main(){
    init();
    int n;
	while(scanf("%d",&n)&&n){
		int ans = 0;
		for(int i=0;i<n;++i){
			int x;
			scanf("%d",&x);
			ans ^= A[x];
		}
		printf(ans?"YES\n":"NO\n");
	}
	return 0;
}
