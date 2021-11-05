/*
    条件为相邻两个数字之差至少为2的正整数
    问[s,e]之间符合条件的数
*/

#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

typedef long long llt;

//Di：i表示长度，j表示最高位
llt D[15][11];
int Dig[100];

//pos表示当前处理的数位，直到0
//pre表示前一位的情况
//lead表示是否为前导0
//limit表示是否要限制上界
llt dfs(int pos,int pre,bool lead,bool limit){
    //检查一下，是否合法，本题搜到这里肯定合法
    if ( -1 == pos ) return 1;

    //如果没有限制，而且前面已经求出D，则直接返回
    if ( !lead && !limit && -1 != D[pos][pre] ) return D[pos][pre];

    int last = limit ? Dig[pos] : 9;
    llt ans = 0;

    //递归搜索
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

    llt a,b;
    for(;2==scanf("%lld%lld",&a,&b);){
        printf("%lld\n",ddp(b)-ddp(a-1));
    }
    return 0;
}
