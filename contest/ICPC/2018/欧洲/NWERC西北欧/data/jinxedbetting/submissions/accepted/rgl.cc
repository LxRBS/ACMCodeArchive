#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define llog2(x) ((unsigned) (8*sizeof (ll)-1-__builtin_clzll((ll)(x))))

void iterate_single(ll &a,ll &b,ll &av,ll &it){
  if (a==1){
    a+=b;
    b=0;
    ++it;
  }else{
    b+=(a+1)/2;
    a/=2;
    av-=1;
    ++it;
  }
}

void iterate_batch(ll &a,ll &b,ll &av,ll &it,ll const reps){
  if (not reps) return; else assert(not b);
  ll steps=llog2(a)+1;
  av-=(steps-1)*reps;
  it+=steps*reps;
}

void iterate_exactly(ll &a,ll &b,ll &av,ll &it,ll reps){
  if (not reps) return;

  for (; reps>0 and b>0; --reps) iterate_single(a,b,av,it);

  ll const period=llog2(a+b)+1;
  iterate_batch(a,b,av,it,reps/period);
  reps%=period;

  while (reps--){
    iterate_single(a,b,av,it);
  }
}

int main(){
  int n; cin>>n; ll jeff; cin>>jeff;
  vector<ll> v(n-1);
  for (int i=n-1; i--;) cin>>v[i], v[i]=jeff-v[i];
  sort(v.begin(),v.end());

  ll av=v[0];
  ll a=0,b=0;
  for (auto i: v) a+=(i==av), b+=(i==av+1);

  ll it=0;

  for (int ci=a+b; ci<=v.size(); ci++){
    ll lef=-1;
    for (ll rad=(1ll<<55ll); rad; rad>>=1ll){
      ll mid=lef+rad;

      ll a2=a,b2=b,av2=av,it2=it;
      iterate_exactly(a2,b2,av2,it2,mid);

      if (av2>=0 and (ci==v.size() or v[ci]-it2>av2+1)){
        lef=mid;
      }
    }
    iterate_exactly(a,b,av,it,lef+1);
    ++b;
  }
  cout<< (it - 1) <<endl;
}
