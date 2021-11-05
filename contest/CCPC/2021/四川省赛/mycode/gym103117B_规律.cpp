/**
    N个人每个人有一个喜好，记作Ai
    N个人轮流操作，总共进行M轮，M在1E9
    第i个人操作，如果池子里有Ai，则第i个人的收益加1，并将Ai从池子里拿走
    如果没有Ai，则将Ai加入，收益不变
    问M轮后，每个人的收益
    M很大，不能模拟。
    对每一个Ai单独进行计算
    假设只有一个人喜好Ai，则该人的收益显然是该人的操作数量/2
    如果有两个人喜好，则前一个人的收益是0，后一个人的收益是该人的操作数量
    如果有t个人有共同喜好且t是偶数，则按对计算即可
    如果有t个人有共同喜好且t是奇数，则没两轮，每个人的收益加1
*/
#include <bits/stdc++.h>
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

#define pb push_back

typedef long long llt;
int const SIZE = 100100;

int A[SIZE], B[SIZE], Limit[SIZE];
int N, M, K;
vector<int> Vec[SIZE];

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase = getUnsigned();
    while(nofkase--){
        fill(B, B + (N = getUnsigned()), 0);
        fill(Limit, Limit+K+1, 0);
        K = getUnsigned();
        for(int i=1;i<=K;++i)Vec[i].clear();
        M = getUnsigned();

        int round = M / N;   // 轮数
        int left = M % N; // 余数

        for(int i=0;i<N;++i){
            Vec[A[i] = getUnsigned()].pb(i);
            if(A[i]==79){
                int x=5;
            }
            if(i<left) Limit[A[i]] = Vec[A[i]].size();
        }

        for(int sz,i=1;i<=K;++i)if(sz=Vec[i].size()){
                if(274==i){
                    int x=5;
                }
            if(sz&1){ // 奇数
                int r = round / 2;
                for(int j=0;j<sz;++j){
                    B[Vec[i][j]] = r;
                }
                if(round&1){
                    for(int j=1;j<sz;j+=2){
                        ++B[Vec[i][j]];
                    }
                    for(int j=0;j<Limit[i];j+=2){
                        ++B[Vec[i][j]];
                    }
                }else{
                    for(int j=1;j<Limit[i];j+=2){
                        ++B[Vec[i][j]];
                    }
                }
            }else{ // 偶数
                for(int j=1;j<sz;j+=2){
                    B[Vec[i][j]] = round;
                }
                for(int j=1;j<Limit[i];j+=2){
                    ++B[Vec[i][j]];
                }
            }
        }

        printf("%d", *B);
        for(int i=1;i<N;++i)printf(" %d", B[i]);
        printf("\n");
    }
    return 0;
}
