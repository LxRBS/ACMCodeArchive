#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// https://en.wikipedia.org/wiki/Edmonds%27_algorithm
// With link-cut trees to improve performance from O(VE) to O(V^2logV)

struct LinkCut{/*{{{*/
  LinkCut *p,*l,*r;
  LinkCut(LinkCut* p=0): p(p), l(0), r(0) {}

  bool root() {return not p or p->l != this and p->r != this;}

  void rot(LinkCut* LinkCut::*a,LinkCut* LinkCut::*b) {
    if (not root()) (p->l==this?p->l:p->r)=(this->*a);
    (this->*a)->p=p, p=(this->*a);
    (this->*a)=(p->*b), (p->*b)=this;
    if (this->*a) (this->*a)->p=this;
  }

  void rotate() {
    if (p->l==this) p->rot(&LinkCut::l,&LinkCut::r);
    else            p->rot(&LinkCut::r,&LinkCut::l);
  }

  void splay() {
    while (not root()) {
      if (not p->root()) ((p->l==this)==(p->p->l==p)? p:this)->rotate();
      rotate();
    }
  }

  void link(LinkCut* x) {
    splay(); x->splay(); p=x; p->l=this; expose();
  }

  void cut() {
    splay(); if (r) r->p=p; p=r=0;
  }

  void expose() {
    for (LinkCut* i=this,*j=0; i; j=i,i=i->p) {
      i->splay();
      i->l=j;
    }
    splay();
  }

  LinkCut* findroot() {
    expose();
    LinkCut* x=this;
    while (x->r) x=x->r;
    x->expose();
    return x;
  }

};/*}}}*/

struct Graph{
  int const n;
  vector<vector<int32_t>> edge;

  Graph(int n): n(n) {edge.assign(n,vector<int32_t>(n,1<<30));}

  int64_t minimum_cost_arborescence(){
    vector<priority_queue<pair<int32_t,int>,vector<pair<int32_t,int>>,greater<pair<int32_t,int>>>> pi(n);
    for (int i=n; i-->1;)
      for (int j=n; j-->0;)
        if (i!=j) pi[i].emplace(edge[j][i],j);

    vector<LinkCut> lc(n);
    vector<bool> exists(n,true),merging(n,false);
    vector<int> par(n,-1);

    auto const get_pi=[&pi,&exists,this](int i){
      while (not exists[pi[i].top().second] or edge[pi[i].top().second][i]!=pi[i].top().first){
        pi[i].pop();
      }
      return pi[i].top().second;
    };

    int64_t res=0;
    for (int i=1; i<n; i++) if (exists[i]){
      int const j=get_pi(i);

      // If no conflict, make i a child of j.
      if (lc[j].findroot()!=&lc[i]){
        lc[i].link(&lc[j]);
        res+=edge[j][i];
        par[i]=j;
      }else{
        // Conflict! Rest of cycle goes through a common ancestor.
        vector<int> del={i};
        merging[i]=true;
        for (int x=j; x!=i; x=par[x]){
          del.push_back(x);
          merging[x]=true;
        }

        vector<int32_t> old_pi(n);
        for (int b: del){
          if (b==i){
            old_pi[b]=edge[j][b];
          }else{
            old_pi[b]=edge[par[b]][b];
            exists[b]=false;
          }
        }
        res+=edge[j][i];

        // Detach edges from the solution that went to deleted nodes.
        vector<int> cycle_children;
        for (int a=1; a<i; a++) if (exists[a] and merging[par[a]]) {
          cycle_children.push_back(a);
          res-=edge[par[a]][a];
          lc[a].cut();
        }

        // Merge deleted nodes' edges together, adding new edges for vertex i.
        for (int a=0; a<n; a++) if (exists[a] and a!=i){
          edge[a][i]-=old_pi[i];
        }
        for (int b: del) if (b!=i){
          for (int a=0; a<n; a++) if (a!=i and exists[a]){
            edge[a][i]=min(edge[a][i],edge[a][b]-old_pi[b]);
            edge[i][a]=min(edge[i][a],edge[b][a]);
          }
        }
        // Put the merged node back into the priority queues.
        for (int a=0; a<n; a++) if (exists[a] and a!=i){
          pi[a].emplace(edge[i][a],i);
          pi[i].emplace(edge[a][i],a);
        }
        // Reattach deleted solution edges to the merged vertex.
        for (int a: cycle_children){
          res+=edge[i][a];
          lc[a].link(&lc[i]);
          par[a]=i;
        }
        for (int b: del) {
          merging[b]=false;
        }
        --i;
      }
    }

    return res;
  }
};

int main(){
  ios::sync_with_stdio(false);
  int n; cin>>n;
  Graph g(n+1);

  for (int i=1; i<=n; i++){
    int x,t; cin>>x>>t;
    for (int j=0; j<=n; j++){
      cin>>g.edge[j][i];
    }
    if (x!=i){
      g.edge[x][i]=t;
    }
  }

  cout<<g.minimum_cost_arborescence()<<endl;
}
