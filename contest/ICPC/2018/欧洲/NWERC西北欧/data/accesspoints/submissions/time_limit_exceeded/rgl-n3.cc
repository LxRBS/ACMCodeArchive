#include <bits/stdc++.h>
using namespace std;
typedef double ld;

ld critical_x(ld const a,ld const b,ld const c){
  return a==0? 0: -b/(2*a);
}
ld critical_point(ld const a,ld const b,ld const c){
//  ld const x=critical_x(a,b,c);
//  return a*powl(x,2)+b*x+c;
  return c-powl(b,2)/4/a;
}

ld solve(vector<int> x){
  int const n=x.size();

  vector<ld> interesting;
  for (int i=0; i<n; i++){
    ld u=0,v=0,w=0;
    ld sum=0.L;
    for (int j=i; j>=0; j--){
      u+=1, v-=2*x[j], w+=powl(x[j],2);
      interesting.push_back(critical_x(u,v,w));
    }
  }
  sort(interesting.begin(),interesting.end());

  vector<ld> dp[2];
  dp[0].assign(interesting.size(),0);
  for (int i=0; i<n; i++){
    dp[(i+1)&1].assign(interesting.size()+1,1e60L);
    for (int j=0; j<interesting.size(); j++){
      dp[(i+1)&1][j  ]=min(dp[(i+1)&1][j  ],dp[(i  )&1][j  ]+(ld)powl(x[i]-interesting[j],2));
      dp[(i+1)&1][j+1]=min(dp[(i+1)&1][j+1],dp[(i+1)&1][j  ]);
    }
  }
  cerr<<"  answer = "<<fixed<<dp[n&1].back()<<endl;
  return dp[n&1].back();
}

int main(){
  cout.precision(6);
  cerr.precision(6);

  int n; cin>>n;
  vector<int> x(n),y(n);
  for (int i=0; i<n; i++){
    cin>>x[i]>>y[i];
  }
  cout<<fixed<<solve(x)+solve(y)<<endl;
}
