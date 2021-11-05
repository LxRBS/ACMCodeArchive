/**
 * N×M的地板，有白有黑。白色块需要用1×1或者1×2的砖去覆盖，费用分别是x和y
 * 问覆盖所需的最小费用
 * 贪心即可
*/
#include<bits/stdc++.h>
using namespace std;

#define pb push_back
typedef vector<int> vi;

template<typename T>string value2string(const T &t){
    stringstream ss;
    ss<<t;
    return ss.str();
}

#ifndef ONLINE_JUDGE
int const SIZE = 120;
#else
int const SIZE = 300010;
#endif

int N, M, X, Y;
char A[110][1100];

int proc(int index){
    char const * const p = A[index];
    int k = 0, ans = 0;
    while(k < M){
        while(k < M && p[k] == '*') ++k;

        int cur = k;
        while(k < M && p[k] == '.') ++k;
        cur = k - cur;
        ans += (cur&1 ? X : 0) + (cur>>1) * Y; 
    }
    return ans;
}

int proc(){
    int ans = 0;
 
    if(X+X<=Y){
        for(int i=0;i<N;++i)for(int j=0;j<M;++j){
            if(A[i][j] == '.') ans += X;
        }
        return ans;
    }

    for(int i=0;i<N;++i){
        ans += proc(i);
    }
    return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif
    int nofkase;
    scanf("%d", &nofkase);
    while(nofkase--){
        scanf("%d%d%d%d", &N, &M, &X, &Y);
        for(int i=0;i<N;++i)scanf("%s", A+i);
        printf("%d\n", proc());
    }
    return 0;
}

