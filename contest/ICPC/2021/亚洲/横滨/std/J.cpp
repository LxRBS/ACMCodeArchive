/** 
* copy from CSU-team1
*/

#include<bits/stdc++.h>

#define fi first
#define se second
#define pii pair<int, int>
#define LL long long
#define fo(i, a, b) for(int i = a; i <= b; i++)
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0' || ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0' && ch<='9')x=x*10+ch-'0',ch=getchar();
    return x*f;
}
template<class T>inline void write(T x)
{
    static int stack[20];
    if(x<0){putchar('-');x=-x;}
    if(!x){putchar('0');return;}
    int top=0;
    while(x)stack[++top]=x%10,x/=10;
    while(top)putchar(stack[top--]+'0');
}
template<class T>inline void pr1(T x){write(x);putchar(' ');}
template<class T>inline void pr2(T x){write(x);puts("");}
const int N = 2e5 + 10;
const int B = 1331, mod = 919491001, md = 993244853, D = 233;
struct Tree {
  struct edge {
    int x, y, next;
  } e[N * 2]; int len, last[N];
  bool v[N], h[N];
  int tp, sta[N], tot[N];
  pii f[N];
  vector<int> q;
  vector<pii> g;
  
  void ins(int x, int y) {
    e[++len] = edge{x, y, last[x]};
    last[x] = len;
  }
  
  void dfs(int x, int lst) {
    v[x] = 1, sta[++tp] = x;
    for(int k = last[x]; k; k = e[k].next) {
      if((int)q.size() > 0) return ;
      int y = e[k].y;
      if(k ^ (lst ^ 1)) {
        if(v[y]) {
          for(int i = tp; sta[i] != y; i--) h[sta[i]] = 1, q.emplace_back(sta[i]);
          h[y] = 1, q.emplace_back(y);
          return ;
        } else dfs(y, k);
      }
    } tp--;
  }
  
  void gg(int x, int fa) {
    vector<int> r; tot[x] = 1;
    for(int k = last[x]; k; k = e[k].next) {
      int y = e[k].y;
      if(y ^ fa && !h[y]) {
        gg(y, x), r.push_back(f[y].fi), tot[x] += tot[y];
        f[x].se = f[x].se ^ (((LL)f[y].se * D + tot[y]) % md);
      }
    } sort(r.begin(), r.end());
    fo(i, 0, (int)r.size() - 1) {
      f[x].fi = ((LL)f[x].fi * B + r[i]) % mod;
    } f[x].fi = (LL)f[x].fi * tot[x] % mod;
    if((int)r.size() == 0) f[x].fi = 1;
  }
  
  void gao() {
    dfs(1, 0);
    fo(i, 0, (int)q.size() - 1) gg(q[i], 0), g.push_back(f[q[i]]);
  }
} T1, T2;
pii s1[N * 2], s2[N]; int p[N];
int main()
{
    //freopen("a.in","r",stdin);
    //freopen("a.out","w",stdout);
    int n=read();
    T1.len = T2.len = 1;
    fo(i, 1, n) {
      int x = read(), y = read();
      T1.ins(x, y), T1.ins(y, x);
    }
    fo(i, 1, n) {
      int x = read(), y = read();
      T2.ins(x, y), T2.ins(y, x);
    }
    T1.gao(), T2.gao();
    if((int)T1.q.size() != (int)T2.q.size()) puts("No");
    else {
      int len = (int)T1.q.size();
      fo(i, 1, len) s1[i] = T1.g[i - 1], s1[i + len] = s1[i];
      fo(i, 1, len) s2[i] = T2.g[i - 1];
      p[1] = 0;
      fo(i, 2, len) {
        int j = p[i - 1];
        while(s2[i] != s2[j + 1] && j) j = p[j];
        if(!j && s2[i] != s2[1]) p[i] = 0;
        else p[i] = j + 1;
      }
      int j = 0;
      bool bk = 0;
      fo(i, 1, len * 2) {
        while(s1[i] != s2[j + 1] && j) j = p[j];
        if(s1[i] == s2[j + 1]) j++;
        if(j == len) {bk = 1; break;}
      }
      if(bk) {puts("Yes"); return 0;} 
      reverse(s1 + 1, s1 + len * 2 + 1);
      j = 0;
      bk = 0;
      fo(i, 1, len * 2) {
        while(s1[i] != s2[j + 1] && j) j = p[j];
        if(s1[i] == s2[j + 1]) j++;
        if(j == len) {bk = 1; break;}
      }
      if(bk) {puts("Yes"); return 0;}
      puts("No");
    }
    return 0;
}
