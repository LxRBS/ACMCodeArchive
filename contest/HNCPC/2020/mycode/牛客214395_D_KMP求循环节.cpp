/**
    给定一堆字符串，问满足i<j且si+sj==sj+si的ij一共有多少对
    如果条件满足说明si和sj的最小循环节是一样的，
    用KMP求循环节即可
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long llt;

int N;
char A[1000010];
int Next[1000010];
unordered_map<int, vector<int> > MMap;

//��src������������nΪsrc�ĳ���
void getNext(char const src[],int n,int next[]){
    next[0] = 0;
    for(int i=1;i<n;++i){
        int k = next[i-1];
        while( k > 0 && src[i] != src[k] ) k = next[k-1];
        next[i] = src[i] == src[k] ? k + 1 : 0;
    }
}

int BKDRHash(char const s[]){
    int const seed = 1331;
    int ans = 0;
    for(char const*p=s;*p;++p){
        ans = ans * seed + *p;
    }
    return ans;
}

int main(){
    //freopen("1.txt","r",stdin);
    while(1==scanf("%d",&N)){
        MMap.clear();
        for(int k,n,i=1;i<=N;++i){
            scanf("%s", A);
            n = strlen(A);
            getNext(A, n, Next);
            k = n - Next[n-1];
            if(n%k) k = n;
            A[k] = '\0';
            MMap[BKDRHash(A)].push_back(i);
        }
        llt ans = 0;
        for(auto pp: MMap){
            llt n = pp.second.size();
            ans += n * (n-1) >> 1;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
