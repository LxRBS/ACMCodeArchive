#include<bits/stdc++.h>
using namespace std;

const int M=3e5+9;
int n,k,num;
int a[M],s[M],b[M];
void work(){

	int top=0,num=0;
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i]);
	}
	priority_queue<int>q;
	for(int i=1;i<=n;++i){
		while(top&&s[top]<a[i]&&k){
			q.push(s[top]);
			top--;
			k--;
		}
		s[++top]=a[i];
	}
	for(int i=1,l=1;i<=n;++i){
		if(l>top){
			b[++num]=q.top();
			q.pop();
		}
		else if(q.empty()){
			b[++num]=s[l];
			l++;
		}
		else{
			if(q.top()>s[l]){
				b[++num]=q.top();
				q.pop();
			}
			else{
				b[++num]=s[l];
				l++;
			}
		}
	}
	for(int i=1;i<=n;++i){
		printf("%d%c",b[i]," \n"[i==n]);
	}
}
int main(){
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
	int T;
	scanf("%d",&T);
	while(T--)work();
	return 0;
}
/*
2
7 3
1 4 2 1 4 2 4
5 2
4 3 5 4 5
*/