#include<bits/stdc++.h>
#define pb push_back
using namespace std;
typedef double db;
const db inf=1e9;
const db eps=1e-6;
typedef vector<db> vd;
db a[10][10],dp[256][256],w[10][10];
int N;
vd simplex(vector<vd> A,vd b,vd c){
    int n=A.size(),m=A[0].size()+1,r=n,s=m-1;
    vector<vd> D(n+2,vd(m+1,0));
    vector<int> ix(n+m);
    for (int i=0;i<n+m;i++) ix[i]=i;
    for (int i=0;i<n;i++){
        for (int j=0;j<m-1;j++) D[i][j]-=A[i][j];
        D[i][m-1]=1; D[i][m]=b[i];
        if (D[r][m]>D[i][m]) r=i;
    }
    for (int j=0;j<m-1;j++) D[n][j]=c[j];
    D[n+1][m-1]=-1;
    double d;
    int cc=0;
    while (1){
        if (r<n){
            swap(ix[s],ix[r+m]);
            D[r][s]=1.0/D[r][s]; 
            vector<int> sp;
            for (int j=0;j<=m;j++) if (j!=s){
                D[r][j]*=-D[r][s];
                if (D[r][j]) sp.pb(j);
            }
            for (int i=0;i<=n+1;i++) if (i!=r){
                for (int j=0;j<sp.size();j++){
                    D[i][sp[j]]+=D[r][sp[j]]*D[i][s];
                }
                D[i][s]*=D[r][s];
            }
        }
        r=-1; s=-1;
        for (int j=0;j<m;j++) if (s<0||ix[s]>ix[j]){
            if (D[n+1][j]>eps||(D[n+1][j]>=-eps&&D[n][j]>eps)) s=j;
        }
        if (s<0) break;
        for (int i=0;i<n;i++) if (D[i][s]<-eps){
            if (r<0) {r=i;continue;}
            d=D[r][m]/D[r][s]-D[i][m]/D[i][s];
            if (d<-eps||(d<eps&&ix[r+m]>ix[i+m])) r=i;
        }
        if (r<0) return vd();
    }
    if (D[n+1][m]<-eps) return vd();
    vd x(m-1);
    for (int i=m;i<n+m;i++)
        if (ix[i]<m-1) x[ix[i]]=D[i-m][m];
    return x;
}
db work(vector<vd> a){
    int n=a.size(),m=a[0].size();
    vector<vd> A(m+1,vd(n+1,0));
    vd b(m+1,0),c(n+1,0);
    for (int i=0;i<m;i++){
        for (int j=0;j<n;j++) A[i][j]=-a[j][i];
        A[i][n]=1;
    }
    for (int i=0;i<n;i++) A[m][i]=1;
    b[m]=1; c[n]=1;
    vd sv=simplex(A,b,c);
    return sv[n];
}
bool vis[256][256];
db dfs(int p,int q){
    if (!p) return 1;
    if (!q) return 0;
    if (vis[p][q]) return dp[p][q];
    vector<int> decksA(0),decksB(0);
    for (int i=0;i<N;i++){
        if ((p>>i)&1) decksA.pb(i);
        if ((q>>i)&1) decksB.pb(i);
    }
    int n=decksA.size(),m=decksB.size();
    vector<vd> a(n,vd(m,0));
    for (int i=0;i<n;i++)
    for (int j=0;j<m;j++){
        int s=decksA[i],t=decksB[j];
        a[i][j]=w[s][t]*dfs(p-(1<<s),q)+(1.0-w[s][t])*dfs(p,q-(1<<t));
    }
    vis[p][q]=1;
    return dp[p][q]=work(a);
}
void solve(){
    cin >> N;
    for (int i=0;i<N;i++)
        for (int j=0;j<N;j++)
            cin >> w[i][j];
    memset(vis,0,sizeof(vis));
    printf("%.10f\n",dfs((1<<N)-1,(1<<N)-1));
}
int main(){
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int _; cin >> _;
    while (_--) solve();
}