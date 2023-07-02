/**
 * 给定数组A，取值范围在{0,1,2}
 * 给定字符串S，取值范围为{'M', 'E', 'X'}
 * 现在要求求出所有的和: mex({Ai, Aj, Ak|SiSjSk="MEX"})
 * 注意到mex的取值范围是有限的，局限于[0,3]，因此大量的mex(AiAjAk)函数值是相等的
 * 于是可以统计数量，再相乘求和。显然以j为枚举对象是最合适的
 * 对每一个Aj当Sj=='E'，假设Aj==0，则{AiAjAk}=={000}的数量为m0*x0
 * 其中m0表示j之前Ai==0且Si=='M'的数量,x0表示j之后Ak==0且Sk=='X'的数量
 * 此时对答案的贡献为: 1*m0*x0
 * 同理有{001}对答案的贡献为: 2*m0*x1
 * ...
 * 一共有27种情况。
 * 至于数量用前缀和、后缀和很容易求出
 */
#include <bits/stdc++.h>
using namespace std;

using llt = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using int128 = __int128_t;

int N;
vi A;
string S;

llt proc(){
    vi mcnt[3], xcnt[3];
    for(auto & v : mcnt) v.assign(N, 0);
    for(auto & v : xcnt) v.assign(N, 0);

    mcnt[0][0] = mcnt[1][0] = mcnt[2][0] = 0;
    if(S[0] == 'M') ++mcnt[A[0]][0];

    for(int i=1;i<N;++i){
        mcnt[0][i] = mcnt[0][i - 1];
        mcnt[1][i] = mcnt[1][i - 1];
        mcnt[2][i] = mcnt[2][i - 1];
        if(S[i] == 'M') ++mcnt[A[i]][i];
    }

    xcnt[0][N-1] = xcnt[1][N-1] = xcnt[2][N-1];
    if(S[N-1] == 'X') ++xcnt[A[N-1]][N-1];

    for(int i=N-2;i>=0;--i){
        xcnt[0][i] = xcnt[0][i + 1];
        xcnt[1][i] = xcnt[1][i + 1];
        xcnt[2][i] = xcnt[2][i + 1];
        if(S[i] == 'X') ++xcnt[A[i]][i];
    }

    llt ans = 0;
    for(int i=1;i<N-1;++i){
        if(S[i] != 'E') continue;

        switch(A[i]){
            case 0:{
                ans += mcnt[0][i - 1] * (xcnt[0][i + 1] + 2LL * xcnt[1][i + 1] + xcnt[2][i + 1]);
                ans += mcnt[1][i - 1] * (2LL * xcnt[0][i + 1] + 2LL * xcnt[1][i + 1] + 3LL * xcnt[2][i + 1]);
                ans += mcnt[2][i - 1] * (xcnt[0][i + 1] + 3LL * xcnt[1][i + 1] + xcnt[2][i + 1]);
            }break;
            case 1:{
                ans += mcnt[0][i - 1] * (2LL * xcnt[0][i + 1] + 2LL * xcnt[1][i + 1] + 3LL * xcnt[2][i + 1]);
                ans += mcnt[1][i - 1] * (2LL * xcnt[0][i + 1]);
                ans += mcnt[2][i - 1] * (3LL * xcnt[0][i + 1]);
            }break;
            case 2:{
                ans += mcnt[0][i - 1] * (xcnt[0][i + 1] + 3LL * xcnt[1][i + 1] + xcnt[2][i + 1]);
                ans += mcnt[1][i - 1] * (3LL * xcnt[0][i + 1]);
                ans += mcnt[2][i - 1] * (1LL * xcnt[0][i + 1]);
            }break;
            default: throw runtime_error("XX");
        }
    }
    return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    A.assign(N, 0);
    for(auto & i : A) cin >> i;
    cin >> S;
    cout << proc() << endl;
    return 0;
}