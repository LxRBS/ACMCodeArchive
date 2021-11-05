/*
    条件为每一个奇数数字有偶数个，每一个偶数数字有奇数个
    问[s,e]之间符合条件的数
*/

#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

typedef long long llt;
typedef unsigned long long ull;

int const POW_OF_3[] = {
    1,3,9,27,81,81*3,81*9,81*27,81*81,81*81*3
};

//Dij：i表示长度，j表示对应数字的出现情况，使用3进制表示，0表示没有，1表示奇数，2表示偶数
llt D[22][59100];
int Dig[100];

//pos表示当前处理的数位，直到0
//pre表示之前的情况
//lead表示是否为前导0
//limit表示是否要限制上界
llt dfs(int pos,int pre,bool lead,bool limit){
    //检查一下，是否合法
    if ( -1 == pos ) {
        //pre%3如果是0就不必讨论，否则i为奇数时余数必须是2，i为偶数时余数必须是1
        for(int i=0;pre;++i,pre/=3){
            if ( ( pre % 3 ) && ( ( pre % 3 ) & 1 ) == ( i & 1 )  ){
                return 0;
            }
        }
        return 1;
    }

    //如果没有限制，而且前面已经求出D，则直接返回
    if ( !lead && !limit && -1 != D[pos][pre] ) return D[pos][pre];

    int last = limit ? Dig[pos] : 9;
    llt ans = 0;

    //递归搜索
    int tmp = 0, npre;
    for(int i=0;i<=last;++i){
        if ( lead && 0 == i ) ans += dfs(pos-1,pre,true,limit&&i==Dig[pos]);
        else {
            npre = pre;
            tmp = npre / POW_OF_3[i] % 3;
            npre -= tmp * POW_OF_3[i];
            if ( 2 == tmp ) tmp = 1;
            else tmp += 1;
            npre += tmp * POW_OF_3[i];
            ans += dfs(pos-1,npre,false,limit&&i==Dig[pos]);
        }
    }

    return lead||limit?ans:D[pos][pre]=ans;
}

//求[1,n]满足条件的数有多少个
llt ddp(ull n){
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

    int kase;
    scanf("%d",&kase);
    ull a,b;
    while(kase--){
        scanf("%llu%llu",&a,&b);
        printf("%lld\n",ddp(b)-ddp(a-1));
    }
    return 0;
}
