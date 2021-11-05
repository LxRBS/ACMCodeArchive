/*
  ���������������ӳ��
  Ҫ����һ������ʹ���������

  ����3�ڵ��������Ȼ2��1�ȡ�1��2�ȣ����������ǹ̶���
  ����4�ڵ���������3��1�ȡ�1��3�ȣ�Ҳ����2��2�ȡ�2��1�ȣ������б仯��

  N�ڵ���������е�Ķ����ͱ�Ȼ��2N-2��
  ÿ����������������֪�ģ�Ҫ�����ܺ�һ���µ�������棬����
  ������ֱ���ö��ذ�����Ϊ������1�ȵĵ�
  ���Խ����ۿ�����N-2���൱��ÿ����Ķ���������1��
  Ȼ��ʣ��Ķ����������䣬���������ķ��䷽����Ȼ�Ϸ�
  ֱ������ȫ��������
*/
#include <bits/stdc++.h>
using namespace std;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

typedef int gains_t;//type of gains

//one iteration of complete knapsack problem
//d is the result array
//maxv is the upper bound of the cost namely it is volume in classical problem
//cost is the current cost
//gains is the current gains
void completeKnapsack(gains_t d[],int maxv,int cost,gains_t gains){
    for(int v=cost;v<=maxv;++v){
        d[v] = max(d[v],d[v-cost]+gains);
    }
}

int Gain[3300];
int N;
int D[5500];

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase = getUnsigned();
    while(nofkase--){
        N = getUnsigned();
        for(int i=1;i<N;++i) Gain[i] = getUnsigned();

        fill(D,D+N,-2000000000);
        D[0] = 0;
        for(int i=2;i<N;++i)completeKnapsack(D,N-2,i-1,Gain[i]-Gain[1]);
        printf("%d\n",D[N-2]+N*Gain[1]);
    }
    return 0;
}


