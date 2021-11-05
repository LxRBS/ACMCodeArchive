/*
    含有4或者62的数是不吉利的
    问[s,e]之间吉利的数字有多少个
*/

#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

typedef long long llt;

//Dij表示长度为i的前一位为j的满足条件的数
llt D[7][10];
int Dig[100];

//pos表示当前处理的数位，直到0
//pre表示前一位
//limit表示搜索的上界
llt dfs(int pos,int pre,bool limit){
    if ( -1 == pos ) return 1;//能够搜索到这里，说明前面的每一个条件都满足，返回1个

    //如果没有限制，而且前面已经求出D，则直接返回
    if ( !limit && -1 != D[pos][pre] ) return D[pos][pre];

    int last = limit ? Dig[pos] : 9;
    llt ans = 0;

    //递归搜索
    for(int i=0;i<=last;++i){
        if ( 4==i || (2==i&&6==pre) ) continue;

        ans += dfs(pos-1,i,limit&&(i==Dig[pos]));
    }

    return 0==limit?D[pos][pre]=ans:ans;
}

//求[1,n]满足条件的数有多少个
llt ddp(int n){
    int k = 0;
    while(n){
        Dig[k++] = n % 10;
        n /= 10;
    }
    return dfs(k-1,0,true);
}

int main(){
    //freopen("1.txt","r",stdin);

    memset(D,-1,sizeof(D));
    int a,b;
    while( scanf("%d%d",&a,&b),a+b ){
        printf("%lld\n",ddp(b)-ddp(a-1));
    }
    return 0;
}
