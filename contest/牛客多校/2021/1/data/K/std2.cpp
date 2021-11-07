#include<bits/stdc++.h>
#define rep(i,n) for(int i=0;i<n;++i)
#define mp make_pair
#define pb push_back
#define st first
#define nd second
#define x0 fuckcjb
#define y0 fuckyzc
#define x1 fucksf
#define y1 fuckjsb
using namespace std;
using ll=long long;
using ld=double;
const int N=1000+5;
int T,n;
int a[N];
ld sqt[N];
ld cal(int x,int y){return sqt[abs(x-y)];}
void check(){
    rep(i,n)for(int j=i+1;j<n;++j)
        if(cal(i,a[i])+cal(j,a[j])>cal(i,a[j])+cal(j,a[i])){
            swap(a[i],a[j]);
        }
}
bool in[N];
int q[N],top;
int main(){
    rep(i,N)sqt[i]=sqrt(i);
    for(scanf("%d",&T);T--;){
        scanf("%d",&n);
        rep(i,n)scanf("%d",a+i);
        sort(a,a+n);
        rep(i,15)check();
        rep(i,n)printf("%d%c",a[i]," \n"[i+1==n]);
    }
}