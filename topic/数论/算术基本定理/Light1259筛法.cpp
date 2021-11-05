/*
    ����n�����ж�����(a,b)����
    a+b=n��a��b��Ϊ����
    ɸ��������
    ��������鿪��һǧ��ֱ���ж�
*/
#include <stdio.h>
#include <math.h>
#include <iostream>
using namespace std;

//����ɸ��
int const SIZE = 1E7+5;//һ��ֻɸ��30000+����
bool isComp[SIZE] = {false};//isComp[i]Ϊ��˵��i�Ǻ���
int P[665000];//1E7���ڵ�����Ϊ664000+
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
    //freopen("1.txt","r",stdin);
    sieve();

    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        int n;
        scanf("%d",&n);

        int ans = 0;
        int n2 = n >> 1;
        for(int i=0;P[i]<=n2&&i<PCnt;++i)if(!isComp[n-P[i]])++ans;
        printf("Case %d: %d\n",kase,ans);
    }
    return 0;
}