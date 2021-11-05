/*
    ��ʾ�ɶ������Ժ�0��1����Ϊ�ǺϷ���
    ��[s,e]֮���ж��ٸ����ǺϷ���
*/

#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

typedef long long llt;

//Dij��i��ʾ���ȣ�j��ʾ0��1������֮���32
llt D[40][70];
int Dig[100];

//pos��ʾ��ǰ�������λ��ֱ��0
//pre��ʾ֮ǰ��0��1������֮���32
//lead��ʾ�Ƿ�ǰ��0
//limit��ʾ�Ƿ�Ҫ�����Ͻ�
llt dfs(int pos,int pre,bool lead,bool limit){
    //���һ�£��Ƿ�Ϸ�
    if ( -1 == pos ) return pre >= 32;

    //���û�����ƣ�����ǰ���Ѿ����D����ֱ�ӷ���
    if ( !limit && !lead && -1 != D[pos][pre] ) return D[pos][pre];

    int last = limit ? Dig[pos] : 1;
    llt ans = 0;

    //�ݹ�����
    for(int i=0;i<=last;++i){
        if ( lead && 0==i ) ans += dfs(pos-1,pre,true,limit&&(i==Dig[pos]));
        else ans += dfs(pos-1,pre+(0==i?1:-1),false,limit&&(i==Dig[pos]));
    }

    return limit||lead?ans:D[pos][pre]=ans;
}

//��[1,n]�������������ж��ٸ�
llt ddp(llt n){
    int k = 0;
    while(n){
        Dig[k++] = n & 1;
        n >>= 1;
    }
    llt tmp = dfs(k-1,32,true,true);
    return tmp;
}

int main(){
    //freopen("1.txt","r",stdin);

    memset(D,-1,sizeof(D));

    llt a,b;
    while(2 == scanf("%I64d%I64d",&a,&b)){
        printf("%I64d\n",ddp(b)-ddp(a-1));
    }
    return 0;
}
