/**
 * 要求用直角弯铺满N×N的正方形，恰好只空一格。能的话输出方案。
 * 显然N是3的倍数是不能的
 * 考虑构造，两个直角弯可以构成一个2×3的矩形
 * 如果N是较大的数且模3余2，刚好能用矩形把正方形围一圈，且剩下一个(N-4)×(N-4)的正方形
 * 如果N是较大的数且模3余1，就要把正方形围两圈，且剩下一个(N-8)×(N-8)的正方形
 * 因此递归即可，对于N比较小的情况，特判
*/
#include <bits/stdc++.h>
using namespace std;

int N;

int A[1010][1010];

void proc1(int, int, int);

void proc2(int s, int e, int start){ // 按33...32排
    int n = e - s + 1;
	if(2 == n){
		A[s][s] = A[s][e] = A[e][s] = start++;
		return;
	}

	int cnt = n / 3;
	/// 竖
	for(int c=s,i=0;i<cnt;++i,c+=3){
		A[c][s] = A[c][s+1] = A[c+1][s] = start++;
		A[c+1][s+1] = A[c+2][s] = A[c+2][s+1] = start++;
	}
    /// 横
	for(int c=s,i=0;i<cnt;++i,c+=3){
        A[e-1][c] = A[e-1][c+1] = A[e][c] = start++;
		A[e][c+1] = A[e][c+2] = A[e-1][c+2] = start++;
	}
	/// 再竖
	for(int c=e,i=0;i<cnt;++i,c-=3){
		A[c][e-1] = A[c][e] = A[c-1][e] = start++;
		A[c-1][e-1] = A[c-2][e-1] = A[c-2][e] = start++;
	}
	/// 再横
	for(int c=e,i=0;i<cnt;++i,c-=3){
		A[s][c] = A[s+1][c] = A[s+1][c-1] = start++;
		A[s][c-1] = A[s][c-2] = A[s+1][c-2] = start++;
	}
	/// 四周围上以后
	proc1(s+2, e-2, start);
}

/// 处理4×4
void proc4(int s, int e, int start){
    A[s][s] = A[s][s+1] = A[s+1][s] = start++;
	A[s+2][s] = A[s+3][s] = A[s+3][s+1] = start++;
	A[s+3][s+2] = A[s+3][s+3] = A[s+2][s+3] = start++;
	A[s][s+2] = A[s][s+3] = A[s+1][s+3] = start++;
	A[s+1][s+1] = A[s+2][s+1] = A[s+2][s+2] = start++;
}

void proc1(int s, int e, int start){ // 按33...322排
	int n = e - s + 1;
    if(1 == n) return; // should not here
	if(4 == n){
		return (void)proc4(s, e, start);
	}

	int cnt = (n - 4) / 3;
	/// 竖
	for(int c=s,i=0;i<cnt;++i,c+=3){
		A[c][s] = A[c][s+1] = A[c+1][s] = start++;
		A[c+1][s+1] = A[c+2][s] = A[c+2][s+1] = start++;

		A[c][s+2] = A[c][s+3] = A[c+1][s+2] = start++;
		A[c+1][s+3] = A[c+2][s+2] = A[c+2][s+3] = start++;
	}
    /// 横
	for(int c=s,i=0;i<cnt;++i,c+=3){
        A[e-1][c] = A[e-1][c+1] = A[e][c] = start++;
		A[e][c+1] = A[e][c+2] = A[e-1][c+2] = start++;

        A[e-3][c] = A[e-3][c+1] = A[e-2][c] = start++;
		A[e-2][c+1] = A[e-2][c+2] = A[e-3][c+2] = start++;		
	}
	/// 再竖
	for(int c=e,i=0;i<cnt;++i,c-=3){
		A[c][e-1] = A[c][e] = A[c-1][e] = start++;
		A[c-1][e-1] = A[c-2][e-1] = A[c-2][e] = start++;

		A[c][e-3] = A[c][e-2] = A[c-1][e-2] = start++;
		A[c-1][e-3] = A[c-2][e-3] = A[c-2][e-2] = start++;		
	}
	/// 再横
	for(int c=e,i=0;i<cnt;++i,c-=3){
		A[s][c] = A[s+1][c] = A[s+1][c-1] = start++;
		A[s][c-1] = A[s][c-2] = A[s+1][c-2] = start++;

		A[s+2][c] = A[s+3][c] = A[s+3][c-1] = start++;
		A[s+2][c-1] = A[s+2][c-2] = A[s+3][c-2] = start++;		
	}
	if(7 == n) return; // 7可以直接反悔了
    proc2(s+4, e-4, start);
}

void proc(){
	int t = N % 3;
	if(!t) return (void)puts("NO");

	if(2 == t){
		proc2(0, N-1, 1);
	}else if(1 == t){
		proc1(0, N-1, 1);
	}

	puts("YES");
	for(int i=0;i<N;++i){
		for(int j=0;j<N;++j){
			printf("%d ", A[i][j]);
		}
		printf("\n");
	}
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    scanf("%d", &N);
	proc();
	
    return 0;
}