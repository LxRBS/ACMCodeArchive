/**
 * 给定一个有根树，将其划分成若干条路径，任意答案均可
 * 直接写个深搜即可
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
int const SIZE = 130;
#else
int const SIZE = 1.1E6+10;
#endif

using vi = vector<int>;
using vvi = vector<vi>;

int N, Root;
vvi G;
vvi Ans;

void dfs(int u, vi & vec){
    if(G[u].empty()){
        Ans.emplace_back(vec);
        return;
    }
    bool flag = false;
    for(int v : G[u]){
        if(flag){
            vi tmp(1, v);
            dfs(v, tmp);
        }else{
            flag = true;
            vec.push_back(v);
            dfs(v, vec);
        }
    }    
    return;
}

void proc(){
    Ans.clear();
    vi vec(1, Root);
    dfs(Root, vec);
    printf("%d\n", (int)Ans.size());
    for(const auto & vec : Ans){
        printf("%d\n", (int)vec.size());
        for(int i : vec) printf("%d ", i);
        printf("\n");
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif 
    int nofkase = getInt();
    while(nofkase--){
        G.assign((N = getInt()) + 1, vi());
        for(int a,i=1;i<=N;++i){
            a = getInt();
            if(a == i){
                Root = i;
            }else{
                G[a].push_back(i);
            }
        }        
        proc();
        if(nofkase) printf("\n");
    }
    return 0;
}

