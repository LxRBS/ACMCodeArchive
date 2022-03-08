/**
 * 一个地图，有起点和终点，有若干石块。Taka从起点出发，可以往4个方向走。
 * 但是只有在碰到石块时才能停下来，并重新选择方向前进。
 * 问最少几步到达终点，不能的话输出-1。
 * 注意地图是没有边界的，所以如果边界没有石块，Taka就会冲出地图，视为失败。
 * 地图在1E9，石块数量在1E5，显然能够到达的位置只与石块有关，所以把石块的位置用map记下来
 * 然后根据当前位置判断下一个能够到达的位置即可。
 * BFS，成批扩展。
*/
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

typedef int llt;

llt getInt(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}

	llt ret = (llt)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10 + (llt)(ch-'0');
	return sgn ? ret : -ret;
}

#ifndef ONLINE_JUDGE
int const SIZE = 13;
#else
int const SIZE = 200030;
#endif  

int H, W, N;
int Sx, Sy, Gx, Gy;
map<llt, set<llt> > Rows;
map<llt, set<llt> > Cols;

typedef pair<int, int> pii;
struct pair_hash{
	inline size_t operator()(const pii&p)const{
		return p.first * 1331 + p.second;
	}	
};

unordered_set<pii, pair_hash> Flag;

/// 看能不能走，根据石块的位置和，一个方向最多存在2个可能的下一步位置
vector<pii> go(int fi, int se, const map<llt, set<llt> > &mm, bool isY=false){
    auto it = mm.find(fi);
    if(mm.end() == it) return {};

    vector<pii> ans;
    /// 说明fi那一溜有石块
    const set<llt> &ss = it->second;
    auto jt = ss.lower_bound(se);
    assert(*jt != se); // 当前位置不可能有石块
    /// jt所在位置应该比se要大，如果确实存在且不是紧挨着就可以走
    if(jt != ss.end() && *jt > se + 1){
        if(isY) ans.emplace_back(*jt-1, fi);
        else ans.emplace_back(fi, *jt-1);
    }
    if(jt != ss.begin()){ // 说明前面还有石块
        --jt;
        if(*jt + 1 < se){
            if(isY) ans.emplace_back(*jt+1, fi);
            else ans.emplace_back(fi, *jt+1);
        }
    }
    return ans;
}

int proc(){
    queue<pii> q;
    q.push({Sx, Sy});
    Flag.insert({Sx, Sy});
    int step = 0;
    
    while(!q.empty()){
        ++step;
        int sz = q.size();
        while(sz--){
            auto h = q.front(); q.pop();
            /// 首先看能不能横着走
            vector<pii> vec = go(h.first, h.second, Rows);
            for(const auto &p: vec){
                if(p.first == Gx && p.second == Gy) return step;
                auto a320 = Flag.find(p);
                if(a320 == Flag.end()){
                    Flag.insert(a320, p);
                    q.push(p);
                }
            }
            /// 再看能不能竖着走
            vec = go(h.second, h.first, Cols, true);
            for(const auto &p: vec){
                if(p.first == Gx && p.second == Gy) return step;
                auto a320 = Flag.find(p);
                if(a320 == Flag.end()){
                    Flag.insert(a320, p);
                    q.push(p);
                }
            }
        }
    }
    return -1;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    H = getInt(); W = getInt(); N = getInt();
    Sx = getInt(); Sy = getInt();
	Gx = getInt(); Gy = getInt();
	for(int x,y,i=0;i<N;++i){
        x = getInt(); y = getInt();
		Rows[x].insert(y);
		Cols[y].insert(x);
	}
	printf("%d\n", proc());
    return 0;
}

