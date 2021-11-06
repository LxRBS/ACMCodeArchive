#include <bits/stdc++.h>
using namespace std;

// Use-case: team knows how to implement quicksort but don't know the
// standard library well enough to know they can use sorted(), sort(),
// Collections.sort(), eval("mylist.sort()") to get it done for them.

template <class T>
void quicksort(T beg,T end){
  if (beg==end or beg+1==end) return;
  auto const pivot=beg[rand()%(end-beg)];

  auto l=beg,r=end-1;
  for (;;){
    while (l<=r and     (*l<pivot)) ++l;
    while (l<=r and not (*r<pivot)) --r;
    if (r<l) {swap(l,r); break;}
    swap(*l,*r);
  }
  for (auto i=beg; i<l; i++) if (*i==pivot) swap(*(l--),*i);
  for (auto i=end; i-->r;)   if (*i==pivot) swap(*(r++),*i);

  quicksort(beg,l+1);
  quicksort(r,end);
}

int main(){
  ios::sync_with_stdio(false);
  int n; cin>>n;
  vector<int> v(n); for (auto &i: v) cin>>i;
  quicksort(v.begin(),v.end());
  long double res=1.L;
  for (int i=n; i--;){
    if (v[i]>i+1){
      cout<<"impossible"<<endl;
      return 0;
    }else{
      res=min(res,v[i]/(i+1.L));
    }
  }

  cout.precision(16);
  cout<<res<<endl;
}
