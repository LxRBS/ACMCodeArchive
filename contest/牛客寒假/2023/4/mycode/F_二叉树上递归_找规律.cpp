/**
 * 给一个K表示一共有2^K个节点，然后说了一些跟lowbit有关的话。
 * 本质上就是建了一个二叉排序树，节点从1到2^K，其中2^K做跟，其他节点构成一个满二叉树
 * 给定X，问X在先中后序遍历的顺序。
 * 二叉树其实非常有规律，直接递归即可
 * 首先对于中序遍历，答案就是X
 * 对于先序遍历，维护一个当前数，对当前节点 cur, 如果 X == cur， 那就是当前数
 * 如果 X < cur， 那就要去左儿子，且当前数加1
 * 如果 X > cur， 那就要去右儿子，根节点及其做儿子所有节点数都要加上
 * 对于后序遍历，如果 X == cur，答案是当前数加上左右儿子的节点数量
 * 如果 X < cur，就要去左儿子，当前数不变
 * 否则，去右儿子，当前数加上左儿子的节点数量。
 * 在当前节点，如何获取左右儿子的值，以及左右儿子的节点数量，恰好可以使用lowbit完成。
 * 不过也可以根据当前深度与K的关系，计算得出。
 */
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)
 
using llt = long long; 
llt getInt(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}
 
	llt ret = (llt)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10LL + (llt)(ch-'0');
	return sgn ? ret : -ret;
}

using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vpii = vector<pii>;

int Q;
int K;
llt X;

llt dfsQian(int curdepth, llt cur, llt ans){
    if(cur == X){
        return ans;
    }    

    if(X < cur){
        auto sn = cur - (1LL << K - 1 - curdepth);
		return dfsQian(curdepth + 1, sn, ans + 1);
    }

    auto sn = cur + (1LL << K - 1 - curdepth);
	return dfsQian(curdepth + 1, sn, ans + (1LL << K - curdepth));
}

llt dfsHou(int curdepth, llt cur, llt ans){
    if(cur == X){
        auto cnt = 1LL << K - curdepth + 1;
        return ans + cnt - 1;
    }
    if(X < cur){
        auto sn = cur - (1LL << K - 1 - curdepth);
        return dfsHou(curdepth + 1, sn, ans);
    }
    auto sn = cur + (1LL << K - 1 - curdepth);
    return dfsHou(curdepth + 1, sn, ans - 1 + (1LL << K - curdepth));
}

void proc(){
    if(0 == K) return (void)printf("1 1 1\n");

    if((1LL << K) == X){
        printf("1 %lld %lld\n", X, X);   
        return;  
    }

    auto qian = dfsQian(0, 1LL<<K, 0LL);
    auto zhong = X;
    auto hou = dfsHou(0, 1LL<<K, 0LL);
	
    printf("%lld %lld %lld\n", qian + 1, zhong, hou);
    return;
}


int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif 
    // ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    K = getInt(); Q = getInt();
    for(int q=1;q<=Q;++q){
        X = getInt();
        proc();
    }
    return 0;
}