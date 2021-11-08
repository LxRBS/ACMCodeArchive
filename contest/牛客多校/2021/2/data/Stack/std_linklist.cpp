#include<bits/stdc++.h>
using namespace std;
const int M=1e6+5;

void Rd(int &r)
{
	static char c;
	for(c=0;c<'0' || c>'9';c=getchar());
	for(r=0;c>='0' && c<='9';c=getchar())r=r*10+(c^'0');
}

int n,m;
int Q[M];

int L[M],R[M],I[M];void Link(int l,int r){L[r]=l,R[l]=r;}
int Stk[M];

void Solve()
{
	Link(0,n+1);
	int pos=1,sv=0;
	for(int i=1;i<=n;i++)
	{
		if(Q[i]==-327327327)continue;
		if(Q[i]<1 || Q[i]>i){puts("-1");return;}
		if(Q[i]-sv > i-pos+1){puts("-1");return;}
		while(pos<=i)
		{
			if(sv<Q[i])
			{
				Link(pos,R[Stk[sv]]),Link(Stk[sv],pos);
				sv++,Stk[sv]=pos;
			}
			else
			{
				sv=Q[i]-1;
				Link(pos,R[Stk[sv]]),Link(Stk[sv],pos);
				Stk[++sv]=pos;
			}
			pos++;
		}
	}
	while(pos<=n)Link(pos,R[Stk[sv]]),Link(Stk[sv],pos),pos++;
	for(int i=R[0],cnt=1;i<=n;i=R[i],cnt++)I[i]=cnt;
	for(int i=1;i<=n;i++)printf("%d ",I[i]);
}

int main()
{
	Rd(n);Rd(m);
	for(int i=1;i<=n;i++)Q[i]=-327327327;
	for(int i=1,x;i<=m;i++)Rd(x),Rd(Q[x]);
	Solve();
	return 0;
}
