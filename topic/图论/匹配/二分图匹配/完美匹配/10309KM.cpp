//Kuhn-Munkres�㷨������ͼ����ƥ�䣨��СȨֵ����slack�Ż�
#include <cstdio>
#include <algorithm>
using namespace std;
#define SIZE 25
typedef int weight_t;

int N;

weight_t G[SIZE][SIZE];//����ͼ����
int Link[SIZE];//Link[i]-i��ʾA��B��ƥ��Ľڵ�
bool FA[SIZE],FB[SIZE];//��¼��Ӧ�ڵ��Ƿ�����������

weight_t LabelA[SIZE];
weight_t LabelB[SIZE];//���
weight_t Slack[SIZE];//B�нڵ���ɳڵ���Сֵ

//dfsʵ���������㷨��nodeΪA�еĽڵ�
//����ֵΪ�Ƿ��������·
bool dfs(int node){
	FA[node] = true;
	for(int i=0;i<N;++i){
		//���Bi��������·
		if ( FB[i] ) continue;
			
		//���node-i֮���д��ڱ�
		if ( LabelA[node]+LabelB[i] == G[node][i] ){
			FB[i] = true;

		    //����ҵ�����·
		    if ( -1 == Link[i] || dfs(Link[i]) ){
			    Link[i] = node;
			    return true;
		    }
		}else{
		    //����Slack
		    Slack[i] = min(Slack[i],LabelA[node]+LabelB[i]-G[node][i]);
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
		fill(Slack,Slack+N,INT_MAX);

		while(1){
			fill(FA,FA+N,false);
			fill(FB,FB+N,false);

			//ƥ��ɹ�
			if ( dfs(i) ) break;

			//���Ҷ���Ŀ��б䶯ֵ
			weight_t delta = INT_MAX;
			for(int j=0;j<N;++j)if(!FB[j]){
				delta = min(delta,Slack[j]);
			}
			//���¶���
			for(int j=0;j<N;++j){
				if ( FA[j] ) LabelA[j] -= delta;
				if ( FB[j] ) LabelB[j] += delta;
				else Slack[j] -= delta;
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
                int x;
				scanf("%d",&x);
				G[i][j] = -x;
			}
		}

		fill(Link,Link+N,-1);
		printf("%d\n",-KM());
	}
	return 0;
}
