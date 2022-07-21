#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define pa pair<int,int>
const int N=510;
LL read()
{
	LL x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=x*10ll+ch-'0',ch=getchar();
	return x*f;
}
struct Tree
{
	int n,c[N],fa[N];
	vector<int>G[N];
	void link(int x,int y)
	{
		G[x].emplace_back(y);
		G[y].emplace_back(x);
	}
	void dfs(int x,int f)
	{
		fa[x]=f;
		for(int y:G[x])
		{
			if(y==f)continue;
			dfs(y,x);
		}
	}
}T1,T2;
 
struct hungarian {  // km
  int n;
  vector<int> matchx;  // ×ó¼¯ºÏ¶ÔÓ¦µÄÆ¥Åäµã
  vector<int> matchy;  // ÓÒ¼¯ºÏ¶ÔÓ¦µÄÆ¥Åäµã
  vector<int> pre;     // Á¬½ÓÓÒ¼¯ºÏµÄ×óµã
  vector<bool> visx;   // °Ý·ÃÊý×é ×ó
  vector<bool> visy;   // °Ý·ÃÊý×é ÓÒ
  vector<int> lx;
  vector<int> ly;
  vector<vector<int> > g;
  vector<int> slack;
  int inf;
  int res;
  queue<int> q;
  int org_n;
  int org_m;
 
  hungarian(int _n, int _m) {
    org_n = _n;
    org_m = _m;
    n = max(_n, _m);
    inf = numeric_limits<int>::max();
    res = 0;
    g = vector<vector<int> >(n, vector<int>(n));
    matchx = vector<int>(n, -1);
    matchy = vector<int>(n, -1);
    pre = vector<int>(n);
    visx = vector<bool>(n);
    visy = vector<bool>(n);
    lx = vector<int>(n, -inf);
    ly = vector<int>(n);
    slack = vector<int>(n);
  }
 
  void addEdge(int u, int v, int w) {
    g[u][v] = max(w, 0);  // ¸ºÖµ»¹²»Èç²»Æ¥Åä Òò´ËÉèÎª0²»Ó°Ïì
  }
 
  bool check(int v) {
    visy[v] = true;
    if (matchy[v] != -1) {
      q.push(matchy[v]);
      visx[matchy[v]] = true;  // in S
      return false;
    }
    // ÕÒµ½ÐÂµÄÎ´Æ¥Åäµã ¸üÐÂÆ¥Åäµã pre Êý×é¼ÇÂ¼×Å"·ÇÆ¥Åä±ß"ÉÏÓëÖ®ÏàÁ¬µÄµã
    while (v != -1) {
      matchy[v] = pre[v];
      swap(v, matchx[pre[v]]);
    }
    return true;
  }
 
  void bfs(int i) {
    while (!q.empty()) {
      q.pop();
    }
    q.push(i);
    visx[i] = true;
    while (true) {
      while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v = 0; v < n; v++) {
          if (!visy[v]) {
            int delta = lx[u] + ly[v] - g[u][v];
            if (slack[v] >= delta) {
              pre[v] = u;
              if (delta) {
                slack[v] = delta;
              } else if (check(v)) {  // delta=0 ´ú±íÓÐ»ú»á¼ÓÈëÏàµÈ×ÓÍ¼ ÕÒÔö¹ãÂ·
                                      // ÕÒµ½¾Íreturn ÖØ½¨½»´íÊ÷
                return;
              }
            }
          }
        }
      }
      // Ã»ÓÐÔö¹ãÂ· ÐÞ¸Ä¶¥±ê
      int a = inf;
      for (int j = 0; j < n; j++) {
        if (!visy[j]) {
          a = min(a, slack[j]);
        }
      }
      for (int j = 0; j < n; j++) {
        if (visx[j]) {  // S
          lx[j] -= a;
        }
        if (visy[j]) {  // T
          ly[j] += a;
        } else {  // T'
          slack[j] -= a;
        }
      }
      for (int j = 0; j < n; j++) {
        if (!visy[j] && slack[j] == 0 && check(j)) {
          return;
        }
      }
    }
  }
 
  int get() {
    // ³õÊ¼¶¥±ê
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        lx[i] = max(lx[i], g[i][j]);
      }
    }
 
    for (int i = 0; i < org_n; i++) {
      fill(slack.begin(), slack.end(), inf);
      fill(visx.begin(), visx.end(), false);
      fill(visy.begin(), visy.end(), false);
      bfs(i);
    }
 
    // custom
    for (int i = 0; i < org_n; i++) {
      if (g[i][matchx[i]] > 0) {
        res += g[i][matchx[i]];
      } else {
        matchx[i] = -1;
      }
    }
    
//    cout<< org_n << " " << org_m << "\n";
//    cout << res << "\n";
//    for (int i = 0; i < n; i++) {
//      cout << matchx[i] + 1 << " ";
//    }
//    cout << "\n";
	return res;
  }
};
bool vis[N][N];
int f[N][N][2];
void dp(int x,int y)
{
	if(vis[x][y])return;
	vis[x][y]=true;
	if(T1.c[x]==T2.c[y])
	{
		vector<int>v1,v2;
		for(int p:T1.G[x])
		{
			if(p==T1.fa[x])continue;
			v1.emplace_back(p);
		}
		for(int p:T2.G[y])
		{
			if(p==T2.fa[y])continue;
			v2.emplace_back(p);
		}
		
		for(int i=0;i<v1.size();i++)
		for(int j=0;j<v2.size();j++)
		dp(v1[i],v2[j]);
		
		if(v1.size()<=v2.size())
		{
			hungarian KM(v1.size(),v2.size());
			for(int i=0;i<v1.size();i++)
			for(int j=0;j<v2.size();j++)
			KM.addEdge(i,j,f[v1[i]][v2[j]][0]);
			f[x][y][0]=f[x][y][1]=1+KM.get();
		}
		else
		{
			hungarian KM(v2.size(),v1.size());
			for(int j=0;j<v2.size();j++)
			for(int i=0;i<v1.size();i++)
			KM.addEdge(j,i,f[v1[i]][v2[j]][0]);
			f[x][y][0]=f[x][y][1]=1+KM.get();
		}
		
	}
	for(int p:T2.G[y])
	{
		if(p==T2.fa[y])continue;
		dp(x,p);
		f[x][y][0]=max(f[x][y][0],f[x][p][0]);
	}
	for(int p:T1.G[x])
	{
		if(p==T1.fa[x])continue;
		dp(p,y);
		f[x][y][0]=max(f[x][y][0],f[p][y][0]);
	}
}
int main()
{
	T1.n=read(),T2.n=read();
	for(int i=1;i<=T1.n;i++)T1.c[i]=read();
	for(int i=1;i<=T2.n;i++)T2.c[i]=read();
	for(int i=1;i<T1.n;i++)T1.link(read(),read());
	for(int i=1;i<T2.n;i++)T2.link(read(),read());
	T1.dfs(1,0),T2.dfs(1,0);
	dp(1,1);
	printf("%d\n",f[1][1][0]);
 	return 0;
}
