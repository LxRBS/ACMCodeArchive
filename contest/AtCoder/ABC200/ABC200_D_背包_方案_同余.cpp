/**
 * 给定数组A，要求从中选出两个不同的子序列，使得：
 * 两个子序列之和同模200，输出方案，或者输出No
 * 首先将Ai对200取模，记录每个模数对应的元素的位置
 * 如果存在某个模数，有多个元素，则已经找到答案，输出。
 * 由于N在200，因此模式之和在20100以内。做一个01背包，并且记录方案
 * 如果对某个i，D[N][i]与D[N][i+200k]均不为0，
 * 可知存在某个子序列使得和为i，且另外存在某个子序列使得和i+200k。
 * 找到对应的方案即可。
 * 又或者如果某个D[N][i]>=2，可知存在多个子序列使得和为i
 * 找到对应的方案输出即可。
 * 否则，输出No
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
int const SZ = 2E5+10;
#endif

int N;
vi A;
vvi D;
vector<vector<vi>> G;
map<int, vi> Value2Pos, Pos2Value;
pair<vi, vi> Ans;
int Total;

inline void output(vi & v){
    sort(v.begin(), v.end());
    cout << v.size();
    for(auto i : v) cout << " " << i;
    cout << endl;
}

inline void output(){
    assert(not Ans.first.empty() and not Ans.second.empty());
    cout << "Yes" << endl;
    output(Ans.first); output(Ans.second);
}

bool checkSingleValue(){
    for(const auto & p : Value2Pos){
        if(p.second.size() == 1) continue;
        Ans.first.clear();
        Ans.second.clear();
        Ans.first.push_back(p.second[0]);
        Ans.second.push_back(p.second[1]);
        return true;
    }
    return false;
}

void get(vi & vec, int anchor){
    for(int i=N;i>0;--i){
        const auto wi = A[i - 1];
        if(1 == G[i][anchor][0]){
            vec.push_back(Value2Pos[wi][0]);
            anchor -= wi;
        }else if(-1 == G[i][anchor][0]){
            
        }else{
            assert(0);
        }
    }
    return;
}

void proc(const vi & candi){
    assert(candi.size() >= 2);
    get(Ans.first, candi[0]); 
    get(Ans.second, candi[1]);
    output();
    return;
}

void proc(int anchor){
    get(Ans.first, anchor);
    vi & vec = Ans.second;
    for(int i=N;i>0;--i){
        const auto wi = A[i - 1];
        if(G[i][anchor].size() > 1){
            if(1 == G[i][anchor][1]){
                vec.push_back(Value2Pos[wi][0]);
                anchor -= wi;
            }else if(-1 == G[i][anchor][1]){
                
            }else{
                assert(0);
            }  
        }else{
            if(1 == G[i][anchor][0]){
                vec.push_back(Value2Pos[wi][0]);
                anchor -= wi;
            }else if(-1 == G[i][anchor][0]){
                
            }else{
                assert(0);
            }             
        }      
    }
    output();
}

void proc(){
    for(int i=0;i<N;++i){
        auto & j = A[i];        
        j %= 200;
        if(0 == j) j = 200;
        Value2Pos[j].push_back(i + 1);
    }

    if(checkSingleValue()) return (void)output();

    Total = accumulate(A.begin(), A.end(), 0);
    D.assign(N + 1, vi(Total + 1, 0));
    G.assign(N + 1, vvi(Total + 1, vi()));
    D[0][0] = 1;
    for(int i=1;i<=N;++i){
        const auto wi = A[i - 1];
        for(int v=Total;v>=0;--v){
            D[i][v] = D[i - 1][v];
            if(v >= wi) {
                D[i][v] += D[i - 1][v - wi]; 
                if(D[i - 1][v - wi]){
                    G[i][v].push_back(1);
                }
            }     
            if(D[i - 1][v]){
                G[i][v].push_back(-1);
            }
            
        }
    }

    for(int i=1;i<=min(200, Total);++i){
        vi candi;
        for(int j=i;j<=Total;j+=200){
            if(D[N][j]){
                candi.push_back(j);
                if(candi.size() >= 2){
                    return (void)proc(candi);
                }
            }
        }
    }

    for(int i=1;i<=Total;++i){
        if(D[N][i] >= 2){
            return (void)proc(i);
        }
    }

    return (void)(cout << "No" << endl);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    A.assign(N, 0);
    for(auto & i : A)cin >> i;
    proc();
    return 0;
}