/**
 * N×N的方阵，初始全为0
 * 有子弹从上往下或者从左往右飞，碰到边界就会停下并占据那一格
 * 后续的子弹碰到之前停下的子弹也会停下来并占据相应的格子
 * 现在给定一个结果，问可不可能
 * 所有的有子弹格子，必须满足右边或者下边也有子弹，否则不可能
 * 暴力检查一遍
*/
#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define hash_t map

typedef pair<int,int> pii;
typedef vector<pii> vpii;

int N;
char A[55][55];

bool isOK(int r, int c){
    if(c==N-1) return true;
    if(r==N-1) return true;
    return '1' == A[r+1][c] || '1' == A[r][c+1];
}

bool proc(){
    for(int i=0;i<N;++i)for(int j=0;j<N;++j){
        if('1' ==A[i][j] && !isOK(i, j)) return false;
    }
    return true;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif
    int nofkase;
    scanf("%d", &nofkase);
    while(nofkase--){
        scanf("%d", &N);
        for(int i=0;i<N;++i)scanf("%s", A[i]);
        puts(proc() ? "YES" : "NO");
    }

    return 0;
}