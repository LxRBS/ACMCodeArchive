#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,m;
ll a[100005];
ll b[100005];

int main(){
    cin>>n>>m;
    ll i;
    for (i=0;i<n;i++) cin>>a[i];
    ll l=0,r=n;
    while(l<=r){
        ll mid=(l+r)/2;
        int flag=1;
        for(ll i=0;i<n;i++){
            b[i]=a[i]+(i+1)*mid;
        }
        sort(b,b+n);
        ll t=m;
        for(i=0;i<mid;i++){
            t-=b[i];
            if(t<0) flag=0;
        }
        if(flag){
            l=mid+1;
        }
        else{
            r=mid-1; 
        }
    }
    cout<<r<<endl;
    return 0;
}
