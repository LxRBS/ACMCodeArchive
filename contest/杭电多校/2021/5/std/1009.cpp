#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pb push_back
const int N=2e6+3;
vector<int>G[N];
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int n,t;
	cin>>t;
	while(t--){
		cin>>n;
		unordered_set<int>s;
		vector<int>a(n+1);
		for(int i=1;i<=n;++i){
			cin>>a[i]; s.insert(a[i]); G[a[i]].pb(i);
		}
		ll ans=0;
		for(auto num:s){ // ö��ÿ������Ϊ���� 
			ll res=0;// �� 
			ll sum=0;// ��ǰǰ׺��
			unordered_map<int,int>f1,f2;// ǰ׺��Ϊsum�ĵ���f1[sum]�� 
			G[num].pb(n+1);
			ll k=0,minn=0;
			for(int j=1;j<=n;++j){
				if(j>G[num][k]) k++;
				if(a[j]!=num&&sum==minn){
					ll len=G[num][k]-j-1;
					f2[sum+1]--;
					f2[sum-len]++;
					j+=len;
					sum-=len+1;
				}
				else if (a[j]==num){
					f1[sum]+=f2[sum];
					f2[sum+1]+=f2[sum];
					f2[sum]=0;
					f1[sum]++;
					res+=f1[sum];
					sum++;
					ans+=res;
				}
				else{
					f1[sum]++;
					sum--;
					res-=f1[sum];
					ans+=res;
				}
				if(minn>sum)minn=sum;
			}
			
		}
		cout<<ans<<'\n';
		for(auto &i:s)G[i].clear();
	}
	return 0;
}
 