#include <cstdio>
#include <algorithm>
using namespace std;

bool const F[] = {
    false,true,true,true,false,true,false,true,false,false,
	false,true,false,true,false,false,false,true,false,true,
	false,false,false,true,false,false,false,false,false,true,
	false,true,false,false,false,false,false,true,false,false
};
int N;
int A[21] = {0,1};
bool isUsed[21];
void output(){
	printf("1");
	for(int i=2;i<=N;++i)
		printf(" %d",A[i]);
	printf("\n");
}
void dfs(int depth){
    if ( N + 1 == depth ){
        if ( F[1+A[N]] ) output();
        return;
    }

    for(int i=2;i<=N;++i){
    	if ( isUsed[i] || !F[A[depth-1]+i] ) continue;
        //�仯
    	A[depth] = i;
    	isUsed[i] = true;
    	//�ݹ� 
    	dfs(depth+1);
    	//��ԭ
    	isUsed[i] = false;
    }
}
int main() {
	for(int kase=1;EOF!=scanf("%d",&N);++kase){
        printf("Case %d:\n",kase);
        fill(isUsed,isUsed+N+1,false);
        isUsed[1] = true;
        //��һ����һ����1��ֱ���ѵڶ�����
        dfs(2);
        printf("\n");
	}
	return 0;
}
