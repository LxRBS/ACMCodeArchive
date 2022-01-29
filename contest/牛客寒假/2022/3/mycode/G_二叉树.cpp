/**
 * 给定二个二叉树A和B，B可以旋转最多一次得到A，问旋哪个节点
 * 从根往下，找到第一个不同的节点，就是A的节点
*/
#include<bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getUnsigned(){
	char ch = __hv007();
	while( ch < '0' || ch > '9' ) ch = __hv007();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = __hv007() ) && ch <= '9' ) ret = (ret<<1) + (ret<<3) + (int)(ch-'0');
	return ret;
}

#ifndef ONLINE_JUDGE
int const SIZE = 18;
#else
int const SIZE = 1010;
#endif

typedef long long llt;
llt const MOD = 1000000000+7;

typedef pair<int, int> PairTy;

int N;
int A[SIZE][2];
int B[SIZE][2];
int RootA, RootB;

PairTy Dif;

bool dfs(int a, int b){
    if(a != b){
        Dif = {a, b};
        return true;
    }

    if(A[a][0]){
        assert(B[b][0]);
        if(dfs(A[a][0], B[b][0])){
            return true;
        }
    }

    if(A[a][1]){
        assert(B[b][1]);
        if(dfs(A[a][1], B[b][1])){
            return true;
        }
    }

    return false;
}

void proc(){
    bool flag = true;
    for(int i=1;i<=N;++i){
        if(A[i][0] == B[i][0] && A[i][1] == B[i][1]) continue;
        flag = false;
        break;
    }
    if(flag){
        return (void)puts("0");
    }

    puts("1");

    int flaga[1010] = {0}, flagb[1010] = {0};
    for(int i=1;i<=N;++i){
        flaga[A[i][0]] = flaga[A[i][1]] = 1;
        flagb[B[i][0]] = flagb[B[i][1]] = 1;
    }
    for(int i=1;i<=N;++i){
        if(flaga[i] == 0){
            RootA = i;
            break;
        }
    }
    for(int i=1;i<=N;++i){
        if(flagb[i] == 0){
            RootB = i;
            break;
        }
    }

   assert(dfs(RootA, RootB));

   int a = Dif.first;
   int b = Dif.second;
   
   printf("%d\n", a);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    N = getUnsigned();
    for(int i=1;i<=N;++i) A[i][0] = getUnsigned(), A[i][1] = getUnsigned();
    for(int i=1;i<=N;++i) B[i][0] = getUnsigned(), B[i][1] = getUnsigned();
    proc();
    return 0;
}