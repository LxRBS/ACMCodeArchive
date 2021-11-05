/*
    ����Ϊ������������֮������Ϊ2��������
    ��[s,e]֮�������������
*/

#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

typedef long long llt;

//Di��i��ʾ���ȣ�j��ʾ���λ
llt D[15][11];
int Dig[100];

//pos��ʾ��ǰ�������λ��ֱ��0
//pre��ʾǰһλ�����
//lead��ʾ�Ƿ�Ϊǰ��0
//limit��ʾ�Ƿ�Ҫ�����Ͻ�
llt dfs(int pos,int pre,bool lead,bool limit){
    //���һ�£��Ƿ�Ϸ��������ѵ�����϶��Ϸ�
    if ( -1 == pos ) return 1;

    //���û�����ƣ�����ǰ���Ѿ����D����ֱ�ӷ���
    if ( !lead && !limit && -1 != D[pos][pre] ) return D[pos][pre];

    int last = limit ? Dig[pos] : 9;
    llt ans = 0;

    //�ݹ�����
    for(int i=0;i<=last;++i){
        if ( lead ){
            if ( 0 == i ) ans += dfs(pos-1,0,true,limit&&i==last);
            else ans += dfs(pos-1,i,false,limit&&i==last);
        }else if( pre + 2 <= i || i <= pre - 2 ){
            ans += dfs(pos-1,i,false,limit&&i==last);
        }
    }

    return lead||limit?ans:D[pos][pre]=ans;
}

//��[1,n]�������������ж��ٸ�
llt ddp(llt n){
    int k = 0;
    while(n){
        Dig[k++] = n % 10;
        n /= 10;
    }
    llt tmp = dfs(k-1,0,true,true);
    return tmp;
}

int main(){
    //freopen("1.txt","r",stdin);

    memset(D,-1,sizeof(D));

    llt a,b;
    for(;2==scanf("%lld%lld",&a,&b);){
        printf("%lld\n",ddp(b)-ddp(a-1));
    }
    return 0;
}
