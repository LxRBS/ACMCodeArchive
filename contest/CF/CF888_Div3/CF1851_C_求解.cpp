/**
 * 给定一个N长度的数组A，以及一个整数K。
 * 问能否选出一个子序列，满足：
 * 1. 以1开头，以N结尾
 * 2. 长度是K的整数倍
 * 3. 每相邻的K个为一组，且同组元素数值相同，不同组数值没有要求
 * 注意到子序列长度没有要求，实际上就是：
 * 1. 若 A1 == A[N]，只需要看A中有没有K个A1即可
 * 2. 若 A1 != A[N]，只需要选两段，前面K个均为A1，后面K个均为A[N]即可
 */
#include <bits/stdc++.h>
using namespace std;

using llt = long long;
using vi = vector<int>;
using vvi = vector<vi>;

int N, K;
vi A;

bool f(){
    int c = 0;
    for(auto i : A)if(i == A[0])if(++c==K)return true;
    return false;
}

bool proc(){
    if(A[0] == A[N - 1]) return f();
    
    int c = 0;
    int k = 0;
    while(k < N and c < K){
        if(A[k] == A[0]){
            ++c;
        }
        ++k;
    }
    if(c != K) return false;

    int z = 0;
    for(int i=k;i<N;++i){
        if(A[i] == A[N - 1]){
            if(++z == K) return true;
        }
    }
    return false;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int nofkase; cin >> nofkase;
    while(nofkase--){
        cin >> N >> K;
        A.assign(N, 0);
        for(auto & i : A) cin >> i;
        cout << (proc() ? "YES" : "NO") << endl;
    }
    return 0;
}


