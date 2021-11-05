/*
    ��[s,e]֮�京��49�������ж��ٸ�
*/

#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

typedef long long llt;

//Dijk��ʾ����Ϊi��ǰһλΪj����������������k��ʾǰ������Ƿ��Ѿ��Ϸ�
llt D[20][10][2];
int Dig[100];

//pos��ʾ��ǰ�������λ��ֱ��0
//pre��ʾǰһλ
//status��ʾ״̬��ֻȡ1��0
//limit��ʾ�������Ͻ�
llt dfs(int pos,int pre,int status,bool limit){
    if ( -1 == pos ) return status;//�ܹ����������ֻ��status����

    //���û�����ƣ�����ǰ���Ѿ����D����ֱ�ӷ���
    if ( !limit && -1 != D[pos][pre][status] ) return D[pos][pre][status];

    int last = limit ? Dig[pos] : 9;
    llt ans = 0;

    //�ݹ�����
    for(int i=0;i<=last;++i){
        ans += dfs(pos-1,i,status||(4==pre&&9==i),limit&&(i==Dig[pos]));
    }

    return 0==limit?D[pos][pre][status]=ans:ans;
}

//��[1,n]�������������ж��ٸ�
llt ddp(llt n){
    int k = 0;
    while(n){
        Dig[k++] = n % 10;
        n /= 10;
    }
    return dfs(k-1,0,0,true);
}

int main(){
    //freopen("1.txt","r",stdin);

    memset(D,-1,sizeof(D));
    int nofkase;
    scanf("%d",&nofkase);


    llt n;
    while(nofkase--){
        scanf("%I64d",&n);
        printf("%I64d\n",ddp(n));
    }
    return 0;
}