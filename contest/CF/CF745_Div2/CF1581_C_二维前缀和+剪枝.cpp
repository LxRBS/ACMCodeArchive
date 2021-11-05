/**
 * 给定一个01矩阵，要求通过修改矩阵元素弄出这样一个区域
 *  11...1
 * 1      1
 * .      .
 * 1      1
 *  11...1 
 * 即，中间的部分全是0，四边为1，注意四角随意
 * 问总高度要>=5，总宽度要>=4
 * 问最少修改几个元素可以得到符合条件的区域
 * 做一个四重循环，遍历所有可能的矩形区域
 * 对于内部空间修改次数实际上就是子矩阵和
 * 对于四边，修改次数是全和减去子矩阵和
 * 因此用二维前缀和，每次可以O(1)
 * 这样就是O(n^4)，n在400，仍然超时
 * 注意到在某个位置，如果此时内部修改的次数加上上左两边的修改次数已经超过了答案，
 * 则显然不用再往下了，注意只能break一层循环。这是一个剪枝
*/
#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
int const SIZE = 13;
#else 
int const SIZE = 410;
#endif

int N, M;
int A[SIZE][SIZE];
int B[SIZE][SIZE];

inline int calc(int r0, int c0, int r1, int c1){
	return B[r1][c1] - (r0?B[r0-1][c1]:0) + (r0&&c0?B[r0-1][c0-1]:0) - (c0?B[r1][c0-1]:0);
}

inline int check(int r0, int c0, int r1, int c1, int &other){
	int ans = other = 0;

    /// 第r0行[c0+1, c1-1]
	int t = calc(r0, c0+1, r0, c1-1);
	ans += c1 - 1 - c0 - t;
	other += c1 - 1 - c0 - t;
	/// 第r1行
	t = calc(r1, c0+1, r1, c1-1);
	ans += c1 -1 -c0 - t;
	/// 第c0列[r0+1, r1-1]
	t = calc(r0+1, c0, r1-1, c0);
	ans += r1 - 1 - r0 - t;
	other += r1 - 1 - r0 - t;
	/// 第c1列
	t = calc(r0+1, c1, r1-1, c1);
	ans += r1 - 1 - r0 - t;
	/// 中间
	t = calc(r0+1, c0+1, r1-1, c1-1);
	ans += t;
	other += t;
	return ans;
}

int proc(){
    B[0][0] = A[0][0];
	for(int i=1;i<N;++i) B[i][0] = B[i-1][0] + A[i][0];
	for(int i=1;i<M;++i) B[0][i] = B[0][i-1] + A[0][i];
	for(int i=1;i<N;++i)for(int j=1;j<M;++j){
		B[i][j] = B[i-1][j] + B[i][j-1] - B[i-1][j-1] + A[i][j];
	}

    int ans = N * M;
	for(int tmp, tmp2, i=0;i<N-4;++i)for(int j=0;j<M-3;++j)
	for(int u=i+4;u<N;++u)for(int v=j+3;v<M;++v){
		tmp = check(i, j, u, v, tmp2);
		if(tmp < ans){
			ans = tmp;
			continue;
		}
		if(ans < tmp2){
			break;
		}
	}
	return ans;
}

char T[SIZE];
int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase;
	scanf("%d", &nofkase);
	while(nofkase--){
        scanf("%d%d", &N, &M);
		for(int i=0;i<N;++i){
			scanf("%s", T);
			for(int j=0;j<M;++j){
				A[i][j] = T[j] - '0';
			}
		}
		printf("%d\n", proc());
	}
	return 0;
}