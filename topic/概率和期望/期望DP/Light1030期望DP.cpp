/*
    1��N�ĵ�ͼ��ÿ��λ����һ�������Ļƽ�
	��ʼ��1λ�ã�ÿ����1��6�����ӣ�ǰ�����ɲ����õ�Ŀ��λ�õĻƽ�
	�����ǰ�Ĳ���ʹ�ó����˵�ͼ������������
	����Nλ�ú�ֹͣ��������õ��ƽ����������� 
	��DiΪ��iλ�õ���Nλ�õ���������
	Di = SIGMA( P(i��j�ĸ���) * Dj ) 
	Djʵ�������ֻ��6�ֿ��ܣ���i+1��i+6 
*/
#include <cstdio>
#include <algorithm>
using namespace std;

int N;
int A[101];
double D[101];//Di��ʾ��λ��i����λ��N������

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        scanf("%d",&N);
        for(int i=1;i<=N;++i)scanf("%d",A+i);

        fill(D,D+N+1,0.0);
        D[N] = A[N];
        for(int i=N-1;i>=1;--i){
            D[i] = A[i];
            int cnt = 6;
            if ( N - i < cnt ) cnt = N - i;
            for(int j=1;j<=cnt;++j) D[i] += D[i+j] / cnt;
        }
        printf("Case %d: %f\n",kase,D[1]);
    }
    return 0;
}
