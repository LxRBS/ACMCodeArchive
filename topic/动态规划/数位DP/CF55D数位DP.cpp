/*
    ���һ�����ܹ����Լ�����λ�ϵ���������������������
    ��[s,e]֮�������������ж��ٸ�
*/

#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

typedef long long llt;

//Dijk��i��ʾ���ȣ�j��ʾ�Ѿ����ֹ������֣�k��ʾ��ǰ������ֵ
llt D[20][1<<8][2600];
int Dig[100];

//pos��ʾ��ǰ�������λ��ֱ��0
//pre��ʾ֮ǰ�Ѿ����ֹ������֣��ö����Ʊ�ʾ��ʾ
//sum��ʾ��ǰ������ֵ
//limit��ʾ�������Ͻ�
llt dfs(int pos,int pre,int sum,bool limit){
    //���һ�£�sum�Ƿ����������г��ֹ�����λ
    if ( -1 == pos ) {
        for(int i=2;i<=9;++i){
            if ( (pre&(1<<(i-2))) && (0!=sum%i) ){
                return 0;
            }
        }
        return 1;
    }

    //���û�����ƣ�����ǰ���Ѿ����D����ֱ�ӷ���
    if ( !limit && -1 != D[pos][pre][sum] ) return D[pos][pre][sum];

    int last = limit ? Dig[pos] : 9;
    llt ans = 0;

    //�ݹ�����
    for(int i=0;i<=last;++i){
        ans += dfs(pos-1,i<2?pre:pre|(1<<(i-2)),(sum*10+i)%2520,limit&&(i==Dig[pos]));
    }

    return limit?ans:D[pos][pre][sum]=ans;
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


    llt a,b;
    while(nofkase--){
        scanf("%I64d%I64d",&a,&b);
        printf("%I64d\n",ddp(b)-ddp(a-1));
    }
    return 0;
}