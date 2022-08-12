#include<bits/stdc++.h>
using namespace std;
int n,a[100005],sz;
const int lmt=1<<15;
void dfs(int x,int sz){
	if(x>lmt)return;
	if(sz==1){
		a[++::sz]=x;
		return;
	}
	int y=rand()%(sz-1)+1;
	dfs(x*2,y);
	dfs(x*2,sz-y);
}
int main(){
    freopen("7.in","w",stdout);
	srand(time(0)); 
    n=rand()%1000+1;
    dfs(2,n);
    cout<<sz<<endl;
    for(int i=1;i<=sz;i++){
    	if(i<=10)cout<<a[i]<<" ";
    	else cout<<a[i]+rand()%5<<" ";
	}
    return 0;
}
