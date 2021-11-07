#include <bits/stdc++.h>
using namespace std;

const int N=444;
string s[N];
int p[N][N];
bool vis[N][N];
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
		int bn=0;
		for (int i=0;i<n;i++) {
			string s;
			pout>>s;
			if (s.size()!=n) return 1;

			for (int j=0;j<n;j++) {
				if (s[i]!='0'&&s[i]!='1') return 1;
				p[i][j]=(s[j]=='1'),bn+=p[i][j];
			}
		}
		for (int i=0;i<n;i++) for (int j=0;j<n-1;j++) {
			if (p[i][j]&&p[i][j+1]) return 1;
			if (p[j][i]&&p[j+1][i]) return 1;
		}
		for (int i=0;i<n;i++) for (int j=0;j<n;j++) vis[i][j]=0;

		queue<pair<int,int> > q;
		for (int i=0;i<n;i++) for (int j=0;j<n;j++) if (p[i][j]==0) {
			q.push(make_pair(i,j));
			vis[i][j]=1;
			goto find;
		}
		find:;
		while (!q.empty()) {
			auto f=q.front(); q.pop();
			for (int k=0;k<4;k++) {
				int nx=f.first+dx[k],ny=f.second+dy[k];
				if (nx>=0&&nx<n&&ny>=0&&ny<n&&p[nx][ny]==0&&!vis[nx][ny]) {
					vis[nx][ny]=1; q.push(make_pair(nx,ny));
				}
			}
		}
		for (int i=0;i<n;i++) for (int j=0;j<n;j++) if (p[i][j]==0&&!vis[i][j]) {
			return 1;
		}
		int an=0;
		if (n%3==0) an=n*n/3;
		else if (n%6==1||n%6==5) an=(n*n+2)/3;
		else an=(n*n-1)/3;
		if (n==3) an=4;
		if (bn!=an) return 1;
	}
	return 0;
}