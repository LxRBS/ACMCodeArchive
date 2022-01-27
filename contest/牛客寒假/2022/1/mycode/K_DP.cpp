/**
 * 一段，每格可能有RGB3种颜色
 * 再给定一个标记数组Ai，对于i-2,i-1,i的连续三格
 * 如果绿色比红色多，Ai就是G；绿少红多就是R；一样多就是B
 * 现在给定A，问绿色最多是多少。N在1E5
 * 不能贪心，搜索肯定超时
 * Diabc表示当前位置i，结尾颜色分别为abc时绿色最多的数量
 * 则在满足Ai的情况下，Diabc = max(D[i-1][b][c][k]),其中k=RGB
*/
#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
int const SIZE = 20;
#else
int const SIZE = 110000;
#endif

int const R = 0;
int const G = 1;
int const B = 2;

int N;
char A[SIZE];

int D[SIZE][4][4][4];

void init(){
	for(int i=0;i<3;++i)for(int j=0;j<3;++j){
		D[0][G][i][j] = 1;
		D[0][R][i][j] = D[0][B][i][j] = 0;
	}
	for(int i=0;i<3;++i){
		D[1][G][G][i] = 2;
		D[1][G][R][i] = D[1][G][B][i] = 1;

        D[1][R][G][i] = 1;
		D[1][R][R][i] = D[1][R][B][i] = 0;

		D[1][B][G][i] = 1;
		D[1][B][R][i] = D[1][B][B][i] = 0;
	}
}

inline bool isOK(int a, int b, int c, int idx){
    int cnt[3] = {0};
	++cnt[a]; ++cnt[b]; ++cnt[c];
	if(A[idx] == 'G' && cnt[G] > cnt[R]) return true;
	if(A[idx] == 'R' && cnt[G] < cnt[R]) return true;
	if(A[idx] == 'B' && cnt[G] == cnt[R]) return true;
	return false;
}

int main(){
#ifndef ONLINE_JUDGE    
    freopen("1.txt","r",stdin);
#endif
    scanf("%d%s", &N, A);
    
	init();
    for(int t,z,i=2;i<N;++i){
		for(int a=0;a<3;++a)for(int b=0;b<3;++b)for(int c=0;c<3;++c){
			D[i][a][b][c] = -1;
			int & d = D[i][a][b][c];

			if(isOK(a, b, c, i)){
                t = a == G ? 1 : 0;
				if(-1 != (z=D[i-1][b][c][G])){
                    d = max(t+z, d);
				}    
				if(-1 != (z=D[i-1][b][c][R])){
					d = max(t+z, d);
				}
				if(-1 != (z=D[i-1][b][c][B])){
					d = max(t+z, d);
				}
			}
		}
	}

	int ans = -1;
	for(int a=0;a<3;++a)for(int b=0;b<3;++b)for(int c=0;c<3;++c){
		ans = max(ans, D[N-1][a][b][c]);
	}
	cout<<ans<<endl;
    return 0;
}

