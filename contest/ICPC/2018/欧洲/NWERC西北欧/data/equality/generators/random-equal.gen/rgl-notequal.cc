#include <bits/stdc++.h>
using namespace std;

mt19937 rng;
vector<int> v,f;
vector<bool> s;

int fet(int x){
  int y=0; while (x>=0) y+=f[x], --(x&=x+1); return y;
}
int ffind(int y){
  int x=0;
  for (int i=(1<<20); i; i>>=1)
    if ((x+i)<=f.size() and f[x+i-1]<y)
      y-=f[x+i-1], x+=i;
  return x;
}

void gen(int beg,int end){
  int width=fet(end-1)-fet(beg-1);
  if (end-beg==1){
    if (bernoulli_distribution(0.1)(rng)){
      cout<<"shuffle(["<<v[beg]<<"])";
    }else{
      cout<<"["<<v[beg]<<"]";
    }
  }else if (width==1){
    assert(0<=beg and end<=v.size());
    vector<int> tmp(v.begin()+beg,v.begin()+end);
    shuffle(tmp.begin(),tmp.end(),rng);
    cout<<"shuffle([";
    for (int i=0; i<end-beg; i++) {cout<<tmp[i]; if (i+1!=end-beg) cout<<",";}
    cout<<"])";
  }else if (width==end-beg and bernoulli_distribution(0.2)(rng)){
    bool iss=is_sorted(v.begin()+beg,v.begin()+end);
    vector<int> tmp(v.begin()+beg,v.begin()+end);
    if (iss) shuffle(tmp.begin(),tmp.end(),rng);
    if (iss) cout<<"sorted(";
    cout<<"[";
    for (int i=0; i<end-beg; i++) {cout<<tmp[i]; if (i+1!=end-beg) cout<<",";}
    cout<<"]";
    if (iss) cout<<")";
  }else{
    if (width<2) cerr<<"width is "<<width<<endl;
    assert(width>=2);
    int want=uniform_int_distribution<int>(1,width-1)(rng);
    int x=ffind(fet(beg)+want);
    assert(beg<x); assert(x<end);
    cout<<"concat(";
    gen(beg,x);
    cout<<",";
    gen(x,end);
    cout<<")";
  }
}

int main(int argc,char **argv){
  int const n=atoi(argv[1]);
  rng=mt19937(353979873892110948ll+atoi(argv[2]));
  int const max_num=(argc>=4? atoi(argv[3]): 9909);

  v.assign(n,0);
  f.assign(n,0);
  s.assign(n,0);
  for (int i=0; i<n; i++){
    // v[i]=uniform_int_distribution<int>(1,999'999'999)(rng);
    v[i]=uniform_int_distribution<int>(1,max_num)(rng);
    s[i]=bernoulli_distribution(0.5)(rng);
  }
  for (int i=0; i<n; i++){
    f[i]+=(s[i] or i==0 or s[i-1]);
    if ((i|(i+1))<n) f[i|(i+1)]+=f[i];
  }

  gen(0,n); cout<<endl;

  vector<int> swictims,swalues;
  for (int i=n; i--;)
    if (not s[i] and bernoulli_distribution(0.01)(rng))
      swictims.push_back(i),
      swalues.push_back(v[i]);
  shuffle(swictims.begin(),swictims.end(),rng);
  for (int i=swictims.size(); i--;)
    v[swictims[i]]=swalues[i];

  gen(0,n); cout<<endl;
}
