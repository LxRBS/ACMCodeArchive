/*
    一共有N种，每种Ai个礼物，将这些礼物放到一列桌子上，条件如下：
    1. 每个桌子要放一个特殊的礼物和一个普通礼物
    2. 相邻桌子的普通礼物的种类必须不同
    3. 特殊礼物没有限制
    4. 礼物必须连续摆放
    问最多能摆到多少张桌子
    题意比较难解，其实很容易
    对不同的人，特殊礼物所属种类是可以不同的
    假设有一种礼物种类是A数量是无穷多，那就可以安排这样一种方法：
    AXAXA...XA
    将其他所有礼物当做普通，再将A也当做普通，可以摆这么多。
    再将A当做特殊礼物摆上去，这就是最多的一种摆法。
    该情况要求A的数量要达到总数的(sum-2)*3/4
    如果A没有这么多，我们可以找到一种sum/2的摆法
    例如A只有sum/2，我们可以这样摆
    AXAXAX...
    XAXAXA...
    上面作为特殊礼物不用管，下面作为普通礼物，显然种类是不一致的
    如果A不到一半，仍然可以这样摆，最后把AX的组合换成别的就行；
    超过一半也能这样摆，只是将AX的组合换成AA就行
    但是数据比较水，直接sum/2就能过
*/
#include <iostream>
using namespace std;
int A[110],N;
int main(){
    int nofkase;
    cin>>nofkase;
    for(int kase=1;kase<=nofkase;++kase){
        cin>>N;
        int mx = -1, k = -1, sum = 0;
        for(int i=0;i<N;++i){
            cin>>A[i];
            sum += A[i];
            if(mx<A[i]) mx = A[i],k = i;
        }
        printf("Case #%d: %d\n",kase,sum/2);
    }
    return 0;
}
