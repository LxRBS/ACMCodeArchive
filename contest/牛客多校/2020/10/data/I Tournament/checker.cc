#include <bits/stdc++.h>
using namespace std;

const int N=444;
int g[N][N];
int dx[]={1,0,-1,0},dy[]={0,1,0,-1};
int n;

int main(int argc, char **argv)
{
	ifstream input("input");
    ifstream output("output");
    ifstream pout("user_output");
    int T;
    input>>T;
    for (int i=0;i<T;i++) {
    	input>>n;
    	for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) g[i][j]=0;
		for (int i=1;i<=n*(n-1)/2;i++) {
			int u,v;
			pout>>u>>v;
			if (u==v) return 1;
			if (u>n||u<1||v>n||v<1) return 1;
			if (g[u][v]) return 1;
			g[u][v]=g[v][u]=i;
			g[u][u]=g[v][v]=i;
		}
		int s=0;
		for (int i=1;i<=n;i++) {
			s+=*max_element(g[i]+1,g[i]+n+1)-*min_element(g[i]+1,g[i]+n+1)+1;
		}
		int fs=0;
		int k=(n+1)/2;
		if (n%2==0) fs=k*(4*k*k+k-1)/2; else fs=k*(k-1)*(4*k-1)/2;
		if (s!=fs) return 1;
	}
	return 0;
}