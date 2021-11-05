//ѡk����ͬ��������ʹ���ǢΪn���󷽰����������Կ�����01����
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

//��ͨɸ��
int const SIZE = 1130;
bool isComp[SIZE] = {false};//isComp[i]Ϊ��˵��i�Ǻ���
int P[SIZE];//P[i]Ϊ��i��������i��0��ʼ
int PCnt = 0;//PCnt��¼1~SIZE֮��������ĸ���

void sieve(){
    for(int i=2;i<SIZE;++i){
        if ( isComp[i] ) continue;

        P[PCnt++] = i;
        for(int j=i*i;j<SIZE;j+=i){//i*i���ܳ���Χ
            isComp[j] = true;
        }
    }
}

int D[15][1121];//Dkin��ʾǰi������ѡk����Ϊn������������i�ù��������Ż���
void dp(){
    fill(D[0],D[0]+1121,0);
    D[0][0] = 1;
    for(int i=0;i<PCnt;++i){
        for(int n=1120;n>=P[i];--n){
            for(int k=1;k<15;++k){
                D[k][n] += D[k-1][n-P[i]];//����01�������󷽰�������
            }
        }
    }
}

int main(){
    sieve();
    dp();
    int n,k;
    while(scanf("%d%d",&n,&k)&&n&&k){
        printf("%d\n",D[k][n]);
    }
    return 0;
}

