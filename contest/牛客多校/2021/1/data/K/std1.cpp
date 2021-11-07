#include<bits/stdc++.h>
#define N 1005
using namespace std;
typedef double ll;
const ll INF=1e60,NPOS=-1;
int data[N], vis[N];
struct Matrix
{
    int n;
    ll a[N][N];
};
struct KuhnMunkres:Matrix
{
    ll hl[N],hr[N],slk[N];
    int fl[N],fr[N],vl[N],vr[N],pre[N],q[N],ql,qr;
    int check(int i)
    {
        if(vl[i]=1,fl[i]!=NPOS) return vr[q[qr++]=fl[i]]=1;
        while(i!=NPOS)swap(i,fr[fl[i]=pre[i]]);
        return 0;
    }
    void bfs(int s)
    {
        fill(slk,slk+n,INF),fill(vl,vl+n,0),fill(vr,vr+n,0);
        for(vr[q[ql=0]=s]=qr=1;;)
        {
            for(ll d; ql<qr;)
                for(int i=0,j=q[ql++]; i<n; ++i)
                    if(!vl[i]&&slk[i]>=(d=hl[i]+hr[j]-a[i][j]))
                        if(pre[i]=j,d)slk[i]=d;
                        else if(!check(i))return;
            ll d=INF;
            for(int i=0; i<n; ++i)
                if(!vl[i]&&d>slk[i])d=slk[i];
            for(int i=0; i<n; ++i)
            {
                if(vl[i])hl[i]+=d;
                else slk[i]-=d;
                if(vr[i])hr[i]-=d;
            }
            for(int i=0; i<n; ++i)
                if(!vl[i]&&!slk[i]&&!check(i))return;
        }
    }
    void ask()
    {
        fill(fl,fl+n,NPOS),fill(fr,fr+n,NPOS),fill(hr,hr+n,0);
        for(int i=0; i<n; ++i)hl[i]=*max_element(a[i],a[i]+n);
        for(int j=0; j<n; ++j)bfs(j);
    }
} km;
ll do_km(int n, int *data){
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			km.a[i][j] = -sqrt(abs(i - data[j]));
	km.n = n;
	km.ask();
	ll ans = 0;
	for (int i = 0; i < n; i++)
		ans+=km.a[i][km.fl[i]];
	return -ans;
}
ll greedy(int n){
	for (int i = 0; i < n; i++) vis[i] = -1;
	multiset<int>S;
	for (int i = 0; i < n; i++)
		S.insert(data[i]);
	ll now = 0;
	for (int d = 0; !S.empty() ; d++){
		for (int i = 0; i < n; i++)
			if (vis[i] == -1 && S.find(i - d) != S.end()){
				S.erase(S.find(i - d));
				now += sqrt(d);
				vis[i] = i - d;
			}
			else if (vis[i] == -1 && S.find(i + d) != S.end()){
				S.erase(S.find(i + d));
				now += sqrt(d);
				vis[i] = i + d;
			}
	}
	return now;
}

int main(){
	int T; scanf("%d", &T);
	while (T--){
		int n; scanf("%d",&n);
		for (int i = 0; i < n; i++) scanf("%d", &data[i]);
		if (n <= 100){
			double ans = do_km(n, data);
			for (int i = 0; i < n; i++)
				printf("%d%c", data[km.fl[i]], i == n-1 ? '\n' : ' ');
		}
		else{
			ll now = greedy(n);
			for (int i = 0; i < n; i++)
				printf("%d%c", vis[i], i == n-1 ? '\n' : ' ');
		}
	}
}
