#include<bits/stdc++.h>
using namespace std;

int n,m,K,sx,sy,tx,ty;
struct edge{
	int x[2],y[2]; 
}e[20];

int mp[20][20];

int Lw[20][20],Dw[20][20];

bool dfs(int x,int y){
	mp[x][y]=1;
	if(x==tx && y==ty){
		return 1;
	}
	bool re=0;
	//x-1 y
	if(x>=1 && Lw[x][y]==0 && mp[x-1][y]==0){
		re|=dfs(x-1,y);
	}
	//x+1 y
	if(x+1<n && Lw[x+1][y]==0 && mp[x+1][y]==0){
		re|=dfs(x+1,y);
	}
	//x y-1
	if(y>=1 && Dw[x][y]==0 && mp[x][y-1]==0){
		re|=dfs(x,y-1);
	}
	//x y+1
	if(y+1<m && Dw[x][y+1]==0 && mp[x][y+1]==0){
		re|=dfs(x,y+1);
	}
	return re;
}

bool check(int s){
	memset(mp,0,sizeof(mp));
	memset(Lw,0,sizeof(Lw));
	memset(Dw,0,sizeof(Dw));
	for(int i=0;i<K;++i){
		if((s&(1<<i))==0){
			if(e[i].x[0]==e[i].x[1]){
				for(int j=e[i].y[0];j<e[i].y[1];++j){
					Lw[e[i].x[0]][j]=1;
				}
			}
			else{
				for(int j=e[i].x[0];j<e[i].x[1];++j){
					Dw[j][e[i].y[0]]=1;
				}
			}
		}
	}
	return dfs(sx,sy);
}

int popcount(int x){
	int re=0;
	while(x){
		if(x&1) ++re;
		x>>=1;
	}
	return re;
}

int f[(1<<15)+5];

void solve(){
	cin>>n>>m>>K>>sx>>sy>>tx>>ty;
	for(int i=0;i<K;++i){
		cin>>e[i].x[0]>>e[i].y[0]>>e[i].x[1]>>e[i].y[1];
		if(e[i].x[0]==e[i].x[1]&&e[i].y[0]>e[i].y[1]){
			swap(e[i].y[0],e[i].y[1]);
		}
		if(e[i].y[0]==e[i].y[1]&&e[i].x[0]>e[i].x[1]){
			swap(e[i].x[0],e[i].x[1]);
		}
	}
	int ans=K;
	for(int s=0;s<(1<<K);++s){
		f[s]=0;
	}
	for(int s=0;s<(1<<K);++s){
		if(f[s]){
			continue;
		}
		f[s]=check(s);
		if(f[s]){
			ans=min(ans,popcount(s));
			for(int j=0;j<K;++j){
				f[s|(1<<j)]|=f[s];
			}
		}
	}
	cout<<ans<<endl;
	return;
}

int main(){
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	int t=1;cin>>t;
	for(int i=1;i<=t;++i){
		solve();
	}
	return 0;
} 
