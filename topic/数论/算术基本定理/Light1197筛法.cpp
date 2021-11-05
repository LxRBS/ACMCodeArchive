/*
     ������[a,b]֮��������ĸ���
     ���䳤�����Ϊ10��
     ��a���ܴܺ�
     ɸ��
*/
#include <stdio.h>
#include <cmath>
#include <algorithm>
using namespace std;

//����ɸ��
int const SIZE = 65536;//һ��ֻɸ��30000+����
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

typedef long long llt;
bool Flag[100010];

//ɸ[a,b]֮�������
int proc(int a,int b){
    fill(Flag,Flag+b-a+1,false);
    for(int i=0;i<PCnt&&(llt)P[i]*P[i]<=b;++i){
        llt start = (llt)P[i] * P[i];
        if ( start < a ) start = 0 == a % P[i] ? a : (llt)a / P[i] * P[i] + P[i];
        //��start��ʼɸ
        for(llt j=start;j<=b;j+=P[i])Flag[j-a]=true;
    }
    int ans=0;
    for(int i=a;i<=b;++i)if(!Flag[i-a])++ans;
    return 1==a?ans-1:ans;
}

int main(){
    sieve();

    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        int a,b;
        scanf("%d%d",&a,&b);
        printf("Case %d: %d\n",kase,proc(a,b));
    }
    return 0;
}