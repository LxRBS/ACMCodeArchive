/**
 * 给定5个区间，以及每个区间对应的分数
 * 再给定N个数的数组。现在可以对数组做任意平移，问最大得分是多少。
 * 贪心。
 * 最大得分一定是某个Ai在某个区间的临界点取到。
 * 因此对每一个Ai，求其到每个区间的临界点移动距离diff，然后将整个数组移动diff，看数组的得分即可。
 * 移动数组，等价于移动边界，因此O(4)即可。
 * 另外无需双向移动，只需移动到最近的即可。
 * 统计数量需要二分，使用STL即可。但是要注意开闭边界与lower_bound和upper_bound的配合。
 * O(4NlogN)
 */
#include <bits/stdc++.h>
using namespace std;
 
char *__abc147, *__xyz258, __ma369[1000000];
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
int const SIZE = 23;
#else
int const SIZE = 110;
#endif

using llt = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vpii = vector<pii>;
using vll = vector<llt>;

llt const MOD = 998244353LL;
inline llt add(llt a, llt b){return (a+b)%MOD;}

int N;
llt A, B, C, D;
vll W;
llt V[6];
llt Origin;

inline int get(llt wi){
    if(wi < A) return 1;
    if(wi < B) return 2;
    if(wi < C) return 3;
    if(wi <= D) return 4;
    return 5;
}

/// W整体往左移动diff，diff始终为正
llt procMoveW2Left(llt diff){
    assert(diff > 0);
    // auto p1 = equal_range(W.begin(), W.end(), A+diff);
    auto t1 = lower_bound(W.begin(), W.end(), A+diff) - W.begin();
    auto ret = (llt)t1 * V[1];

    // auto p2 = equal_range(W.begin(), W.end(), B+diff);
    auto t2 = lower_bound(W.begin(), W.end(), B+diff) - W.begin();
    ret += (llt)(t2-t1) * V[2];

    // auto p3 = equal_range(W.begin(), W.end(), C+diff);
    auto t3 = lower_bound(W.begin(), W.end(), C+diff) - W.begin();
    ret += (llt)(t3-t2) * V[3];

    // auto p4 = equal_range(W.begin(), W.end(), D+diff);
    auto t4 = upper_bound(W.begin(), W.end(), D+diff) - W.begin();
    ret += (llt)(t4-t3) * V[4];
    ret += (llt)(N - t4) * V[5];
    return ret;
}

llt procMoveW2Right(llt diff){
    assert(diff > 0);
    auto t1 = lower_bound(W.begin(), W.end(), A-diff) - W.begin();
    auto ret = (llt)t1 * V[1];

    // auto p2 = equal_range(W.begin(), W.end(), B+diff);
    auto t2 = lower_bound(W.begin(), W.end(), B-diff) - W.begin();
    ret += (llt)(t2-t1) * V[2];

    // auto p3 = equal_range(W.begin(), W.end(), C+diff);
    auto t3 = lower_bound(W.begin(), W.end(), C-diff) - W.begin();
    ret += (llt)(t3-t2) * V[3];

    // auto p4 = equal_range(W.begin(), W.end(), D+diff);
    auto t4 = upper_bound(W.begin(), W.end(), D-diff) - W.begin();
    ret += (llt)(t4-t3) * V[4];
    ret += (llt)(N - t4) * V[5];
    return ret;
}

llt proc(int index, int origin_pos, int target_pos){
    if(origin_pos == target_pos) return Origin;

    if(1 == target_pos){
        auto diff = W[index] - A + 1;
        auto tmp = procMoveW2Left(diff);
        return tmp;
    }

    if(2 == target_pos){
        if(origin_pos < target_pos){
            auto diff = A - W[index];
            auto tmp = procMoveW2Right(diff);
            return tmp;
        }else{
            auto diff = W[index] - B + 1;
            auto tmp = procMoveW2Left(diff);
            return tmp;
        }
    }

    if(3 == target_pos){
        if(origin_pos < target_pos){
            auto diff = B - W[index];
            auto tmp = procMoveW2Right(diff);
            return tmp;
        }else{
            auto diff = W[index] - C + 1;
            auto tmp = procMoveW2Left(diff);
            return tmp;
        }
    }

    if(4 == target_pos){
        if(origin_pos < target_pos){
            auto diff = C - W[index];
            auto tmp = procMoveW2Right(diff);
            return tmp;
        }else{
            auto diff = W[index] - D;
            auto tmp = procMoveW2Left(diff);
            return tmp;
        }
    }

    if(5 == target_pos){
        auto diff = D + 1 - W[index];
        auto tmp = procMoveW2Right(diff);
        return tmp;
    }

    assert(0);
    return 0;
}

llt proc(int index){
    int pos = get(W[index]);
    llt ans = proc(index, pos, 1);
    // printf("(%d, origin = %d, target = %d): %lld\n", index, pos, 1, ans);
    for(int i=2;i<=5;++i){
        auto tmp = proc(index, pos, i);
        ans = max(ans, tmp);
        // printf("(%d, origin = %d, target = %d): %lld\n", index, pos, i, tmp);
    }
    return ans;
}

llt proc(){
    auto tmp = *max_element(V+1, V+6);
    if(tmp == V[1] || tmp == V[5]){
        return tmp * (llt)N;
    }

    sort(W.begin(), W.end());

    Origin = 0;
    for(int i=0;i<N;++i) Origin += V[get(W[i])];
    
    llt ans = Origin;
    for(int i=0;i<N;++i){
        auto tmp = proc(i);
        ans = max(ans, tmp);
        // printf("%d: %lld\n", i, tmp);
    }
    return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getInt();
    while(nofkase--){
        W.assign(N = getInt(), 0);
        for(auto & i : W) i = getInt();
        A = getInt();
        B = getInt();
        C = getInt();
        D = getInt();
        for(int i=1;i<=5;++i) V[i] = getInt();
        printf("%lld\n", proc());
    }
    return 0;
}


