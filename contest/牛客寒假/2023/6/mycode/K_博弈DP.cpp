/**
 * 初始给一个X。两个人轮流走棋，
 * 1 令 X = X / 2
 * 2 令 X += 1
 * 已经出现过的数不能走，只能走正整数，问先手胜负
 * 注意到没有减一操作，因此每一个1操作以后，左边一定都是可行的，而1操作能不能做，取决于当前是从哪里加上去的
 * 也就是说对于左边而言，一定存在一个左边界，从左边界到当前位置都是已经走过的点，而左边界之前都是没走过的点
 * 而对2操作而言，只需要设定右边界即可，因为右边界以上的数可不可行没有意义
 * 因此可以使用左右边界以及当前位置来表示状态，{left, now ,right}
 * 既然能表示状态，就可以使用DP
 * 每一次只有两种可能的操作，记忆化深搜即可
 * 不过存在一个剪枝，如果1操作不能做，只能走2操作，根据右边界的情况无须深搜，可以直接判定胜平负的结果。
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
int const SIZE = 1E6+10;
#endif

using _t = tuple<int, int, int>;
using mt = map<_t, int>;

int const DRAW = 0;
int const WIN = 1;
int const LOST = 2;

char Output[3][10] = {
	"draw", "ning", "red"
};

mt D;

int dp(const _t & t){
    auto it = D.find(t);
    if(it != D.end()) return it->second;
    it = D.insert(it, {t, LOST});

    auto left = get<0>(t);
    auto now = get<1>(t);
    auto right = get<2>(t);

    if(0 < now / 2 && now / 2 < left){
        auto tmp = now / 2;
        auto ret = dp({now / 2, now / 2, left});
        if(ret & LOST) return it->second = WIN;
        else if(ret == DRAW) it->second = DRAW;
    }else if(-1 != right){
        auto tmp = right - now;
        if(tmp & 1) return it->second = LOST;
        return it->second = WIN;
    }else{
        assert(-1 == right);
        return it->second = DRAW;
    }

    if(-1 == right || now + 1 < right){
        auto ret = dp({left, now + 1, right});
        if(ret & LOST) return it->second = WIN;
        else if(ret == DRAW) it->second = DRAW;
    }
    
    return it->second;
}


int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    D[{1, 1, -1}] = DRAW;
    int x;
    cin >> x;
    cout << Output[dp({x, x, -1})] << endl;
    return 0;
}