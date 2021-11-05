/**
  1��N�ڣ����ʵ���Ϊ������һ���ж��ٶ�
  gcd(x,y)=p,��gcd(x/p,y/p)=1
  ���ԣ���ÿһ������p������1~N/p��Χ�ڻ��ʵ���һ���ж��ٶԼ���
  ����Ī����˹���ݿɵã���N/p����n
  ans = SIGMA{��(i)*(n/i)*(n/i)}
  �ٶ�ÿһ��������ͼ���
  ע�⵽n/i����ʹ�ø���ʱ�临�Ӷ��������̺��������Ԥ����ǰ׺��
*/
#include <stdio.h>
typedef long long int llt;

int const SIZE = 10000007;//TODO
bool isComp[SIZE] = {false};
int P[SIZE] = {0};
int PCnt = 0;
int Euler[SIZE] = {0,1};
int Mobius[SIZE] = {0,1};
llt C[SIZE] = {0LL,1LL};//Ci = sigma(miu(i))
void sieveEulerMobius(){
    int tmp;
	for(int i=2;i<SIZE;++i){
		if ( !isComp[i] ) P[PCnt++] = i, Euler[i] = i - 1, Mobius[i] = -1;

		for(int j=0;j<PCnt&&i*P[j]<SIZE;++j){
			isComp[tmp=i*P[j]] = true;

			if ( 0 == i % P[j] ){
				Euler[tmp] = Euler[i] * P[j];
				Mobius[tmp] = 0;
				break;
			}else{
				Euler[tmp] = Euler[i] * ( P[j] - 1 );
				Mobius[tmp] = - Mobius[i];
			}
		}

		C[i] = C[i-1] + Mobius[i];
	}
}

int main(){
    sieveEulerMobius();

    int n;
    scanf("%d",&n);
    llt ans=0LL;
    for(int i=0;i<PCnt&&P[i]<=n;++i){//��ÿһ������
        for(int r,j=1,nn=n/P[i];j<=nn;j=r+1){//�����ֿ�
            r = nn / (nn/j);
            ans += ( C[r] - C[j-1] ) * (nn/j) * (nn/j);
        }
    }
    printf("%lld\n",ans);
    return 0;
}


