/*
    条件为含有13并能被13整除的数
    问[s,e]之间有多少个数是符合条件的
*/

#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

typedef long long llt;

//Dijkw：i表示长度，j表示前一位，k表示余数，w表示是否出现过13
llt D[40][10][13][2];
int Dig[100];

//pos表示当前处理的数位，直到0
//pre表示之前的位
//left表示当前对13的余数
//status为是否出现过13
//limit表示是否要限制上界
llt dfs(int pos,int pre,int left,bool status,bool limit){
    //检查一下，是否合法
    if ( -1 == pos ) return status&&0==left?1:0;

    //如果没有限制，而且前面已经求出D，则直接返回
    if ( !limit && -1 != D[pos][pre][left][status] ) return D[pos][pre][left][status];

    int last = limit ? Dig[pos] : 9;
    llt ans = 0;

    //递归搜索
    for(int i=0;i<=last;++i){
        ans += dfs(pos-1,i,(left*10+i)%13,status||(1==pre&&3==i),limit&&i==last);
    }

    return limit?ans:D[pos][pre][left][status]=ans;
}

//求[1,n]满足条件的数有多少个
llt ddp(llt n){
    int k = 0;
    while(n){
        Dig[k++] = n % 10;
        n /= 10;
    }
    llt tmp = dfs(k-1,0,0,false,true);
    return tmp;
}

int main(){
    //freopen("1.txt","r",stdin);

    memset(D,-1,sizeof(D));

    llt a;
    while(1 == scanf("%I64d",&a)){
        printf("%I64d\n",ddp(a));
    }
    return 0;
}
