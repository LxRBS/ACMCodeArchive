/**
 * n×m的矩阵，每一格有一个方向，上下左右，同时还有黑白两色
 * 问最多能放多少个机器人，使得机器人在移动中互相不碰，尽可能放在黑色格子中
 * 按照题目意思，必然有环。且每一格显然只能有一个后继，因此一个内向基环树的森林
 * 每个基环树能放的最大数量显然就是环的长度。现在考虑怎么找黑格最大
 * 环上的点显然是不会相碰的，令环上某点为u，则所有能够以环长步数到达u点的点，只能放一个机器人
 * 然后这些点中如果有一个是黑色，则黑色加1即可。
 * 如果对每个环点搜一次，应该会超时。
 * 但是容易观察到，令U为到u的距离为环长整数倍的集合，v是u的后继，V是v的集合
 * 则V到u必然是环长整数倍减一，同理，后面的点分别是减二、减三、……这显然是一个模
 * 因此在环上任取一点断开其入边，则基环树变为了以该点为根的树
 * 则所有深度对环长取模相等的点最后都能到达环上的同一点，只能取一个。
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
    while(1){
		char ch = __hv007();
		if('A' <= ch && ch <= 'Z' || ('0' <= ch && ch <= '9') && ('a' <= ch || ch <= 'z')) return ch;
	} 
}

#ifndef ONLINE_JUDGE
int const SIZE = 22;
#else
int const SIZE = 1000100;
#endif

int N, M, Total;
char A[SIZE];
char B[SIZE];
int Ans, Black, Len;

vector<int> G[SIZE];
vector<int> H[SIZE]; // 反向图
bool Flag[SIZE];

vector<bool> Dep2Ans;


/// 根据index的方向获取下一格
inline int get(int index){
    switch(B[index]){
		case 'U': return index - M;
		case 'R': return index + 1;
		case 'D': return index + M;
		case 'L': return index - 1;
		default: throw runtime_error("XXXXX");
	}
}

void dfs(int u){
	int v = get(u);
	G[u].push_back(v);
	H[v].push_back(u);

	if(!Flag[v]){
		Flag[v] = true;
		dfs(v);
	}
}

int getRoot(int u){
	Flag[u] = true;
	int v = G[u][0];
	if(Flag[v]) return v;
	return getRoot(v);
}

int calc(int rt){
	int ans = 1, v = G[rt][0];
    while(v != rt){
		v = G[v][0];
		++ans;
	}
    return ans;
}

void dfsDepth(int u, int depth){
	Flag[u] = true;
    if('0' == A[u] && !Dep2Ans[depth%Len]){
		Black += Dep2Ans[depth%Len] = 1;
	} 
	for(auto v: H[u]){
		dfsDepth(v, depth+1);
	}
}

void proc(){
	Ans = Black = 0;
	for(int i=1;i<=Total;++i){
		G[i].clear(); H[i].clear();
		Flag[i] = false;
	}

    /// 首先建图，实际上是一个内向基环树森林
	for(int i=1;i<=Total;++i)if(!Flag[i]){
		Flag[i] = true;
        dfs(i);
	}

	/// 对每一个基环树做处理
	fill(Flag, Flag+Total+1, false);
	for(int parent, rt, i=1;i<=Total;++i)if(!Flag[i]){
        rt = getRoot(i); // 求环上一点
		Ans += Len = calc(rt); // 求环长
		parent = G[rt][0];
		// 反向图上断开parent->rt的边，此时反向图变为了一棵树
		for(auto it=H[parent].begin();it!=H[parent].end();++it){
			if(*it == rt){
				H[parent].erase(it);
				break;
			}
		}
		Dep2Ans.assign(Len, false);
        dfsDepth(rt, 0);
	}
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif
    int nofkase = getInt();
    while(nofkase--){
        N = getInt(); M = getInt(); Total = N * M;
		for(int i=1;i<=Total;++i) A[i] = getChar();
		for(int i=1;i<=Total;++i) B[i] = getChar();
		proc();
		printf("%d %d\n", Ans, Black);
    }
    return 0;
}

