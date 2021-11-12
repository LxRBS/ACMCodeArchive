/**
 * 有一个未知的N排列P，再给定N-1个片段
 * 每个片段包含若干个数，表示这些数在排列中是连续的，但未必按照给出的顺序
 * 求该排列。任意一个答案均可。N在200
 * 用搜索
 * 对第i个位置，检查所有可以放置的v，深搜。
 * 有两种情况：
 * 假设前一个数是prev，则有可能从片段中搜出若干个可能的v，进行放置
 * prev对后一个数没有影响，则从剩下的数中找一个可以开头的
 * 样例没过，但是没看懂说明。感觉spj似乎有问题，莫非看错题了
 * 自检查了题目数据，感觉都对。
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
int const SIZE = 21;
#else 
int const SIZE = 200100;
#endif

typedef long long llt;

int N, Total;
vector<set<int> > A;
vector<int> Ans;
vector<int> V2Pos[SIZE];

bool Flag[SIZE];

/// 检查当前是否可以放v
/// 如果所有含v的seg都包含相同的元素，则v可以放
/// 只含v的seg不需要考虑
bool isOK(int v){
    int flag[SIZE] = {0};
    int k = 0;
    for(auto i: V2Pos[v]){
        if(A[i].size() == 1) continue;

        ++k;
        for(auto j: A[i]){
            ++flag[j];
        }
    }
    for(int i=1;i<=N;++i)if(i!=v){
        if(flag[i] == k) return true;
    }
    return false;
}

inline void dodo(int v){
    Ans.push_back(v);
    Flag[v] = true;
    for(auto i: V2Pos[v]){
        A[i].erase(v);
    }
}

inline void undo(int v){
    Ans.pop_back();
    Flag[v] = false;
    for(auto i: V2Pos[v]){
        A[i].insert(v);
    }
}

bool find(vector<int> &vec, int v){
    vec.clear();
    int flag[SIZE] = {0};
    int k = 0;
    for(auto i: V2Pos[v]){
        if(A[i].empty()) continue;

        ++k;
        for(auto j: A[i]){
            ++flag[j];
        }
    }

    int you = 0;
    for(int i=1;i<=N;++i)if(i!=v){
        if(flag[i] == k) vec.push_back(i);
        else if(flag[i]) you = 1;
    }
    return you;
}

bool dfs(){
    if(Ans.size() == Total){
        return true;
    }

    /// 取出上一个数
    int prev = Ans.back();
    /// 找可以放在prev后面的数
    vector<int> vtmp;
    bool b = find(vtmp, prev);
    if(vtmp.empty() && b) return false;
    if(!vtmp.empty())for(auto i: vtmp){
        dodo(i);
        if(dfs()) return true;
        undo(i);
    }else for(int i=1;i<=N;++i)if(!Flag[i] && !V2Pos[i].empty() && isOK(i)){
        dodo(i);
        if(dfs()) return true;
        undo(i);       
    }
    return false;
}

void proc(){
    Ans.clear();
    fill(Flag, Flag+N+1, false);
    for(int i=1;i<=N;++i) V2Pos[i].clear();
    for(int i=0;i<A.size();++i){
        for(auto v: A[i]){
            V2Pos[v].push_back(i);
        }
    }

    Total = 0;
    for(int i=1;i<=N;++i)if(!V2Pos[i].empty()) ++Total;

    for(int i=1;i<=N;++i)if(!Flag[i] && !V2Pos[i].empty() && isOK(i)){       
        dodo(i);
        if(dfs()) break;
        undo(i);
    }

    for(int i=1;i<=N;++i)if(!Flag[i])Ans.push_back(i);
#ifndef ONLINE_JUDGE
    cout<<Ans.size()<<endl;
#endif
    for(auto i: Ans)printf("%d ", i);
    puts("");
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getInt();
    while(nofkase--){
        A.assign(N = getInt(), set<int>());
        for(int k, i=1;i<N;++i){
            set<int>& s = A[i];
            k = getInt();
            while(k--){
                s.insert(getInt());
            }
        }
        proc();
    }
    return 0;
}
