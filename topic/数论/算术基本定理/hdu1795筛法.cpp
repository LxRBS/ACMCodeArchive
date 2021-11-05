//�����������С����
//��Χ��С��ɸ��������ʱ��ֱ�Ӵ���
#include <cstdio>
#include <algorithm>
using namespace std;
#define SIZE 10011
bool isComp[SIZE] = {false};
int P[SIZE] = {0};
int PCnt = 0;
int Ans[SIZE] = {0};
void sieve(){
	for(int i=2;i<SIZE;++i){
		if ( !isComp[i] ) 
			P[PCnt++] = i,fill(Ans+P[PCnt-2],Ans+i,i);

		for(int j=0;j<PCnt&&i*P[j]<SIZE;++j){
			isComp[i*P[j]] = true;
			if ( 0 == i % P[j] ) break;
		}
	}
}

int main(){
	sieve();
	int nofkase;
	scanf("%d",&nofkase);
	while(nofkase--){
		int x;
		scanf("%d",&x);
		printf("%d\n",Ans[x]);
	}

	return 0;
}