#include "testlib.h"
#include <vector>
#include <algorithm>
#define N 1005
using namespace std;
typedef double ll;
const ll INF=1e60,NPOS=-1;
int data[N];
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

int main(int argc, char** argv) {
	registerTestlibCmd(argc, argv);
	int T = inf.readInt();
	ll ratio = 0.0;
	for (int cas = 1; cas <= T; ++cas) {
		int n = inf.readInt();
		int f[n];
		for (int i = 0; i < n; i++) f[i] = 0;
		for (int i = 0; i < n; i++)
			f[inf.readInt()]++;
		ll now = 0;
		int data[n];
		for (int i = 0; i < n; i++){
      		data[i] = ouf.readInt(0, n-1);
      		if ((--f[data[i]])<0)
      			quitf(_wa, "The %d-th number %d is incorrect.", i+1, data[i]);
      		now += sqrt(abs(data[i] - i));
      	}
      	ll ans = do_km(n, data);
      	ratio += (now - ans) / ans;
      	//if (ratio > 0.04 * T) break;
    }
    if (ratio > 0.04 * T)
		quitf(_wa, "The average ratio is %.2f%%, which exceeds 4%%.", ratio / T * 100);
	quitf(_ok, "The average ratio is %.2f%%.", ratio / T * 100);
	return 0;
}
