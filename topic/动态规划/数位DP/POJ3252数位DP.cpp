/*
    表示成二进制以后，0比1多认为是合法的
    问[s,e]之间有多少个数是合法的
*/

#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

typedef long long llt;

//Dij：i表示长度，j表示0与1的数量之差加32
llt D[40][70];
int Dig[100];

//pos表示当前处理的数位，直到0
//pre表示之前的0与1的数量之差加32
//lead表示是否前导0
//limit表示是否要限制上界
llt dfs(int pos,int pre,bool lead,bool limit){
    //检查一下，是否合法
    if ( -1 == pos ) return pre >= 32;

    //如果没有限制，而且前面已经求出D，则直接返回
    if ( !limit && !lead && -1 != D[pos][pre] ) return D[pos][pre];

    int last = limit ? Dig[pos] : 1;
    llt ans = 0;

    //递归搜索
    for(int i=0;i<=last;++i){
        if ( lead && 0==i ) ans += dfs(pos-1,pre,true,limit&&(i==Dig[pos]));
        else ans += dfs(pos-1,pre+(0==i?1:-1),false,limit&&(i==Dig[pos]));
    }

    return limit||lead?ans:D[pos][pre]=ans;
}

//求[1,n]满足条件的数有多少个
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
