/**
 * 给定字符串S和T，其中T不超过26且不重复字母
 * 每次从S中删除一个等于T的子序列，问最多删除多少次
 * 贪心操作，对第i次删除，对T中的每个字母记录用到的最靠前的位置
 * 下一次操作在此基础上往后即可。当某个字母用完了，即可全部退出
 */
#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
int const SIZE = 133;
#else
int const SIZE = 1000100;
#endif

typedef long long llt;

inline int tr(char ch){return ch-'a';}

int N, M;
char S[SIZE], T[30];
int Map[26];
int Pos[26][SIZE];
int Cnt[26];

int LastUse[26];
int ToBe[26];

bool isOK(int prev){
    for(int i=1;i<M;++i){
        // i = Map[tr(T[j])];
        if(ToBe[i] >= Cnt[i]) return false;
        

        int pos = Pos[i][ToBe[i]];
        if(pos < prev){
            int tmp = upper_bound(Pos[i]+ToBe[i], Pos[i]+Cnt[i], prev) - Pos[i];
            if(tmp == Cnt[i]) return false;

            pos = Pos[i][tmp];
            ToBe[i] = tmp + 1;
        }else{
            ++ToBe[i];
        }
        prev = pos;
    }
    return true;
}

int proc(){
    if(N < M) return 0;

    memset(Map, -1, sizeof(Map));
    for(int i=0;i<M;++i) Map[tr(T[i])] = i;

    memset(Cnt, 0, sizeof(Cnt));
    for(int k,i=0;i<N;++i){
        k = Map[tr(S[i])];
        if(k!=-1){
            Pos[k][Cnt[k]++] = i;
        }        
    }

    for(int i=0;i<M;++i)if(Cnt[i]==0)return 0;

    memset(LastUse, -1, sizeof(LastUse));
    memset(ToBe, 0, sizeof(ToBe));
    int ans = 0;
    for(int i=0;i<Cnt[0];++i){
        if(isOK(Pos[0][i])) ++ans;
        else break;
    }
    return ans; 
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    int nofkase; scanf("%d", &nofkase);
    while(nofkase--){
        scanf("%d%d%s%s", &N, &M, S, T);
        printf("%d\n", proc());
    }
    return 0;
}