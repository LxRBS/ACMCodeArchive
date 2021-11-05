/*
����N���㡣
ÿ��������·��ĵ����������Ϊ��level��
ͳ��ÿ��level�ĵ��������
���밴��y���������y�����x����
*/
#include <cstdio>
#include <algorithm>
using namespace std;

#define SIZE 32002

//��״����
int C[SIZE] = {0};

//Դ����,Ai��ʾ����Ϊi�ĸ���
int A[SIZE] = {0};

//����x�Ķ�����λ�����λ1�������ֵ
int lowbit(int x){
    return x & ( x ^ ( x - 1 ) );
}

//���£�����idx�ڵ�ֵ����v
//��״�����ܳ���Ϊn���±귶Χ��1��n
void update(int idx,int v,int n){
	while( idx <= n ){
	    C[idx] += v;
		idx += lowbit(idx);
	}
}

//��ǰx�����
int sum(int x){
    int s = 0;
	while( x > 0 ){
	    s += C[x];
		x -= lowbit(x);
	}
    return s;
}

int N;
int Ans[SIZE];
int main() {
	while ( EOF != scanf("%d",&N) ){
		fill(Ans,Ans+N,0);
		fill(C,C+SIZE,0);

        for(int i=0;i<N;++i){
        	int x,y;
        	scanf("%d%d",&x,&y);
            ++x;
            ++Ans[sum(x)];
            update(x,1,SIZE);
        }

        for(int i=0;i<N;++i)printf("%d\n",Ans[i]);
	}
	return 0;
}
