/**
 * 一共有N个人，每个人手上持有一个独特的单词，现在给定N对单词
 * a b
 * 意思是第i个人现在手上持有的是a，但是想换成b，b各不相同，也就是说大家的意愿没有冲突
 * 问能否成功。本题的换不是人之间互相换，而是有规则的。例如
 * x y
 * y x
 * 这组数据就无法成功。因为第1个人想要y，但是第2个人没有拿到x之前，是不会释放y的，于是都不能达成。
 * 按照题意，关键是找到一个b没有被任何人持有。按照a->b做一个有向图
 * 对于Deg[i] == 0的点，向下发起交换，看最后能否换成。
 * 最后检查标记即可
 */
#include <bits/stdc++.h>
using namespace std;
 
char *__abc147, *__xyz258, __ma369[1000000];
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
int const SIZE = 23;
#else
int const SIZE = 5500;
#endif

using llt = long long;
using vi = vector<int>;
using vvi = vector<vi>;

int N;
map<string, int> Map;
vvi G;
vi Flag;
vi Deg;

bool dfs(int u){
    for(const auto & v : G[u]){
        if(Flag[v]) return true;
        Flag[v] = 1;
        bool b = dfs(v);
        if(b) return b;
    }
    return false;
}

bool proc(){
    Flag.assign(G.size(), 0);
    for(int i=0,n=G.size();i<n;++i){
        if(Deg[i]) continue;
        Flag[i] = 1;
        bool b = dfs(i);
        if(b) return false;
    }
    for(int i=0,n=G.size();i<n;++i){
        if(0 == Flag[i]) return false;
    }
    return true;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> N;
    for(int i=0;i<N;++i){
        string a, b;
        cin >> a >> b;
        auto at = Map.find(a);
        if(at == Map.end()){
            at = Map.insert(at, {a, Map.size()});
            G.emplace_back(vi());
            Deg.push_back(0);
        } 
        auto bt = Map.find(b);
        if(bt == Map.end()){
            bt = Map.insert(bt, {b, Map.size()});
            G.emplace_back(vi());
            Deg.push_back(0);
        } 
        G[at->second].push_back(bt->second);
        ++Deg[bt->second];
    }
    puts(proc()?"Yes":"No");
    return 0;
}


