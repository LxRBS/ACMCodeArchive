//��MST�ĳ��� 
#include <cstdio>
#include <climits>
#include <algorithm>
using namespace std;

#define SIZE 105

int Graph[SIZE][SIZE];

int D[SIZE];//��i����ǰ���ϵ���С���� 
bool Flag[SIZE];//������ǵ�i�Ƿ��ѱ�ѡ�� 

//n��ʾ������� 
int Prim(int n){
    fill(D,D+n,INT_MAX);
    fill(Flag,Flag+n,false);
    D[0] = 0;
    
    int ret = 0;
    for(int i=0;i<n;++i){
    	int k = -1;
    	for(int j=0;j<n;++j)
    	    if ( !Flag[j] && ( -1 == k || D[j] < D[k] ) )
    	        k = j;
        //k����һ��Ҫ����ĵ�
		ret += D[k];
		Flag[k] = true;
		//����ʣ�µĵ㵽��ǰ���ϵ���̾���
		for(int j=0;j<n;++j)
		    if ( !Flag[j] && Graph[k][j] < D[j] )
			    D[j] = Graph[k][j]; 
	}

	return ret;
}

int main(){
	int n;

	while( EOF != scanf("%d",&n) ){
        for(int i=0;i<n;i++)for(int j=0;j<n;j++)
			scanf("%d",Graph[i]+j);
        printf("%d\n",Prim(n));
	}

	return 0;
}

