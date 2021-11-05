//Kuhn-Munkres�㷨������ͼ����ƥ�䣬O(N^4)
#include <cstdio>
#include <algorithm>
using namespace std;

#define SIZE 305
typedef int weight_t;

int N;

weight_t G[SIZE][SIZE];//����ͼ����
int Link[SIZE];//Link[i]-i��ʾA��B��ƥ��Ľڵ�
bool FA[SIZE],FB[SIZE];//��¼��Ӧ�ڵ��Ƿ�����������

weight_t LabelA[SIZE];
weight_t LabelB[SIZE];//���

//dfsʵ���������㷨��nodeΪA�еĽڵ�
//����ֵΪ�Ƿ��������·
bool dfs(int node){
	FA[node] = true;
	for(int i=0;i<N;++i){
		//���Bi��������·��node-i֮��û�б�
		if ( FB[i] || LabelA[node]+LabelB[i] != G[node][i] )
			continue;

		FB[i] = true;

		//����ҵ�����·
		if ( -1 == Link[i] || dfs(Link[i]) ){
			Link[i] = node;
			return true;
		}
	}
	return false;
}


//KM�㷨����ƥ�䣬�������Ȩֵ��
int KM(){
	//��ʼ����ţ�LA�������ߵ����Ȩֵ��LB��0
	fill(LabelA,LabelA+N,0);
	fill(LabelB,LabelB+N,0);
	for(int i=0;i<N;++i)for(int j=0;j<N;++j)
			LabelA[i] = max(LabelA[i],G[i][j]);
	
	//��N�������ƥ��
	for(int i=0;i<N;++i){
		while(1){
			fill(FA,FA+N,false);
			fill(FB,FB+N,false);

			//ƥ��ɹ�
			if ( dfs(i) ) break;

			//���Ҷ���Ŀ��б䶯ֵ
			int delta = INT_MAX;
			//Aj���������ϣ�Bk���ڣ�ȡ��ֵ��С��
			for(int j=0;j<N;++j)if(FA[j]){
				for(int k=0;k<N;++k)if(!FB[k]){
					delta = min(delta,LabelA[j]+LabelB[k]-G[j][k]);
				}
			}
			//���¶���
			for(int j=0;j<N;++j){
				if ( FA[j] ) LabelA[j] -= delta;
				if ( FB[j] ) LabelB[j] += delta;
			}
		}
	}

	//���ؽ��
	int ret = 0;
	for(int i=0;i<N;++i)
		ret += G[Link[i]][i];
	return ret;
}

int main(){
	while( EOF != scanf("%d",&N) ){
		for(int i=0;i<N;++i){
			for(int j=0;j<N;++j){
				scanf("%d",G[i]+j);
			}
		}

		fill(Link,Link+N,-1);
		printf("%d\n",KM());
	}
	return 0;
}