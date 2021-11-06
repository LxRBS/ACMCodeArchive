#include <bits/stdc++.h>
using namespace std;

vector<vector<pair<uint64_t,int>>> e,r;
typedef pair<uint64_t,int> E;

int main(){
  uint64_t stime,etime; cin>>stime>>etime;
  int n,m; cin>>n>>m;
  e.resize(n);
  r.resize(n);
  while (m--){
    int a,b; uint64_t c; cin>>a>>b>>c; --a,--b;
    e[a].emplace_back(c,b);
    r[b].emplace_back(c,a);
  }

  priority_queue<E,vector<E>,greater<E>> djk;

  vector<uint64_t> potential(n,-(1<<29));
  djk.emplace(potential[n-1]=0,n-1);
  while (not djk.empty()){
    int x=djk.top().second,c=djk.top().first; djk.pop();
    if (c!=potential[x]) continue;
    for (auto y: r[x]){
      if (potential[x]+y.first<potential[y.second]){
        djk.emplace(potential[y.second]=potential[x]+y.first,y.second);
      }
    }
  }
  assert(~potential[0]);

  uint64_t res=~0llu;

  map<pair<uint64_t,int>,uint64_t> best; // best[{time,node}] = (smallest risk)
  for (uint64_t t=0; t<=etime; t++){
    best[{t,0}]=(t>=stime? (t-stime)+potential[0]: 0llu);
  }
  while (!best.empty()) {
    auto best_it = best.begin();
    auto t=best_it->first.first;
    auto x=best_it->first.second;
    auto risk=best_it->second;
    best.erase(best.begin());
    // cerr<<" risk t="<<t<<" x="<<x+1<<": "<<risk<<endl;

    if (t>=etime){
      if (risk<res){
        // cerr<<"    update answer -> "<<risk<<endl;
        res=risk;
      }
      continue;
    }

    for (auto i: e[x]){
      auto nrisk=risk;

      if (stime<=t){
        // Started from x on or after stime
        nrisk=max(nrisk,i.first+potential[i.second]);
      }else{
        // Started from x before stime
        if (etime<=t+i.first){
          // Arrived at i.second on or after etime
          nrisk=max(nrisk,i.first-(stime-t)+potential[i.second]);
        }else if (stime<=t+i.first){
          // Arrived at i.second before etime but after stime.
          nrisk=max(nrisk,i.first-(stime-t)+potential[i.second]);
        }
      }
      auto it=best.find({t+i.first,i.second});
      uint64_t prev_risk=(it==best.end()? ~0llu: it->second);
      best[{t+i.first,i.second}]=min(prev_risk,nrisk);
    }
  }

  res=min(res,potential[0]);
  cout<<res<<endl;
}
