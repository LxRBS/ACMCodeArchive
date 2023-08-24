/**
 * 给一个长度为N的左右括号的字符串
 * 要求给出一个长度为2N的字符串，满足2个条件
 * 1. 该2N字符串是括号匹配的
 * 2. N字符串不是该2N串的子串
 * 只需要考虑"()()"与"(())"两种候选答案即可
 * 如果原串中有相邻字符相等的情况，就是用第一种，否则就使用第二种
 * 注意特判，样例中已给出。
 */
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

using Real = long double;
using llt = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;

#ifndef ONLINE_JUDGE
int const SZ = 34;
#else
int const SZ = 200000 + 12;
#endif

int N;
string S;
string T;

void procYes(){
    cout << "YES" << endl;
    for(int i=0;i<N;++i) cout << "()";
    cout << endl;
}

void proc(){
    bool b = false;
    N = S.length();
    for(int i=1;i<N;++i){
        if(S[i - 1] == S[i]){
            b = true; break;
        }
    }
    if(b){
        return (void)procYes();
    }
    if(2 == N){
        if("()" == S) return (void)(cout << "NO" << endl);
        return (void)(cout << "YES" << endl << "(())" << endl);
    }
    cout << "YES" << endl;
    for(int i=0;i<N;++i)cout<<'(';
    for(int i=0;i<N;++i)cout<<')';
    cout << endl;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int nofkase; cin >> nofkase;
    while(nofkase--){
        cin >> S;
        proc();
    }
    return 0;
}
