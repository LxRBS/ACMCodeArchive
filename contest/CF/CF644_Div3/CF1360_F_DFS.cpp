/**
 * N个长度为M的字符串，现在要构造一个串s，长度也是M
 * 使得s与这N个串中的每一个最多只有一个字母不同
 * 显然s的每个位置上的字母必然是这N个字符串相应位置上的字母的其中之一
 * 深搜一遍
*/
#include<bits/stdc++.h>
using namespace std;

int N, M;
char A[110][22];
vector<set<char> > Vec;

int Cha[110];
string Ans;

bool change(char ch, int depth){
    bool ret = true;
    for(int i=1;i<=N;++i){
        if(ch != A[i][depth]){
            if(++Cha[i] > 1){
                ret = false;
            }
        }
    }
    return ret;
}

void undo(char ch, int depth){
    for(int i=1;i<=N;++i){
        if(ch != A[i][depth]){
            --Cha[i];
        }
    }
}

bool dfs(int depth){
    if(depth == M){
        for(int i=1;i<=N;++i){
            if(Cha[i]>1) return false;
        }
        return true;
    }

    for(char ch: Vec[depth]){
        Ans += ch;
        if(change(ch, depth)){
            if(dfs(depth+1)){
                return true;
            }
        }
        undo(ch, depth);
        Ans.pop_back();
    }
    return false;
}

string proc(){
    if(1 == M) return "a";

    Vec.assign(M, set<char>());
    for(int i=1;i<=N;++i){
        for(int j=0;j<M;++j){
            Vec[j].insert(A[i][j]);
        }        
    }

    Ans.clear();
    fill(Cha, Cha+N+1, 0);     
    return dfs(0) ? Ans : "-1";
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase;
    scanf("%d", &nofkase);
    while(nofkase--){
        scanf("%d%d", &N, &M);
        for(int i=1;i<=N;++i) scanf("%s", A[i]);
        printf("%s\n", proc().c_str());
    }    
	return 0;
}
