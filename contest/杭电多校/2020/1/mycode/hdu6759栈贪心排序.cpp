/**
    N个机器人从各自的起始位置做初速度为0的匀加速直线运动
    问在全过程中，单独领先的Robot一共有多少个
    对于任意两个Robot，如果位置和加速度都大，则显然小的无需考虑
    考虑i和j两个robot，假设i初始落在后面，则超过的时间(的平方)需要大于2(pj-pi)/(ai-aj)，记作tij
    对于任意3个robot，设为i、j、k，位置依次是pi<pj<pk，加速度为ai>aj>ak
    如果tij<=tjk，则j是没有用的
    考虑最后仍然留在栈中的Robot，令栈顶的3个从内到外依次是i、j、k，
    如果不考虑一模一样的，则k一定领先过，而j一定超过过k，且在i超过j之前，所以j也一定领先过
    以此类推，栈里的robot全部都领先过
    最后去重
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long llt;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

int const SIZE = 50000+10;

struct _t{
    llt p;//起始位置
    llt a;//加速度
}A[SIZE],Stack[SIZE];

bool operator < (const _t&lhs,const _t&rhs){
    return lhs.p < rhs.p || (lhs.p==rhs.p&&lhs.a<rhs.a);
}

bool operator == (const _t&lhs,const _t&rhs){
    return lhs.p==rhs.p&&lhs.a==rhs.a;
}

//比较3个robot，ijk，看是否tij<=tjk
bool f(const _t&i, const _t&j, const _t&k){
    //计算tij
    llt pij = j.p - i.p;
    llt aij = i.a - j.a;
    //计算tjk
    llt pjk = k.p - j.p;
    llt ajk = j.a - k.a;
    return pij * ajk <= aij * pjk;
}

set<_t> Set;
int main(){
    //freopen("1.txt","r",stdin);
    
    int nofkase = getUnsigned();
    while(nofkase--){
        Set.clear();

        int n = getUnsigned();
        for(int i=0;i<n;++i)A[i].p=getUnsigned(),A[i].a=getUnsigned();
        sort(A,A+n);

        int top = 0;
        Stack[top++] = A[0];
        for(int i=1;i<n;++i){
            //记录有相等的机器人
            if(A[i]==A[i-1]) Set.insert(A[i]);
            //如果栈内的加速度也小，直接出栈，不用考虑
            while(top>0&&Stack[top-1].a<=A[i].a) --top;
            //中间的肯定没用，出栈
            while(top>1&&f(Stack[top-2],Stack[top-1],A[i])) --top;
            //入栈
            Stack[top++] = A[i];
        }

        //检查答案
        int ans = 0;
        for(int i=0;i<top;++i)if(Set.end()==Set.find(Stack[i]))++ans;
        printf("%d\n",ans);
    }
    return 0;
}
