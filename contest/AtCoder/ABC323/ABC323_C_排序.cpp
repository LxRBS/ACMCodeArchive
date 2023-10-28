/**
 * M个任务N个人，每个任务对应一个分数
 * 第i个人已经完成了若干任务，即已经获得了若干分
 * 问：对每个人，最少再完成几个任务可以保证其分数最高
 * 在问i的时候，其他人的任务维持原样不变
 * 保证有解
 * 对每个人，将未完成的任务按分数从高到低排序，再处理即可
 * 但如果将所有任务一起排序，则T
 * 按题意，这个数量级是有可能出现的
 */
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

int N, M;
vector<string> S;
vector<int> A;
vector<int> Total;
int MMax;
int MCnt;

int proc(int idx){
    if(Total[idx] == MMax) return 1 == MCnt ? 0 : 1;

    const auto & s = S[idx];
    vector<int> vec;vec.reserve(M);
    for(int i=0;i<M;++i)if(s[i] == 'x')vec.push_back(i);
    sort(vec.begin(), vec.end(), [&](int x, int y){
        assert(s[x] == 'x' and s[y] == 'x');
        if(A[x] != A[y]) return A[x] > A[y];
        return x < y;
    });

    int ans = 0;
    int tmp = Total[idx];
    for(auto i : vec){
        tmp += A[i];
        ++ans;
        if(tmp > MMax) break;
    }
    assert(tmp > MMax);
    return ans;
}

void proc(){
    Total.assign(N, 0);
    for(int i=0;i<N;++i){
        Total[i] = i + 1;
        for(int j=0;j<M;++j){
            if(S[i][j] == 'o'){
                Total[i] += A[j];
            }
        }
    }

    MMax = *max_element(Total.begin(), Total.end());

    MCnt = 0;
    for(auto i : Total)if(i == MMax) ++MCnt;
    assert(MCnt >= 1);

    for(int i=0;i<N;++i){
        cout << proc(i) << endl;
    }
    return;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M;
    A.assign(M, 0);
    for(auto & i : A) cin >> i;
    S.assign(N, "");
    for(auto & s : S) cin >> s;
    proc();
    return 0;
}