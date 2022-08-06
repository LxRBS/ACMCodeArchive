#include<bits/stdc++.h>

using namespace std;

#define gc c=getchar()
#define r(x) read(x)
#define ll long long

template<typename T>
inline void read(T &x){
    x=0;T k=1;char gc;
    while(!isdigit(c)){if(c=='-')k=-1;gc;}
    while(isdigit(c)){x=x*10+c-'0';gc;}x*=k;
}

const int N=1e6+7;

ll f(ll a,ll b,ll c,ll n){
	if(!a)return b/c*(n+1);
	if(a>=c||b>=c)return f(a%c,b%c,c,n)+(a/c)*n*(n+1)/2+(b/c)*(n+1);
	ll m=(a*n+b)/c;
	return n*m-f(c,c-b-1,a,m-1);
}

inline int baoli(int x1,int y1,int x2,int y2){
    int t=x1+y1;
    int ans=0;
    for(int i=x1;i<=x2;++i){
        for(int j=y2;j<=y1;++j){
            if(i+j>=t)break;
            int d=t-(i+j);
            ans+=(i>=d&&j>=d);
        }
    }
    return ans;
}

inline ll calc(int x1,int y1,int x2,int y2){
    int t=x1+y1;
    int x=x1,y=y2;
    if(x+2*y>=t&&2*x+y>=t){
        return 2*f(1,0,1,x2-x1);
    }
    if(x+2*y>=t){
        int h=t-2*x-y;
        return 2*f(1,0,1,x2-x1)-(f(1,0,2,h)-h/2+h);
    }
    if(2*x+y>=t){
        int h=t-2*y-x;
        return 2*f(1,0,1,x2-x1)-(f(1,0,2,h)-h/2+h);
    }
    if(3*x<=t&&3*y>=t){
        int h=t-2*x-y;
        return 2*f(1,0,1,x2-x1)-(f(1,0,2,h)-h/2+h);
    }
    if(3*x>=t&&3*y<=t){
        int h=t-2*y-x;
        return 2*f(1,0,1,x2-x1)-(f(1,0,2,h)-h/2+h);
    }
    int h1=t-2*y-x;
    ll ans=2*f(1,0,1,x2-x1)-(f(1,0,2,h1)-h1/2+h1);
    int h2=t-2*x-((t-1)/3+1);
    ans-=f(1,0,2,h2)-h2/2+h2;
    if((t-x)&1){
        ans+=f(2,0,1,(t-x+1)/2-((t-1)/3+1))-((t-x+1)/2-((t-1)/3+1));
    }
    else {
        ans+=f(2,0,1,(t-x)/2-((t-1)/3+1));
    }
    return ans;
}

struct Data{
    int x1,x2;
};

inline bool operator<(const Data& a, const Data& b){
    return a.x1<b.x1;
}

set<Data>S[N*2];

int main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // int n,m,q;r(n),r(m),r(q);
    int q;r(q);
    // srand(time(NULL));
    ll ans=0;
    while(q--){
        int opt,x1,y1,x2,y2;
        // int t=rand()%50;
        // x1=rand()%(t+1);
        // x2=rand()%(t+1);
        // y1=t-x1;
        // y2=t-x2;
        r(opt),r(x1),r(y1),r(x2),r(y2);
        assert(x1+y1==x2+y2);
        assert(x1!=x2);
        if(x1>x2){
            swap(x1,x2);
            swap(y1,y2);
        }
        // printf("%d %d %d %d\n",x1,y1,x2,y2);
        // printf("%lld %lld\n",calc(x1,y1,x2,y2),baoli(x1,y1,x2,y2));
        // if(calc(x1,y1,x2,y2)!=baoli(x1,y1,x2,y2)){
        //     return 0;
        // }
        int t=x1+y1;
        if(opt==1){
            if(!S[t].size()){
                S[t].insert({-1,-1});
                S[t].insert({t+1,t+1});
            }
            auto it=S[t].lower_bound({x1,x2});
            Data nxt=*it;
            Data pre=*--it;
            if(pre.x2!=-1&&pre.x2==x1){
                S[t].erase(pre);
                ans-=calc(pre.x1,t-pre.x1,pre.x2,t-pre.x2);
                x1=pre.x1;
            }
            if(nxt.x1!=t+1&&nxt.x1==x2){
                S[t].erase(nxt);
                ans-=calc(nxt.x1,t-nxt.x1,nxt.x2,t-nxt.x2);
                x2=nxt.x2;
            }
            S[t].insert({x1,x2});
            ans+=calc(x1,t-x1,x2,t-x2);
        }
        else{
            auto it=S[t].upper_bound({x1,x2});
            Data tmp=*--it;
            assert(tmp.x1<=x1);
            assert(tmp.x2>=x2);
            S[t].erase(tmp);
            ans-=calc(tmp.x1,t-tmp.x1,tmp.x2,t-tmp.x2);
            if(tmp.x1!=x1){
                S[t].insert({tmp.x1,x1});
                ans+=calc(tmp.x1,t-tmp.x1,x1,t-x1);
            }
            if(tmp.x2!=x2){
                S[t].insert({x2,tmp.x2});
                ans+=calc(x2,t-x2,tmp.x2,t-tmp.x2);
            }
        }
        printf("%lld\n",ans);
    }
    return 0;
}