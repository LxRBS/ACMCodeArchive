//���͵�ĸ����������Ϊ50(����)���µ�ϵ����
#include <cstdio>
#include <algorithm>
#include <numeric>
using namespace std;

int A[26];
int G[51];//����ʽϵ��
int T[51];//��ʱ����
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		for(int i=0;i<26;++i)scanf("%d",A+i);

        //���Ƚ�G����Ϊ��һ��ʽ�ӣ�Ҳ������ĸA��
		fill(G,G+A[0]+1,1);
		fill(G+A[0]+1,G+51,0);
		fill(T,T+51,0);

		//���ˣ����ǵ������ʽ��ϵ��ҪôΪ1ҪôΪ0����˲���д������Ķ���ʽ�˷�
		for(int i=1;i<26;++i){
			for(int j=0;j<51;++j)for(int k=0;k<=A[i]*(i+1)&&k<51;k+=i+1){
				if ( j + k < 51 )//ֻ����50�μ����µ�
				    T[j+k] += G[j];
			}
			//����ʱ������ֵ������G
			copy(T,T+51,G);
            //����
			fill(T,T+51,0);
		}

		//�������Ϊ0�δ���û����ĸ��Ҳ�Ͳ���һ������
		printf("%d\n",accumulate(G+1,G+51,0));
	}
	return 0;
}