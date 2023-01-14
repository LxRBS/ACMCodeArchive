/**
 * N(<=10)个格子，黑白两色，两个人轮流走，每次走棋有两种走法
 * 1 对于1<=i<j<=N，假设j是白色，则将i、j颜色翻转
 * 2 翻转第1个各自的颜色，假设第1格为白色
 * 不能走者输，问先手胜负
 * 显然是SG函数、状压DP
 */
#include <bits/stdc++.h>
using namespace std;

int N;
int sg[1<<11];
char A[12];

int dfs(int status){
    if(sg[status] != -1) return sg[status];
                                   
    vector<int> vec;
    if(status & 1){
        int tmp = dfs(status ^ 1);
        vec.push_back(tmp);
    }
    for(int i=0;i<N;++i)for(int j=i+1;j<N;++j){
        if(status & (1<<j)){
            int tmp = dfs(status ^ (1<<i) ^ (1<<j));
            vec.push_back(tmp);
        }
    }
    sort(vec.begin(), vec.end());
    int k = 0;
    while(k<vec.size()){
        if(k != vec[k]) return sg[status] = k;
        ++k;
    }
    return sg[status] = k;
}
                                   
int main(){
    memset(sg, -1, sizeof(sg));
    sg[0] = 0;
    int nofkase; scanf("%d", &nofkase);
    while(nofkase--){
        scanf("%d%s", &N, A);
        int status = 0;
        for(int i=0;i<N;++i){
            if(A[i] == 'w'){
                status |= 1<<i;
            }
        }
        puts(dfs(status)?"Yes":"No");
    }
    return 0;
}