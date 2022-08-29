#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

vector<pair<int,int> > S,T;vector<int> V;

int sumlen[200000];

int query_pos(int x)
{
	int pos=lower_bound(T.begin(),T.end(),make_pair(x+1,-1))-T.begin();
	if(pos==0)return x;
	if(T[pos-1].second>=x)return -1;
	return x-sumlen[pos-1];
}

const long long MOD=998244353;
int add(int x,int y){return x+y>=MOD?x+y-MOD:x+y;}
int sub(int x,int y){return x>=y?x-y:x+MOD-y;}
struct mat
{
	long long num[2][2];
	long long *operator[](int x){return num[x];}
	mat(){for(int i=0;i<2;i++)for(int j=0;j<2;j++)num[i][j]=0;}
};
mat operator*(mat A,mat B)
{
	mat C;
	for(int i=0;i<2;i++)
	{
		for(int j=0;j<2;j++)
		{
			for(int k=0;k<2;k++)C[i][j]=add(C[i][j],A[i][k]*B[k][j]%MOD);
		}
	}
	return C;
}

mat fast_pow(mat A,int p)
{
	mat D;D[0][0]=D[1][1]=1;
	while(p)
	{
		if(p&1)D=D*A;A=A*A;p>>=1;
	}
	return D;
}

int main()
{
	//freopen("1002.in","r",stdin);
	//freopen("1002.out","w",stdout);
	int TT=0;scanf("%d",&TT);
	mat A,B;
	A[0][0]=1,A[1][0]=1,A[0][1]=1,A[1][1]=2;
	B[0][0]=0,B[1][0]=1,B[0][1]=0,B[1][1]=2;
	while(TT--)
	{
		int n=0,m=0;scanf("%d%d",&n,&m);
		for(int i=1,x=0,y=0;i<=m;i++)
		{
			scanf("%d%d",&x,&y);if(x>y)swap(x,y);
			//if(x==1)puts("??");
			if(x<y){S.push_back(make_pair(x,y-1));}
			V.push_back(y); 
		}
		sort(S.begin(),S.end());
		for(int i=0;i<S.size();i++)
		{
			if(T.empty()||T.back().second+1<S[i].first)T.push_back(S[i]);
			else T.back().second=max(T.back().second,S[i].second);
		}
		for(int i=0;i<T.size();i++)
		{
			sumlen[i]=T[i].second-T[i].first+1;if(i)sumlen[i]+=sumlen[i-1];
		}
		
		
		sort(V.begin(),V.end());V.erase(unique(V.begin(),V.end()),V.end());
		int lst=0;mat ans;ans[0][0]=ans[1][1]=1;
		for(int i=0;i<V.size();i++)
		{
			int cur=query_pos(V[i]);if(cur==-1)continue;
			ans=ans*fast_pow(A,cur-lst-1);
			ans=ans*B;
			lst=cur;
		}
		ans=ans*fast_pow(A,query_pos(n)-lst);
		printf("%lld\n",add(ans[0][0],ans[1][0]));
		
		S.clear(),T.clear(),V.clear();
	}
}