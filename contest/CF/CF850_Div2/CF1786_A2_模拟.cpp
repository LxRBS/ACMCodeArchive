/**
 * 与A1版本一样，只是牌还有颜色，黑白交替。问发完N张牌
 * A和B各拿多少黑牌与白牌。仍然是模拟一下即可。
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
int const SIZE = 1E6+1;
#else
int const SIZE = 1E6+1;
#endif

using llt = long long;
using vll = vector<llt>;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vpii = vector<pii>;

llt const MOD = 998244353LL;

vi Ques;
vector<array<int, 4>> Ans;

void init(){    
    int const WHITE = 0;
    int const BLACK = 2;
    Ans.assign(SIZE,{0,0,0,0});

    int yan = 0;
    int o = 0;
    int ppp = -3;
    int c = 0;

    for(int i=1;i<SIZE;++i){        
        const auto & prv = Ans[i - 1];
        auto & now = Ans[i];
        now[0] = prv[0];
        now[1] = prv[1];
        now[2] = prv[2];
        now[3] = prv[3];
        ++now[o | yan];
        yan ^= BLACK;

        ++c;
        if(ppp + 4 == c){
            ppp = c;
            o ^= 1;
            c = 0;
        }
    }
    return;
}

// pii proc(int n){
//     auto k = (n - 1) / 4;
//     auto left = n - k * 4 - 1;
//     if(k & 1){
//         auto t = k - 1 >> 1;
//         auto second = 5 + t * 8;
//         auto first = 1 + t * 8;

//     }else{

//     }
// }

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    init();
    int nofkase = getInt();
    while(nofkase--){
        Ques.push_back(getInt());
    }
    for(auto i : Ques){
        printf("%d %d %d %d\n", Ans[i][0], Ans[i][2], Ans[i][1], Ans[i][3]);
    }
    return 0;
}