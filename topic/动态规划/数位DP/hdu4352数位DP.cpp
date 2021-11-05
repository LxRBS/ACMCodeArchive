/*
    ����Ϊ��ϸ���������г��ȵ���k
    ��[s,e]֮�������������
*/

#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

typedef long long llt;

int K;

//Dijk��i��ʾ���ȣ�j��ʾ��Ӧ���ֵĳ��������ʹ��2���Ʊ�ʾ��k��ʾ���������еĳ���
llt D[22][1<<10][11];
int Dig[100];

inline int _f(int idx,int status){
    for(int i=idx;i<10;++i){
        if ( status & (1<<i) ) return ( status ^ (1<<i)) | ( 1 << idx );
    }
    return status | (1<<idx);
}

//pos��ʾ��ǰ�������λ��ֱ��0
//pre��ʾ֮ǰ�����
//lead��ʾ�Ƿ�Ϊǰ��0
//limit��ʾ�Ƿ�Ҫ�����Ͻ�
llt dfs(int pos,int pre,bool lead,bool limit){
    //���һ�£��Ƿ�Ϸ�
    if ( -1 == pos ) {
        int tmp = 0;
        while( pre ) tmp += (pre&1), pre>>=1;
        return tmp == K;
    }

    //���û�����ƣ�����ǰ���Ѿ����D����ֱ�ӷ���
    if ( !lead && !limit && -1 != D[pos][pre][K] ) return D[pos][pre][K];

    int last = limit ? Dig[pos] : 9;
    llt ans = 0;

    //�ݹ�����
    int tmp,npre;
    for(int i=0;i<=last;++i){
        if ( lead && 0==i ) ans += dfs(pos-1,pre,true,limit&&i==last);
        else ans += dfs(pos-1,_f(i,pre),false,limit&&i==last);
    }

    return lead||limit?ans:D[pos][pre][K]=ans;
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

    int nofkase;
    scanf("%d",&nofkase);
    llt a,b;
    for(int kase=1;kase<=nofkase;++kase){
        scanf("%lld%lld%d",&a,&b,&K);
        printf("Case #%d: %lld\n",kase,ddp(b)-ddp(a-1));
    }
    return 0;
}
