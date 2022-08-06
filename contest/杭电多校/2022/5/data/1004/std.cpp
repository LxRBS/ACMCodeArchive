#include<bits/stdc++.h>
#define rep(i,s,t) for(int i=s;i<=t;++i)
#define per(i,s,t) for(int i=s;i>=t;--i)
#define ll long long
#define db double 
#define sz(a) (int)a.size()
#define fi first
#define se second
#define pb push_back
#define vi vector<int>
#define mp make_pair
using namespace std;
#define int long long
int n,m;
struct point{
    int x,y;
    point(int X=0,int Y=0){
        x=X,y=Y;
    }
    void in(){
        cin>>x>>y;
    }
    void out(){
        cout<<x<<" "<<y<<" ";
    }
    point operator-(point A)const{
        return point(x-A.x,y-A.y);
    }
    ll operator*(point A)const{
        return 1ll*x*A.y-1ll*y*A.x; 
    }
    bool operator==(point A)const{
        return x==A.x&&y==A.y;
    }
}p[21],q[111][5];
__int128 a[21][5];
__int128 b[5],u=1;
int t[21],t0;
int sgn(ll x){
    if(x==0)return 0;
    if(x>0)return 1;
    if(x<0)return -1; 
}
bool cross(point A,point B,point C,point D){
    /*if(A==C||B==D||A==D||B==C){
        A.out(),B.out(),C.out(),D.out();
        cout<<endl;
        return 0;
    }*/
    //A.out(),B.out(),C.out(),D.out();cout<<endl;
    //cout<<(A-B)*(C-B)<<endl;
    //cout<<(A-B)*(D-B)<<endl;
    return sgn((A-B)*(C-B))*sgn((A-B)*(D-B))<=0;
}
bool check(point A,point B){
    //A.out(),B.out();cout<<endl;
    rep(i,0,m-1)
        rep(j,0,3){
            if(B==q[i][j]||B==q[i][(j+1)%4])continue;
            if(cross(A,B,q[i][j],q[i][(j+1)%4])
            &&cross(q[i][j],q[i][(j+1)%4],A,B)){
                return 0;
            }
        }
    //puts("233"); 
    return 1;
}
int popcnt(int x){
    int ans=0;
    rep(i,0,n-1)
        if(x>>i&1)
            ++ans;
    //cout<<"x="<<x<<endl;
    return ans;
}

inline void work(){
    cin>>n>>m;
    rep(i,0,n-1){
        p[i].in();
        rep(j,0,3)a[i][j]=0;
        t[i]=0;
    }
    rep(i,0,m-1)
        rep(j,0,3){
            q[i][j].in();
        }
    rep(i,0,n-1)
        rep(j,0,m-1)
            rep(k,0,3)
                if(check(p[i],q[j][k]))
                    a[i][k]|=(u<<j);
    rep(i,0,n-1)
        rep(j,0,n-1)
            if(i!=j&&check(p[i],p[j]))
                t[i]|=1<<j;
    int ans=1e9; 
    rep(s,0,(1<<n)-1){
        b[0]=b[1]=b[2]=b[3]=t0=0;
        rep(i,0,n-1)
            if(s>>i&1){
                b[0]|=a[i][0];
                b[1]|=a[i][1];
                b[2]|=a[i][2];
                b[3]|=a[i][3];
                t0|=t[i];
            }
        if(b[0]==(u<<m)-1
        &&b[1]==(u<<m)-1
        &&b[2]==(u<<m)-1
        &&b[3]==(u<<m)-1
        &&(t0&s)==s)
            ans=min(ans,popcnt(s));
    }
    if(ans==1e9)puts("No Solution!");
    else{
        printf("%lld\n",ans);
    }
}

main(){
    int T;
    scanf("%lld",&T);
    while(T--)
    work();
    
    return 0;
}
/*
1 1
-698133 978470
-391204 -17983 -406644 -17983 -406644 -50635 -391204 -50635
 
*/
