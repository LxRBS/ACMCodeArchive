#include <bits/stdc++.h>

#define M 500005
#define N 1048576

#define Mo 998244353
#define g 3

using namespace std;

int A[N], B[N], w[2][N], n, rev[N];

int power(int x, int y, int mod)
{
	int s = 1;
	for (; y; y >>= 1, x = 1ll * x * x % mod) if (y & 1) s = 1ll * s * x % mod; 
	return s;
}

void NTT(int *A,int f)
{
		int i,j,k,l,t;
		for (i=0;i<N;++i) if (i<rev[i]) swap(A[i],A[rev[i]]); 
		for (i=1;i<N;i<<=1)
			for (j=0,t=N/(i<<1);j<N;j+=(i<<1))
				for (k=0,l=0;k<i;++k,l+=t)
				{
						int x=A[j+k],y=1ll*A[j+k+i]*w[f][l]%Mo;
						A[j+k]=(x+y)%Mo; A[j+k+i]=(x-y+Mo)%Mo;
				}
		if (f)
		{
				int invn=power(N,Mo-2,Mo);
				for (i=0;i<N;++i) A[i]=1ll*A[i]*invn%Mo; 
		}
}
void work(int *A, int *B)
{
	w[0][0] = 1; w[0][1] = power(g, (Mo - 1) / N, Mo);
	for (int i = 2;i < N; ++i) w[0][i] = 1ll * w[0][i-1] * w[0][1] % Mo;
	for (int i = 0;i < N; ++i) w[1][i] = power(w[0][i], Mo - 2, Mo);	
 	for (int i=0;i<N;++i) 
 		for (int j=1,k=i;j<N;j<<=1,k>>=1) (rev[i]<<=1)|=(k&1);
 		
	NTT(A, 0); NTT(B, 0);
	for (int i = 0; i < N; ++i) A[i] = 1ll * A[i] * B[i] % Mo;
	NTT(A, 1);
}

int main()
{
	scanf("%d", &n);
	for (; n--; )
	{
		int x; scanf("%d", &x);
		A[x]++; B[M - x]++;
	}
	work(A, B);
	for (int i = 1; i < M; ++i)
	{
		int flag = 1;
		for (int j = i; j < M; j += i)
			if (A[j + M]) 
			{
				flag = 0;
				break;
			}
		if (flag) 
		{
			printf("%d\n", i);
			break;
		}
	}
}
