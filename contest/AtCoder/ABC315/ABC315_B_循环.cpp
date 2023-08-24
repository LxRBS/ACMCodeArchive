/**
 * 给定每个月的天数，问一年的正中间是几月几号
 * 保证总天数是奇数。
 * 循环一下即可
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
vi A;

void proc(){
    int s = accumulate(A.begin(), A.end(), 0);
    s /= 2;
    s += 1;
    for(int i=0;;++i){
        if(A[i] < s){
            s -= A[i];
        }else{
            cout << i + 1 << " " << s <<endl;
            break;
        }
    }
    return;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    A.assign(N, 0);
    for(auto & i : A) cin >> i;
    proc();
    return 0;
}
