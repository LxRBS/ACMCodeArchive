/**
 * N+1个柱子，其中N个柱子每个柱子有三个盘子，第N+1是空的
 * 盘子一共有N种颜色，每种颜色恰好有3个
 * 要求利用空位移动盘子，使得最后每个柱子的盘子颜色一样
 * 任意时刻，每根柱子上的盘子数量不超过3个
 * 如果某个颜色分只分布在两根柱子上，有大概率能将该颜色完成
 * 如果某个颜色分布在三根柱子上，仍然有机会完成
 * 做一个颜色队列，依次取出，能完成的就完成，不能完成的扔回队尾
 * 最开始用的是柱子队列，但是一次作业有可能影响三根柱子，因此维护时容易出错
*/
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getUnsigned(){
	char ch = __hv007();
	while( ch < '0' || ch > '9' ) ch = __hv007();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = __hv007() ) && ch <= '9' ) ret = (ret<<1) + (ret<<3) + (int)(ch-'0');
	return ret;
}

#define fi first
#define se second
#define pb push_back
#define mp make_pair
typedef pair<int, int> pii;
typedef vector<int> vi;

#ifndef ONLINE_JUDGE
int const SIZE = 30;
#else 
int const SIZE = 1010;
#endif

int const OK = 0; // 3个一样
int const B2 = 1; // 底下2个一样
int const T2 = 2; // 上面2个一样
int const M2 = 3; // 上下两个一样，中间不一样
int const D3 = 4; // 三个全不一样

int N, Empty;
vector<pii> Buzhou;
vector<pii> Color2Pos[SIZE];
vi Zhu[SIZE];

bool cmp(const pii &a, const pii &b){
	if(a.se != b.se) return a.se > b.se;
	return a.fi < b.fi;
}

void move(int src, int dst){
	int color = Zhu[src].back(); // color是当前要移动的盘子颜色
	Zhu[dst].pb(color); // 移动到dst柱子上
	Zhu[src].pop_back(); // 从src柱子上移除
	Buzhou.pb({src, dst}); // 记录步骤，为输出做准备
    for(auto &pp: Color2Pos[color]){ // 更新Color2Pos中的数据
		if(pp.fi==src && pp.se==Zhu[src].size()){
			pp.fi = dst;
			pp.se = Zhu[dst].size() - 1;
		}
	}
}

inline bool proc222(int idx, int jdx, int kdx){
	move(idx, Empty);
	move(jdx, Empty);
	move(kdx, Empty);
	if(Zhu[idx].back() == Zhu[jdx].back() || Zhu[idx].back() == Zhu[jdx][0]){
		move(idx, jdx);
		move(idx, kdx);
	}else{
		move(idx, kdx);
		move(idx, jdx);
	}
	Empty = idx;
	return true;
}

/// pair表示该柱子上有两个color，而single表示该柱子上有一个color
bool proc(int color, int pair, int single){
    vector<pii> &pos = Color2Pos[color];
	vi row;
	int roo = -1;
	for(const pii &pp: pos){
        if(pp.fi == pair){
			row.pb(pp.se);
		}else if(pp.fi == single){
            roo = pp.se;
		}else{
			throw runtime_error("###333");
		}
	}
	assert(row.size() == 2 && roo != -1);
	if(row[0] > row[1]) swap(row[0], row[1]);

    if(1 == row[1] && 0 == row[0]){ // 说明底下两个颜色一样
        move(pair, Empty);
		if(2 == roo){
			move(single, pair);
			move(Empty, single);
		}else if(1 == roo){
			move(single, Empty);
			move(single, pair);
			move(single, Empty);
			Empty = single;
		}else if(0 == roo){
			move(single, Empty);
			move(single, Empty);
			move(single, pair);
			Empty = single;
		}else{
			throw runtime_error("666666");
		}
		return true;
	}

    if(2 == row[1] && 1 == row[0]){ // 说明上面两个颜色一样
        move(pair, Empty);
		move(pair, Empty);
		if(2 == roo){
			move(single, Empty);
			move(pair, single);
			Empty = pair;
		}else if(1 == roo){
			move(single, pair);
			move(single, Empty);
			move(single, pair);
			Empty = single;
		}else if(0 == roo){
			move(single, pair);
			move(single, pair);
			move(single, Empty);
			Empty = single;
		}else{
			throw runtime_error("XXX");
		}
		return true;
	}

    if(2 == row[1] && 0 == row[0]){ // 说明上下两个颜色一样
        if(0 == roo) return false;
		if(2 == roo){
			move(pair, Empty);
			move(single, Empty);
			move(pair, single);
			move(pair, Empty);
			Empty = pair;
		}else if(1 == roo){
            move(pair, Empty);
			move(single, pair);
			move(single, Empty);
			move(pair, single);
			move(pair, single);
			move(pair, Empty);
			Empty = pair;
		}else{
			throw runtime_error("2222");
		}
		return true;
	}

	throw runtime_error("11111");
}

inline bool proc221(int idx, int jdx, int kdx){
    move(idx, Empty);
	move(jdx, Empty);
	if(Zhu[kdx].back() == Zhu[idx].back() || Zhu[kdx].back() == Zhu[idx][0]){
		move(kdx, idx);
		move(kdx, Empty);
		move(kdx, jdx);
	}else{
		move(kdx, jdx);
		move(kdx, Empty);
		move(kdx, idx);
	}
	Empty = kdx;
    return true;
}

inline bool proc220(int idx, int jdx, int kdx){
    move(idx, Empty);
	move(jdx, Empty);
	if(Zhu[kdx].back() == Zhu[idx].back() || Zhu[kdx].back() == Zhu[idx][0]){
	    move(kdx, idx);
		move(kdx, jdx);
		move(kdx, Empty);
	}else{
        move(kdx, jdx);
		move(kdx, idx);
		move(kdx, Empty);
	}	
	Empty = kdx;
	return true;
}

inline bool proc211(int idx, int jdx, int kdx){
	move(idx, Empty);
	if(Zhu[jdx].back() == Zhu[idx][0] || Zhu[jdx].back() == Zhu[idx].back()){
		move(jdx, idx);
		move(jdx, Empty);
        move(kdx, jdx);
		move(kdx, Empty);
		move(kdx, jdx);
		Empty = kdx;
	}else{
        move(kdx, idx);
		move(kdx, Empty);
		move(jdx, kdx);
		move(jdx, Empty);
		move(jdx, kdx);
		Empty = jdx;
	}
	return true;
}

inline bool proc210(int idx, int jdx, int kdx){
	move(idx, Empty);
	move(jdx, idx);
	move(jdx, Empty);
	move(kdx, jdx);
	move(kdx, jdx);
	move(kdx, Empty);
	Empty = kdx;
	return true;
}

bool proc(int color){
    vector<pii> &pos = Color2Pos[color];

	if(pos[0].fi == pos[1].fi && pos[1].fi == pos[2].fi) return true;

    if(pos[0].fi == pos[1].fi){
        int shuangzhu = pos[0].fi;
		int lingzhu = pos[2].fi;
		return proc(color, shuangzhu, lingzhu);
	}

	if(pos[1].fi == pos[2].fi){
        return proc(color, pos[1].fi, pos[0].fi);
	}

	if(pos[0].fi == pos[2].fi){
        return proc(color, pos[0].fi, pos[1].fi);
	}

    sort(pos.begin(), pos.end(), cmp);
	if(pos[0].se != 2) return false;
    if(0 == pos[1].se && 0 == pos[2].se) return false;

	if(2 == pos[1].se && 2 == pos[2].se){
		return proc222(pos[0].fi, pos[1].fi, pos[2].fi);
	}
	if(2 == pos[1].se && 1 == pos[2].se){
		return proc221(pos[0].fi, pos[1].fi, pos[2].fi);
	}
	if(2 == pos[1].se && 0 == pos[2].se){
		return proc220(pos[0].fi, pos[1].fi, pos[2].fi);
	}	
	if(1 == pos[1].se && 1 == pos[2].se){
		return proc211(pos[0].fi, pos[1].fi, pos[2].fi);
	}
	if(1 == pos[1].se && 0 == pos[2].se){
		return proc210(pos[0].fi, pos[1].fi, pos[2].fi);
	}
	throw runtime_error("AWWWWA");
}


queue<int> Todo;
bool Done[SIZE];
int DoneCnt = 0;

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    N = getUnsigned();
    for(int i=0;i<3;++i)for(int j=1;j<=N;++j){
		Zhu[j].pb(getUnsigned());
	}

	for(int i=1;i<=N;++i){
        if(Zhu[i][0]==Zhu[i][1] && Zhu[i][1]==Zhu[i][2]){
            DoneCnt += Done[Zhu[i][0]] = 1; 
		}else{
			swap(Zhu[i][0], Zhu[i][2]);
            Color2Pos[Zhu[i][0]].pb({i, 0});
			Color2Pos[Zhu[i][1]].pb({i, 1});
			Color2Pos[Zhu[i][2]].pb({i, 2});
		}
	}

	for(int i=1;i<=N;++i)if(0==Done[i]){
		Todo.push(i);
	}

	assert(Todo.size()+DoneCnt == N);

	Empty = N + 1;

	while(!Todo.empty()){
		assert(Zhu[Empty].empty());
		int color = Todo.front();
		Todo.pop();

        if(proc(color)) ++DoneCnt;
		else Todo.push(color);
	}

	assert(DoneCnt == N);

    if(N+1!=Empty){
		Buzhou.push_back({N+1, Empty});
		Buzhou.push_back({N+1, Empty});
		Buzhou.push_back({N+1, Empty});
	}

	printf("%d\n", Buzhou.size());
	for(auto pp: Buzhou){
		printf("%d %d\n", pp.fi, pp.se);
	}
	return 0;
}
