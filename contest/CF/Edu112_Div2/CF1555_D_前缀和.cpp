/**
 * һ���ַ��������������2�����ϵĻ����Ӵ�����Ϊbeautiful
 * ����һ���ַ�����ֻ��a/b/c������ĸ
 * ÿ�β������Ըı�����һ����ĸ������[s, e]
 * ������Ҫ���β��������Խ�[s, e]�Ӵ���Ϊbeautiful
 * �ж��ѯ�ʡ�
 * ��Ϊֻ��������ĸ�����ֱ�����һ�����У�������������
 * ����ÿ��[s, e]ֻ��6�ֿ��ܵĸķ���
 * ��Ҫͳ��[s, e]��abcabc��acbacb��bacbac��bcabca��...��ͬ��ĸ������
 * ����Ԥ���������ַ�������ǰ׺�ͼ�¼��
 * O(1)�ش��ѯ 
*/
#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
int const SIZE = 13;
#else
int const SIZE = 200010;
#endif

int N, M;
char A[SIZE] = {0};
int B[6][SIZE] = {0};

int proc(int s, int e){
	int ans = N;
	for(int i=0;i<6;++i){
		ans = min(ans, B[i][e] - (s?B[i][s-1]:0));
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    scanf("%d%d%s", &N, &M, A);
	char t[] = "abc";
	int k = 0;
	do{
		B[k][0] = t[0] != A[0] ? 1 : 0;
        for(int i=1;i<N;++i){
			B[k][i] = B[k][i-1] + (t[i%3]!=A[i]?1:0);
		}
		++k;
	}while(next_permutation(t, t+3));

    for(int a, b, i=1;i<=M;++i){
		scanf("%d%d", &a, &b);
		printf("%d\n", proc(--a, --b));
	}
    return 0;
}