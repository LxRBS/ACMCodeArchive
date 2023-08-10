/**
 * 给定一个大整数，问通过不限次数的四舍五入，能够得到的最大的数是多少。
 * 显然贪心，找到第一个符合条件的位置进位即可，注意条件有2种
 * 1. 该位 >= 5，可以直接进位
 * 2. 从该位开始有若干个4，且紧接着一个>=5，根据规则该位也能进位
 * 判断第二个条件时随手写了个平方级别的代码，赛后被T了
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

string & proc(){
    N = S.length();
    int k = 0;
    while(1){
        if(S[k] >= '5'){
            fill(S.begin() + k, S.end(), '0');
            if(k > 0){
                assert(S[k - 1] != '9');
                S[k - 1] += 1;
                break;
            }
            S.assign(N + 1, '0');
            S[0] = '1';   
            break;         
        }else if(S[k] == '4'){
            int c = 0;
            while(k + c < N and S[k + c] == '4') ++c;     
            if(k + c == N) break;
            if(S[k + c] >= '5'){
                fill(S.begin() + k, S.end(), '0');
                if(k > 0){
                    assert(S[k - 1] != '9');
                    S[k - 1] += 1;
                    break;
                }
                S.assign(N + 1, '0');
                S[0] = '1';   
                break;  
            }
            k += c;
        }else{
            ++k;
        }

        if(k == N) break;
    }
    return S;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int nofkase; cin >> nofkase;
    while(nofkase--){
        cin >> S;
        cout << proc() << endl;
    }
    return 0;
}
