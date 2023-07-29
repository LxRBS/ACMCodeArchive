/**
 * 给定一个数字串和一个数字，将数字插入串中使得新串最大
 * 贪心即可 
 */
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

using llt = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;

#ifndef ONLINE_JUDGE
int const SZ = 34;
#else
int const SZ = 200000 + 12;
#endif

int N, D;
char A[SZ];

void proc(){
    for(int i=0;i<N;++i){
        if(A[i] - '0' < D){
            for(int j=0;j<i;++j) putchar(A[j]);
            printf("%d", D);
            puts(A+i);
            return;
        }
    }
    printf("%s%d\n", A, D);
    return;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int nofkase; scanf("%d", &nofkase);
    while(nofkase--){
        scanf("%d%d%s", &N, &D, A);
        proc();
    }
    return 0;
}

