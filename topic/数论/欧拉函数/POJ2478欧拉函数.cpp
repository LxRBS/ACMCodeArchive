#include <cstdio>
#define SIZE 1000001
typedef long long llt;
//ɸ��������
bool isComp[SIZE] = {false}; 
int P[SIZE] = {0};
int PCnt = 0;
void sieve(){
	for(llt i=2;i<SIZE;++i){
		if ( isComp[i] ) continue;

		P[PCnt++] = i;
		for(llt j=i*i;j<SIZE;j+=i)
			isComp[j] = true;
	}
}

//������С��������ŷ������
int E[SIZE] = {0};
void euler(){
	//������ŷ����������ֱ�Ӹ���
	for(int i=0;i<PCnt;++i)
		E[P[i]] = P[i] - 1;

	//��n��ŷ������ʱ��n֮ǰ������ŷ��������֪
	for(int i=4;i<SIZE;++i){
		if ( E[i] ) continue;

		for(int j=0;j<PCnt&&P[j]*P[j]<=i;++j){
			if ( i % P[j] ) continue;

			if ( i / P[j] % P[j] )
				E[i] = E[i/P[j]] * ( P[j] - 1 );
			else
				E[i] = E[i/P[j]] * P[j];

			break;
		}
	}
}

llt Ans[SIZE] = {0};
int main(){
	sieve();
	euler();
	for(int i=1;i<SIZE;++i) Ans[i] = Ans[i-1] + E[i];

	int n;
	while( scanf("%d",&n) && n ) 
		printf("%I64d\n",Ans[n]);

	return 0;
}