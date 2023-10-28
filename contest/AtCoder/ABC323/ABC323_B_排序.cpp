#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

int N;
vector<string> A;

void proc(){
    vector<int> a;
    for(int i=0;i<N;++i) a.push_back(i);
    sort(a.begin(), a.end(), [](int x, int y){
        int ax = 0, ay = 0;
        for(auto ch : A[x])if('o' == ch)++ax;
        for(auto ch : A[y])if('o' == ch)++ay;
        if(ax != ay) return ax > ay;
        return x < y;
    });
    for(auto i : a) cout << i + 1 << " ";
    cout << endl;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    A.assign(N, "");
    for(auto & s : A) cin >> s;
    proc();
    return 0;
}