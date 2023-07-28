/**
 * 给定雪花图求参数
 * 注意到雪花图的点的不同度数只有2或者3种不同的值且必然有1
 * 除开1以后，如果只有1个值，记作d，则 x = d, y = x - 1
 * 如果还有两个不同的度数，则只有1个点的那个度数必然就是x, y = x - 1
 */
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

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

int N, M;
vvi G;

void proc3(const map<int, vi> & m){
    int one = -1;
    int x = -1;
    int y = -1;
    for(const auto & p : m){
        if(1 == p.first){
            one = p.second.size();
        }else if(p.second.size() == 1){
            x = p.first;
        }else{
            y = p.first - 1;
        }
    }     
    assert(-1 != x and -1 != y and -1 != one);
    return (void)(cout << x << " " << y << endl);
}

void proc2(const map<int, vi> & m){
    int one = -1;
    int x = -1;
    int y = -1;
    for(const auto & p : m){
        if(1 == p.first){
            one = p.second.size();
        }else{
            x = p.first;
            y = x - 1;
        }
    }
    assert(-1 != x and -1 != y and -1 != one);
    return (void)(cout << x << " " << y << endl);
}

void proc(){
    map<int, vi> d;
    for(int i=1;i<=N;++i){
        d[G[i].size()].push_back(i);
    }

    assert(d.size() <= 3);
    if(3 == d.size()){
        return proc3(d);
    }
    assert(2 == d.size());
    return proc2(d);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    
    int nofkase; cin >> nofkase;
    while(nofkase--){
        cin >> N >> M;
        G.assign(N + 1, vi());
        for(int a,b,i=0;i<M;++i){
            cin >> a >> b;
            G[a].push_back(b);
            G[b].push_back(a);
        }
        proc();
    }
    return 0;
}

