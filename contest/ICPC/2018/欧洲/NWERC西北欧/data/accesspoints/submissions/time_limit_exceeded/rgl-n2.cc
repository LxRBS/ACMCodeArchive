#include <bits/stdc++.h>
using namespace std;
typedef long double ld;

// Place the computers from right to left.
//  - start at position 0
//  - move right until we hit something
//    - if that something's the destination, stop
//    - if that something's another computer:
//      - we'll need to move that computer as well
//      - check whether it's worth it
//        - if so, continue
//        - otherwise, stop there.

ld solve(vector<int> x){
  int const n=x.size();

  vector<ld> s(n+1);
  for (int i=0; i<n; i++)
    s[i+1]=s[i]+x[i];

  vector<ld> cx(n+1,1e60L);
  for (int i=n; i--;){
    cx[i]=min(cx[i+1],(ld)x[i]);

    for (int j=i+1; j<=n; j++)
      if (j<n and cx[j]==cx[j+1])
        continue;
      else if (x[i]>=cx[j] and (s[j+1]-s[i])/(1+j-i)>=cx[j])
        cx[i]=min(cx[j+1], (s[j+1]-s[i])/(j+1-i));
      else
        break;

    for (int j=i+1; j<n; j++)
      cx[j]=max(cx[j],cx[i]);
  }

  ld res=0.L;
  for (int i=n; i--;) res+=powl(x[i]-cx[i],2);
  return res;
}

int main(){
  int n; cin>>n;
  vector<int> x(n),y(n);
  for (int i=0; i<n; i++) cin>>x[i]>>y[i];
  cout.precision(6);
  cout<<fixed<<solve(x)+solve(y)<<endl;
}
