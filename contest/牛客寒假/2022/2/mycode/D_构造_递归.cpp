/**
 * Ҫ����ֱ��������N��N�������Σ�ǡ��ֻ��һ���ܵĻ����������
 * ��ȻN��3�ı����ǲ��ܵ�
 * ���ǹ��죬����ֱ������Թ���һ��2��3�ľ���
 * ���N�ǽϴ������ģ3��2���պ����þ��ΰ�������ΧһȦ����ʣ��һ��(N-4)��(N-4)��������
 * ���N�ǽϴ������ģ3��1����Ҫ��������Χ��Ȧ����ʣ��һ��(N-8)��(N-8)��������
 * ��˵ݹ鼴�ɣ�����N�Ƚ�С�����������
*/
#include <bits/stdc++.h>
using namespace std;

int N;

int A[1010][1010];

void proc1(int, int, int);

void proc2(int s, int e, int start){ // ��33...32��
    int n = e - s + 1;
	if(2 == n){
		A[s][s] = A[s][e] = A[e][s] = start++;
		return;
	}

	int cnt = n / 3;
	/// ��
	for(int c=s,i=0;i<cnt;++i,c+=3){
		A[c][s] = A[c][s+1] = A[c+1][s] = start++;
		A[c+1][s+1] = A[c+2][s] = A[c+2][s+1] = start++;
	}
    /// ��
	for(int c=s,i=0;i<cnt;++i,c+=3){
        A[e-1][c] = A[e-1][c+1] = A[e][c] = start++;
		A[e][c+1] = A[e][c+2] = A[e-1][c+2] = start++;
	}
	/// ����
	for(int c=e,i=0;i<cnt;++i,c-=3){
		A[c][e-1] = A[c][e] = A[c-1][e] = start++;
		A[c-1][e-1] = A[c-2][e-1] = A[c-2][e] = start++;
	}
	/// �ٺ�
	for(int c=e,i=0;i<cnt;++i,c-=3){
		A[s][c] = A[s+1][c] = A[s+1][c-1] = start++;
		A[s][c-1] = A[s][c-2] = A[s+1][c-2] = start++;
	}
	/// ����Χ���Ժ�
	proc1(s+2, e-2, start);
}

/// ����4��4
void proc4(int s, int e, int start){
    A[s][s] = A[s][s+1] = A[s+1][s] = start++;
	A[s+2][s] = A[s+3][s] = A[s+3][s+1] = start++;
	A[s+3][s+2] = A[s+3][s+3] = A[s+2][s+3] = start++;
	A[s][s+2] = A[s][s+3] = A[s+1][s+3] = start++;
	A[s+1][s+1] = A[s+2][s+1] = A[s+2][s+2] = start++;
}

void proc1(int s, int e, int start){ // ��33...322��
	int n = e - s + 1;
    if(1 == n) return; // should not here
	if(4 == n){
		return (void)proc4(s, e, start);
	}

	int cnt = (n - 4) / 3;
	/// ��
	for(int c=s,i=0;i<cnt;++i,c+=3){
		A[c][s] = A[c][s+1] = A[c+1][s] = start++;
		A[c+1][s+1] = A[c+2][s] = A[c+2][s+1] = start++;

		A[c][s+2] = A[c][s+3] = A[c+1][s+2] = start++;
		A[c+1][s+3] = A[c+2][s+2] = A[c+2][s+3] = start++;
	}
    /// ��
	for(int c=s,i=0;i<cnt;++i,c+=3){
        A[e-1][c] = A[e-1][c+1] = A[e][c] = start++;
		A[e][c+1] = A[e][c+2] = A[e-1][c+2] = start++;

        A[e-3][c] = A[e-3][c+1] = A[e-2][c] = start++;
		A[e-2][c+1] = A[e-2][c+2] = A[e-3][c+2] = start++;		
	}
	/// ����
	for(int c=e,i=0;i<cnt;++i,c-=3){
		A[c][e-1] = A[c][e] = A[c-1][e] = start++;
		A[c-1][e-1] = A[c-2][e-1] = A[c-2][e] = start++;

		A[c][e-3] = A[c][e-2] = A[c-1][e-2] = start++;
		A[c-1][e-3] = A[c-2][e-3] = A[c-2][e-2] = start++;		
	}
	/// �ٺ�
	for(int c=e,i=0;i<cnt;++i,c-=3){
		A[s][c] = A[s+1][c] = A[s+1][c-1] = start++;
		A[s][c-1] = A[s][c-2] = A[s+1][c-2] = start++;

		A[s+2][c] = A[s+3][c] = A[s+3][c-1] = start++;
		A[s+2][c-1] = A[s+2][c-2] = A[s+3][c-2] = start++;		
	}
	if(7 == n) return; // 7����ֱ�ӷ�����
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
