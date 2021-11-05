//根据题意推导
//m = n + n * sqrt( (b-a)/b ) 或者
//m = n - n * sqrt( (b-a)/b )
//所以设 b = x * y, x是平方数，y是剩余因子
//则 b-a 是 1*y, 4*y, 9*y, ... 且小于b
#include <cstdio>
#include <vector>
using namespace std;

#define SIZE 1001
bool isComp[SIZE];
int P[SIZE];
int PCnt = 0;
void sieve(){
	for(int i=2;i<SIZE;++i){
		if ( !isComp[i] ) P[PCnt++] = i;
		for(int j=0;j<PCnt&&i*P[j]<SIZE;++j){
			isComp[i*P[j]] = true;
			if ( 0 == i % P[j] )break;
		}
	}
}
int A,B,M,N;
vector<int> Va,Vm0,Vm1;
inline bool read(){
	scanf("%d%d",&B,&N);
	return B || N;
}
//将n分解成x*x*y，x尽可能大
void fac(int n,int&x,int& y){
	x = y = 1;
	for(int i=0;i<PCnt&&P[i]*P[i]<=n;++i){
		if ( n % P[i] ) continue;
		int k = 0;
		while( 0 == n % P[i] ){
			n /= P[i];
			++k;
			if ( 0 == k % 2 ) x *= P[i];
		}
		if ( k & 1 ) y *= P[i];
		if ( 1 == n ) break;
	}
	if ( n != 1 ) y *= n;
}
int main(){
	sieve();
	Va.reserve(1001);
	Vm0.reserve(1001);
	Vm1.reserve(1001);
	while( read() ){
		Va.clear();
		Vm0.clear();
		Vm1.clear();
		int x,y;
		fac(B,x,y);
		for(int i=1;i*i*y<=B;++i){
			//sqrt((b-a)/b)为i/x，且n*i/x必须为整数
			if ( N * i % x ) continue;
			A = B - i * i * y;
			M = N + N * i / x;
			Va.push_back(A);
			Vm0.push_back(M);
			M = N - N * i / x;
			Vm1.push_back(M);
		}
		printf("%d/%d",Va.back(),Vm0.back());
		for(int i=Va.size()-2;i>=0;--i)
			printf(" %d/%d",Va[i],Vm0[i]);
		for(unsigned i=0;i<Va.size()-1;++i)
			printf(" %d/%d",Va[i],Vm1[i]);
		printf("\n");
	}
	return 0;
}
