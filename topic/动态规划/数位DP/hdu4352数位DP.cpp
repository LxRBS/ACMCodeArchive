/*
    条件为最长严格递增子序列长度等于k
    问[s,e]之间符合条件的数
*/

#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

typedef long long llt;

int K;

//Dijk：i表示长度，j表示对应数字的出现情况，使用2进制表示，k表示上升子序列的长度
llt D[22][1<<10][11];
int Dig[100];

inline int _f(int idx,int status){
    for(int i=idx;i<10;++i){
        if ( status & (1<<i) ) return ( status ^ (1<<i)) | ( 1 << idx );
    }
    return status | (1<<idx);
}

//pos表示当前处理的数位，直到0
//pre表示之前的情况
//lead表示是否为前导0
//limit表示是否要限制上界
llt dfs(int pos,int pre,bool lead,bool limit){
    //检查一下，是否合法
    if ( -1 == pos ) {
        int tmp = 0;
        while( pre ) tmp += (pre&1), pre>>=1;
        return tmp == K;
    }

    //如果没有限制，而且前面已经求出D，则直接返回
    if ( !lead && !limit && -1 != D[pos][pre][K] ) return D[pos][pre][K];

    int last = limit ? Dig[pos] : 9;
    llt ans = 0;

    //递归搜索
    int tmp,npre;
    for(int i=0;i<=last;++i){
        if ( lead && 0==i ) ans += dfs(pos-1,pre,true,limit&&i==last);
        else ans += dfs(pos-1,_f(i,pre),false,limit&&i==last);
    }

    return lead||limit?ans:D[pos][pre][K]=ans;
}

//求[1,n]满足条件的数有多少个
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
