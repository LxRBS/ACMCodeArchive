#pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;
const int P=1e9+9;
const int M=1e7+5;
const int Inv2=(P+1)/2;

long long Pow(long long a,long long p)
{
	static long long ret;
	for(ret=1;p;a=a*a%P,p>>=1)if(p&1)ret=ret*a%P;
	return ret;
}

long long Inv[M],Fact[M],Finv[M];
void Init(int n)
{
	Fact[0]=Inv[0]=Finv[0]=1;
	for(int i=1;i<=n;i++)Fact[i]=Fact[i-1]*i%P;
	Finv[n]=Pow(Fact[n],P-2);
	for(int i=n-1;i>=0;i--)Finv[i]=Finv[i+1]*(i+1)%P;
	for(int i=1;i<=n;i++)Inv[i]=Fact[i-1]*Finv[i]%P;
}

long long Combination(int x,int y){return y<0||y>x?0:Fact[x]*Finv[y]%P*Finv[x-y]%P;}
long long Permutation(int x,int y){return y<0||y>x?0:Fact[x]*Finv[x-y]%P;}

struct cser
{
	int x,y;
	long long ret;
	void Reset(){x=y=0;ret=1;}
	void Addy(){++y;(ret+=Combination(x,y))%=P;}
	void Suby(){(ret+=P-Combination(x,y))%=P;y--;}
	void Addx(){ret=(ret*2+P-Combination(x,y))%P;x++;}
	void Subx(){--x;ret=(ret+Combination(x,y))*Inv2%P;}
	long long Moveto(int xx,int yy)
	{
		while(x<xx)Addx();
		while(x>xx)Subx();
		while(y<yy)Addy();
		while(y>yy)Suby();
		return ret;
	}
}cs1,cs2;

int n,m,K;

void Solve1()
{
	long long ans=0;
	long long Pw2=1;
	for(int i=0;i<=K;i++)
	{
		long long th=Permutation(n+m,i);
		ans^=th*Pw2%P;
		(Pw2<<=1)%=P;
	}
	printf("%lld ",ans);
}

void Solve2()
{
	long long ans=0;
	long long Pw2=1;
	cs1.Reset();cs2.Reset();
	for(int i=0;i<=K;i++)
	{
		long long th=Fact[n]*Fact[m]%P*Finv[n+m-i]%P
				    *(cs1.Moveto(n+m-i,n)+P-cs2.Moveto(n+m-i,n-i-1))%P;
		ans^=th*Pw2%P;
		(Pw2<<=1)%=P;
	}
	printf("%lld\n",ans);
}

int main()
{
	scanf("%d%d",&n,&m);n-=2;m-=2;
	K=n+m;
	Init(K);
	Solve1();
	Solve2();
	return 0;
}
