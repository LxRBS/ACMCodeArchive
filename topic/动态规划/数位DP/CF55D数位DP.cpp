/*
    如果一个数能够被自己各个位上的数字整除，就是美丽的
    问[s,e]之间美丽的数字有多少个
*/

#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

typedef long long llt;

//Dijk：i表示长度，j表示已经出现过的数字，k表示当前的数字值
llt D[20][1<<8][2600];
int Dig[100];

//pos表示当前处理的数位，直到0
//pre表示之前已经出现过的数字，用二进制表示表示
//sum表示当前的数字值
//limit表示搜索的上界
llt dfs(int pos,int pre,int sum,bool limit){
    //检查一下，sum是否能整除所有出现过的数位
    if ( -1 == pos ) {
        for(int i=2;i<=9;++i){
            if ( (pre&(1<<(i-2))) && (0!=sum%i) ){
                return 0;
            }
        }
        return 1;
    }

    //如果没有限制，而且前面已经求出D，则直接返回
    if ( !limit && -1 != D[pos][pre][sum] ) return D[pos][pre][sum];

    int last = limit ? Dig[pos] : 9;
    llt ans = 0;

    //递归搜索
    for(int i=0;i<=last;++i){
        ans += dfs(pos-1,i<2?pre:pre|(1<<(i-2)),(sum*10+i)%2520,limit&&(i==Dig[pos]));
    }

    return limit?ans:D[pos][pre][sum]=ans;
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


    llt a,b;
    while(nofkase--){
        scanf("%I64d%I64d",&a,&b);
        printf("%I64d\n",ddp(b)-ddp(a-1));
    }
    return 0;
}