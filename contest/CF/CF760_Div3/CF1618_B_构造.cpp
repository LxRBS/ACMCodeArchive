/**
 * 给定由ab构成的字符串，再将所有长度为2的子串按顺序放好
 * 再从中间删掉一个。给出剩下的子串，求原字符串
 * 只需逐个检查相邻的子串即可，如果有不相等的，则必然是此处缺失了一个子串
*/
#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
int const SIZE = 11;
#else
int const SIZE = 110;
#endif

int N;
char A[SIZE][4];
char Ans[SIZE];

char* proc(){
    int k = 2;
    for(;k<N-1;++k){
        if(A[k-1][1] != A[k][0]){
            break;
        }
    }
    if(N-1 == k){        
        for(int i=1;i<N-1;++i)Ans[i] = A[i][0];
        Ans[N-1] = A[N-2][1];
        Ans[N] = 'a';
        Ans[N+1] = '\0';
    }else{
        for(int i=1;i<k;++i)Ans[i] = A[i][0];
        Ans[k] = A[k-1][1];
        for(int i=k;i<N-1;++i) Ans[i+1] = A[i][0];
        Ans[N] = A[N-2][1];
        Ans[N+1] = '\0';
    }
    return Ans + 1;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif
    int nofkase;
    scanf("%d", &nofkase);
    while(nofkase--){
        scanf("%d", &N);
        for(int i=1;i<N-1;++i)scanf("%s", A[i]);
        printf("%s\n", proc());
    }
    return 0;
}

