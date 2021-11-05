/*
    问[s,e]之间含有49的数字有多少个
*/

#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

typedef long long llt;

//Dijk表示长度为i的前一位为j的满足条件的数，k表示前面的数是否已经合法
llt D[20][10][2];
int Dig[100];

//pos表示当前处理的数位，直到0
//pre表示前一位
//status表示状态，只取1或0
//limit表示搜索的上界
llt dfs(int pos,int pre,int status,bool limit){
    if ( -1 == pos ) return status;//能够搜索到这里，只看status即可

    //如果没有限制，而且前面已经求出D，则直接返回
    if ( !limit && -1 != D[pos][pre][status] ) return D[pos][pre][status];

    int last = limit ? Dig[pos] : 9;
    llt ans = 0;

    //递归搜索
    for(int i=0;i<=last;++i){
        ans += dfs(pos-1,i,status||(4==pre&&9==i),limit&&(i==Dig[pos]));
    }

    return 0==limit?D[pos][pre][status]=ans:ans;
}

//求[1,n]满足条件的数有多少个
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