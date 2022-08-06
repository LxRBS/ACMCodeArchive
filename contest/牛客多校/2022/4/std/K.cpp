#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define ULL unsigned long long
#define inf 1e18
#define MOD 1000000007

const int N=1000005;
int num[N];
//LL trueval[N];

LL p10[8];
void solve(int t) {
	int n;
	p10[0]=1;
	for(int i=1;i<8;i++){
		p10[i]=p10[i-1]*10;
	}
	scanf("%d",&n);
	if(n==1){
		printf("0");
		return;
	}
	for(int i=1;i<=n;i++){
		LL l=i-1;
		for(int j=1;j<8;j++){
			LL tmp=l*p10[j];
			LL k=((i-tmp)%n+n)%n;
			if(k<p10[j]){
				num[i]=j;
//				trueval[i]=k;
				break;
			}
		}
	}
	LL ans=0;
	for(int i=1;i<=n;i++){
		ans+=num[i];
	}
	printf("%lld",ans);
//	printf("\n");
//	for(int i=1;i<=n;i++){
//		printf("%d:%lld(%d)\n",i,trueval[i],num[i]);
//	}
	
}


int main() {
	int t=1;
//	scanf("%d",&t);
	while(t--) {
		solve(t+1);
	}
	return 0;
} 


