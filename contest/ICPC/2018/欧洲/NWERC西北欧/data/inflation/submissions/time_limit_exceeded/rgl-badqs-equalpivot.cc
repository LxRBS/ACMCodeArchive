#include <bits/stdc++.h>
using namespace std;

// Correctly randomises the pivot but doesn't filter out repetitions
// of the same value when partitioning, so big arrays of identical
// values kill it.

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
  if (beg<l and *l==pivot) --l;
  if (r<end and *r==pivot) ++r;

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
