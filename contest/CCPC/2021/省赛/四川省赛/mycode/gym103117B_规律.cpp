/**
    N����ÿ������һ��ϲ�ã�����Ai
    N���������������ܹ�����M�֣�M��1E9
    ��i���˲����������������Ai�����i���˵������1������Ai�ӳ���������
    ���û��Ai����Ai���룬���治��
    ��M�ֺ�ÿ���˵�����
    M�ܴ󣬲���ģ�⡣
    ��ÿһ��Ai�������м���
    ����ֻ��һ����ϲ��Ai������˵�������Ȼ�Ǹ��˵Ĳ�������/2
    �����������ϲ�ã���ǰһ���˵�������0����һ���˵������Ǹ��˵Ĳ�������
    �����t�����й�ͬϲ����t��ż�����򰴶Լ��㼴��
    �����t�����й�ͬϲ����t����������û���֣�ÿ���˵������1
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

        int round = M / N;   // ����
        int left = M % N; // ����

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
            if(sz&1){ // ����
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
            }else{ // ż��
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
