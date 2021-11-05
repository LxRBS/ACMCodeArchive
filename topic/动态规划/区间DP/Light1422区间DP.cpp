/*
    �μ���ʥ�ھۻᣬ�������·������·�
    ÿ���ۻ������������һ�����·�Ҳ���������ѵ����ɼ��·�
    �ѵ����·�������ʹ��
    ÿ���ۻ���ָ�����·�
    ��������Ҫ���ټ��·�
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int N;
int A[110];
int D[110][110];

int dp(int s,int e){
    if ( -1 != D[s][e] ) return D[s][e];
    if ( s == e ) return D[s][e] = 1;
    if ( e < s ) return D[s][e] = 0;

    int& r = D[s][e];
    r = dp(s+1,e) + 1;

    for(int k=s+1;k<=e;++k)if(A[s]==A[k]){
        r = min(r,dp(s+1,k-1)+dp(k,e));
    }

    return r;
}

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        scanf("%d",&N);
        for(int i=0;i<N;++i) scanf("%d",A+i);

        memset(D,-1,sizeof(D));
        printf("Case %d: %d\n",kase,dp(0,N-1));
    }
    return 0;
}
