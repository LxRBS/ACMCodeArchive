/*
    ���ӵļ۸����phi(���ӵĳ���)
    phi��ŷ������
    ÿ������һ��lucky number

    Ϊÿ������һ������
    ͬʱҪ�󻨷Ѵ��ڵ��ڸ��˵���������

    ��N��������Ҫ���Ѷ���

    ����ŷ���������ڵ���x��������x+1��ĵ�һ������
*/

#include <stdio.h>
#include <algorithm>
using namespace std;

//����ɸ��
int const SIZE = 1000100;//һ��ֻɸ��30000+����
bool isComp[SIZE] = {false};//isComp[i]Ϊ��˵��i�Ǻ���
int P[SIZE];//P[i]Ϊ��i��������i��0��ʼ
int PCnt = 0;//PCnt��¼1~SIZE֮��������ĸ���
void sieve(){
    for(int i=2;i<SIZE;++i){
        if ( !isComp[i] ) P[PCnt++] = i;

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
    for(int kase=1;kase<=nofkase;++kase){
        int a,n;
        scanf("%d",&n);

        long long int ans = 0;
        for(int i=0;i<n;++i){
            scanf("%d",&a);
            pair<int*,int*> pp = equal_range(P,P+PCnt,a+1);
            ans += *pp.first;
        }

        printf("Case %d: %lld Xukha\n",kase,ans);
    }
    return 0;
}
