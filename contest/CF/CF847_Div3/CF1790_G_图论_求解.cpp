/**
 *  给定一个无向连通图。有的节点上有token，有的节点上有奖励
 *  规则如下：第一步可以移动任意token，如果走到了奖励节点，则可以在其他token中任选一个进行移动；否则，行动结束
 *  问能否将任意一个token移动到节点1
 *  首先token需要交替移动，不能连续移动一个。因此如无意外，需要持续的走上奖励节点。
 *  因此，首先特判，如果节点1上就有token，或者节点1的邻居有token，则可。
 *  如果不是上述情况，则必然是 1 - 奖励节点连通块 - token 的模式，这有这样的token才有可能走到1 
 *  而这样的token想要走到1，只需要其他token加在一起为它贡献交替的步数即可。
 *  在所有可能满足条件的token中，只需要考察离1最近的token即可。因为如果其他token的贡献无法使得最近的token走到1，则用这个最近的替换任何一个，也不可能贡献出更多。
 *  还有一个特殊情况，如果两个奖励点相连，则实际上走到其上的token可以贡献无数步。注意这个情况仍然不违背上述最近的原则。
 *  首先特判，然后标记一下奖励节点，单独的为1，相连的标记为2。
 *  然后从1跑个最短路，注意只入队奖励节点，得到距离1最近的token。
 *  然后统计其他token的贡献，如果token的邻居只有标记1的奖励节点，则贡献为1；如果有标记2，则贡献为INF；否则贡献为0。
 *  最后比较一下即可。
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
	while( ch != 'o' && ch != 'x' ) ch = __hv007();
	return ch;
}

using llt = long long;
using vi = vector<int>;
using vll =vector<llt>;
using edge_t = tuple<int, int, int, int>;
using ve = vector<edge_t>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vpii = vector<pii>;

llt const MOD = 1E9+7LL;

int N, M;
int P, B;
vvi G;
vi Token, Bonus;
vi IsBonus;
vi IsToken;
vi D;
vi Can;

bool proc(){
	IsToken.assign(N + 1, 0);
	for(int i : Token) IsToken[i] = 1;
	if(IsToken[1]) return true;
	for(int i : G[1]){
		if(IsToken[i]) return true;
	}
	if(1 == Token.size()) return false;

	IsBonus.assign(N + 1, 0);
	for(int i : Bonus) IsBonus[i] = 1;
	for(int i : Bonus){
        for(int v : G[i]){
			if(IsBonus[v]){
				IsBonus[i] = IsBonus[v] = 2;
			}
		}
	}

    D.assign(N + 1, -1);
	queue<int> q;
	D[1] = 0;
	for(int i : G[1]){
		if(IsBonus[i]){
			D[i] = 1;
			q.push(i);
		}
	}
	Can.clear();
	int k = 1, sz;
	while(sz = q.size()){
		++k;
		while(sz--){
			auto h = q.front(); q.pop();
			assert(IsBonus[h]);
			for(auto v : G[h]){
				if(D[v] != -1) continue;
				D[v] = k;
				if(IsToken[v]){
					Can.emplace_back(v);
					IsToken[v] = 2;
				}
                if(IsBonus[v]){
					q.push(v);
				}
			}
		}
	}

	if(0 == Can.size()) return false;


	auto node = Can[0];
	int c = 0;
	for(int i : Token){
		if(i == node) continue;
		int st = 0;
		for(int v : G[i]){
			if(IsBonus[v]){
                st |= IsBonus[v];
				if(st & 2) break;
			}
		}
		if(st & 2) c = 20000000;
		else if(st & 1) ++c;
	}

	if(c + 1 >= D[node]) return true;
    return false;
}


int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int nofkase = getInt();
	for(int kase=1;kase<=nofkase;++kase){
		// printf("%d: ", kase);
        N = getInt(); M = getInt();
		P = getInt(); B = getInt();
		G.assign(N + 1, vi());
		Token.assign(P, 0);
		Bonus.assign(B, 0);
		for(int & i : Token) i = getInt();
		for(int & i : Bonus) i = getInt();
		for(int a,b,i=0;i<M;++i){
			a = getInt(); b = getInt();
			G[a].emplace_back(b);
			G[b].emplace_back(a);
		}		
		puts(proc() ? "YES" : "NO");
	
	}
	return 0; 
}