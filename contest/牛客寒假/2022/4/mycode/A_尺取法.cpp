/**
 * 给一个字符串，问至少包含k个R且不含P的子串有多少个
 * 首先把整串切成不含P的若干段，然后对每一段求至少含k个R的子串数量
 * 用二分或者尺取都可以，这里用的尺取。
*/
#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
int const SIZE = 22;
#else
int const SIZE = 200010;
#endif

typedef long long llt;

char A[SIZE];
int N, K;

llt proc(int s, int e){
    llt ans = 0LL;
    int right = s;
    int cnt = 0;
    for(int left=s;left<e;++left){
        while(right<e && cnt<K){
            if('R' == A[right]) ++cnt;
            ++right;
        }
        if(cnt == K){
            ans += e - right + 1;
        }
        if('R' == A[left]) --cnt;
    }
    return ans;
}

llt proc(){
    llt ans = 0;
    int left = 0, right = 0;
    while(1){        
        while(left<N && 'P'==A[left]) ++left;
        if(N == left) break;

        right = left;
        while(right<N && 'P' != A[right]) ++right;

        ans += proc(left, right);
        left = right;
    }

    return ans;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    scanf("%d%d%s", &N, &K, A);
    printf("%lld\n", proc());
    return 0;
}


