#include<bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using namespace std;
const int maxn=3e5+5;
int v[maxn],n,N;
void add(int x) {while(x<=N) v[x]++,x+=(-x)&x;}
int qry(int x) {int res=0;while(x) res+=v[x],x-=(-x)&x;return res;}
int l[maxn],r[maxn],q[maxn];
vector<int>st;
int find(int x) {return lower_bound(all(st),x)-st.begin()+1;}
int main() {
	scanf("%d",&n);
	for(int i=0;i<n;i++) {
		scanf("%d%d",l+i,r+i);
		st.push_back(l[i]);
		st.push_back(r[i]);
	}
	int k;
	scanf("%d",&k);
	for(int i=0;i<k;i++) {
		scanf("%d",q+i);
		st.push_back(q[i]);
	}
	sort(all(st));
	st.erase(unique(all(st)),st.end());
	N=st.size();
	for(int i=0;i<k;i++) {
		int p=find(q[i]);
		add(p);
	}
	int ans=0;
	for(int i=0;i<n;i++) {
		int u=find(r[i]),v=find(l[i])-1;
		int sum=qry(u)-qry(v);
		if(sum!=0) ans++;
	}
	cout<<ans<<endl;
	return 0;
}