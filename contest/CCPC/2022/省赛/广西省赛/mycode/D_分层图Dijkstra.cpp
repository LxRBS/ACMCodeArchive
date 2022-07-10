/**
 * N=2E4的有向图。从S出发到T，初始速度为1。
 * 某些点是加油站，可花费一定时间将当前速度加倍
 * 有些边是坏边，经过以后速度会变回1
 * 问从S到T的最短时间。
 * 在每个加油站有两种决策，直接走和加油，因此可以考虑建分层图
 * 由于一条边的最长长度为1E6，因此最多加20次油即可，建一个21层图即可
 * 最后跑一个Dijkstra
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

char getChar(){
	char ch = __hv007();
	while(!isalpha(ch)) ch = __hv007();
	return ch;
}

#ifndef ONLINE_JUDGE
int const SIZE = 11;
#else
int const SIZE = 2E4+7;
#endif

using llt = long long;
llt const INF = 0x3F7F7F7FFFFFFFFF;

using pii = pair<int, llt>;
using vpii = vector<pii>;

vpii G[SIZE*21];
llt D[SIZE*21];
bool Flag[SIZE*21];

/// vn是点的数量
void Dijkstra(int vn, int s, int t){
    fill(D, D+vn+1, INF);
	fill(Flag, Flag+vn+1, false);

    using f_t = function<bool(const pii&, const pii&)>;
	priority_queue<pii, vpii, f_t> q([](const pii&a, const pii&b)->bool{
		if(a.second != b.second) return a.second > b.second;
		return a.first < b.first;
	});

    /// 先把起点塞进去
	q.push({s, D[s] = 0});
	while(1){
		while(!q.empty() && Flag[q.top().first]) q.pop();
		if(q.empty()) break;

		auto h = q.top(); q.pop();
		Flag[h.first] = true;

        llt tmp;
		for(const auto &p: G[h.first]){
            if(!Flag[p.first] && D[p.first] > (tmp=h.second + p.second)){
				q.push({p.first, D[p.first]=tmp});
			}
		}
	}
}


int N, M, S, T;

/// 建二十一层图
void mkEdge(int a, int b, llt c, char ch){
	llt speed = 1;
	int start = 0;
    for(int i=0;i<21;++i){
        llt t = c / speed;
		if(c % speed) ++t;
		if('G' == ch) G[start+a].emplace_back(start+b, t);
		else if('B' == ch) G[start+a].emplace_back(b, t);
		else throw runtime_error("XX");
		// if(speed >= c) break;
		start += N;
		speed <<= 1;
	}
}

llt proc(){
	if(S == T) return 0;

    int t = 21 * N + 1;
	for(int i=0;i<21;++i){
		G[i*N+T].emplace_back(t, 0);
	}
	Dijkstra(t, S, t);
	if(INF == D[t]) return -1;
	return D[t];
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    N = getInt(); M = getInt();
	S = getInt(); T = getInt();
	for(int a,b,c,ch,i=0;i<M;++i){
        a = getInt(); b = getInt();
		c = getInt(); ch = getChar();
		mkEdge(a, b, c, ch);
	}
	int p = getInt();
	while(p--){
        int x = getInt();
		llt c = getInt();
		int start = 0;
		for(int i=0;i<20;++i){
            G[start+x].emplace_back(start+N+x, c);
			start += N;
		}
	}
	cout << proc() << endl;
    return 0;
}