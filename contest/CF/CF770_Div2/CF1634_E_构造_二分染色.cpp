/**
 * 给定M个数组，每个数组Ni个数，要求将所有的数分成两堆，记作L和R，满足：
 * 1 L == R
 * 2 每一个数组，一半进入L，一半进入R
 * 可行的话，给出方案；否则输出NO
 * 首先显然要Ni是偶数，且每个数值的数量也必须是偶数，否则必然NO
 * 两个条件其实就是：相同数值各分一半，相同数组各分一半
 * 考虑某个数值v，将其放入L，则其后必然有某个相同的v要放入R，可以推测就放入相邻的后一个即可
 * 对于同一个数组，相邻数必然可以分开
 * 因此连接相应的边，做一个二分染色即可。
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
int const SIZE = 200055;
#endif

typedef vector<int> vi;
typedef unordered_map<int, int> mii;

int M;
int Cnt[SIZE];

mii Pre;
int Total;

vi G[SIZE];
char Ans[SIZE] = {0};

void dfs(int u, char ch){
    Ans[u] = ch;
	for(auto v: G[u]){
		if(Ans[v]) continue;
		dfs(v, ch^'L'^'R');
	}
}

void proc(){
	for(int i=1;i<=Total;i+=2){
		G[i].push_back(i+1);
		G[i+1].push_back(i);
	}

    for(int i=1;i<=Total;++i){
        if(Ans[i]) continue;
		dfs(i, 'L');
	}

    puts("YES");
    char const * p = Ans;
	for(int i=1;i<=M;++i){
		for(int j=1;j<=Cnt[i];++j){
            putchar(*++p);
		}
		putchar('\n');
	}
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif   
    M = getInt();
	int k = 0;
    bool flag = false;

	for(int n,a,i=1;i<=M;++i){
        if(1&(n = getInt())) flag = true;
		Cnt[i] = n;

		for(int j=1;j<=n;++j){
			++k;
			auto it = Pre.find(a = getInt());
            if(it == Pre.end()){
				it = Pre.insert(it, {a, 0});
			}
			if(it->second){
                G[k].push_back(it->second);
				G[it->second].push_back(k);
				it->second = 0;
			}else{
                it->second = k;
			}
		}
	}
	if(flag){puts("NO"); return 0;}
	for(auto p: Pre)if(p.second){puts("NO"); return 0;}
	Total = k;
    proc();
    return 0;
}