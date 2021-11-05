/**
 * ����һ��01����Ҫ��ͨ���޸ľ���Ԫ��Ū������һ������
 *  11...1
 * 1      1
 * .      .
 * 1      1
 *  11...1 
 * �����м�Ĳ���ȫ��0���ı�Ϊ1��ע���Ľ�����
 * ���ܸ߶�Ҫ>=5���ܿ��Ҫ>=4
 * �������޸ļ���Ԫ�ؿ��Եõ���������������
 * ��һ������ѭ�����������п��ܵľ�������
 * �����ڲ��ռ��޸Ĵ���ʵ���Ͼ����Ӿ����
 * �����ıߣ��޸Ĵ�����ȫ�ͼ�ȥ�Ӿ����
 * ����ö�άǰ׺�ͣ�ÿ�ο���O(1)
 * ��������O(n^4)��n��400����Ȼ��ʱ
 * ע�⵽��ĳ��λ�ã������ʱ�ڲ��޸ĵĴ��������������ߵ��޸Ĵ����Ѿ������˴𰸣�
 * ����Ȼ�����������ˣ�ע��ֻ��breakһ��ѭ��������һ����֦
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

    /// ��r0��[c0+1, c1-1]
	int t = calc(r0, c0+1, r0, c1-1);
	ans += c1 - 1 - c0 - t;
	other += c1 - 1 - c0 - t;
	/// ��r1��
	t = calc(r1, c0+1, r1, c1-1);
	ans += c1 -1 -c0 - t;
	/// ��c0��[r0+1, r1-1]
	t = calc(r0+1, c0, r1-1, c0);
	ans += r1 - 1 - r0 - t;
	other += r1 - 1 - r0 - t;
	/// ��c1��
	t = calc(r0+1, c1, r1-1, c1);
	ans += r1 - 1 - r0 - t;
	/// �м�
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