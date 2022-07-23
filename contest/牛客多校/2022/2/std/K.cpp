#include <cstdio>
#include <cstring>
#define MN 200

const int mod = 1000000007;

int n,m;
char s[MN+5]; 

int f[MN+5][MN+5][MN+5];

void add(int& a,int b){
	a = (a+b)%mod;
}

void solve(){
	scanf("%d%d%s",&n,&m,&s[1]);
	memset(f,0,sizeof(f[0])*(m+1));
	f[0][0][0] = 1;
	for(int i=0;i<m;i++){
		for(int j=0;j<=i;j++){
			for(int k=0;k<=i;k++){
				if(j>0){
					if(s[k+1]==')'){
						add(f[i+1][j-1][k+1],f[i][j][k]);
					}else{
						add(f[i+1][j-1][k],f[i][j][k]);
					}
				}
				{
					if(s[k+1]=='('){
						add(f[i+1][j+1][k+1],f[i][j][k]);
					}else{
						add(f[i+1][j+1][k],f[i][j][k]);
					}
				}
			}
		}
	}
	printf("%d\n",f[m][0][n]);
}

int main(){
	int T;
	scanf("%d",&T);
	while(T--) solve();
}
