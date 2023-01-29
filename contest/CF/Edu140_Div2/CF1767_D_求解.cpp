/**
 * 2^N个队伍参加淘汰赛。第一轮：1vs2,3vs4,...
 * 第二轮由相邻的胜者比赛，如此反复。
 * 第i个队伍的能力是pi。所有队伍的能力是1~2^N的排列。
 * 给定一个字符串s，用来表示结果。
 * 如果si是0，则第i轮能力值低的队伍获胜
 * 如果si是1，则第i轮能力值高的队伍获胜
 * 在给定s的情况下，求所有可能获胜的x
 * 如果s1是0，则2^N要被排除，即最大的一个数要被排除
 * 如果s2也是0，则2^N-1和2&N-2要被排除，即剩下的最大的2个数要被排除
 * 如果s3也是0，则剩下的最大的4个数要被排除。
 * 以此类推。
 * 如果结合si是1的情况，那就要排除最小的数。
 * 用一个flag维护当时还有可能获胜的队伍，然后用c0和c1维护之前0和1的数量
 * 第i轮如果是1，则需要排除最小的2^c1个队伍
 * 反之，需要排除最大的2^c0个队伍。
 * O(N*2^N)，N是18。
 */
#include <bits/stdc++.h>
using namespace std;
 
char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)
 
int getInt(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}
 
	int ret = (int)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}
 
#ifndef ONLINE_JUDGE
int const SIZE = 13;
#else
int const SIZE = 35000;
#endif

using llt = long long;
using vi = vector<int>;
using si = set<int>;
using vvi = vector<vi>;

char S[22];
int N;

void proc(vi & flag, int c, int t){
    int a = 1 << c;
    if(t)for(int i=(1<<N);i>=1;--i){
        if(0 == flag[i]) continue;
        flag[i] = 0;
        if(0 == --a) return;        
    }else for(int i=1;i<=(1<<N);++i){
        if(0 == flag[i]) continue;
        flag[i] = 0;
        if(0 == --a) return;
    }
    return;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> N >> S + 1;
    vi flag((1<<N)|1, 1); flag[0] = 1;
    int cnt0 = 0, cnt1 = 0;
    for(int i=1;i<=N;++i){
        if(S[i] == '0'){
            proc(flag, cnt0, 1);
            ++cnt0;
        }else{
            proc(flag, cnt1, 0);
            ++cnt1;
        }
    }
    for(int i=1;i<=(1<<N);++i)if(flag[i])printf("%d ", i);
    printf("\n");
    return 0;
}