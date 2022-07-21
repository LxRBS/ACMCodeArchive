#include<bits/stdc++.h>
using namespace std;
#define M 200
const int mo=1000'000'007;
int Inv[M];
void init(){
	int i;
	Inv[1]=1;
	for (i=2;i<M;i++){
		Inv[i]=1LL*(mo-mo/i)*Inv[mo%i]%mo;
	}
}
int cnt[40];
int tr(char x,char y){
	int r=x-'1';
	if (y=='p'){
		r+=9;
	}else if (y=='s'){
		r+=18;
	}else if (y=='z'){
		r+=27;
	}
	return r;
}
long long dp[20][200];
long long dfs(int a,int b){
	if (a<=0 || a*3>b){
		return 0;
	}
	if (dp[a][b]!=-1){
		return dp[a][b];
	}
	return dp[a][b]=((dfs(a,b-1)*(b-a*3)+dfs(a-2,b-1)*a*3)%mo*Inv[b]+1)%mo;
}
char s[30];
int main(){
	init();
	int Case,Tt,i;
	scanf("%d",&Case);
	memset(dp,-1,sizeof(dp));
	for (Tt=1;Tt<=Case;Tt++){
		scanf("%s",s);
		memset(cnt,0,sizeof(cnt));
		for (i=0;i<26;i+=2){
			int x=tr(s[i],s[i+1]);
			cnt[x]++;
		}
		int cnt1=0;
		for (i=0;i<40;i++){
			if (cnt[i]==1){
				cnt1++;
			}
		}
		printf("Case #%d: %lld\n",Tt,dfs(cnt1,4*34-13));
	}
	return 0;
}
