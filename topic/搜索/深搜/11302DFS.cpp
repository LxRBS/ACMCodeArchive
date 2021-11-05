#include <cstdio>
#include <algorithm>
using namespace std;

struct _t{
    int cnt;//ÿ�����ӿ������׵�����
	int size[3][2];//���ܵĳߴ�
}Box[10];

int Ans;     //��
bool Flag[10];//��־λ
bool isHalt;//�Ƿ���ǰ��ֹ

void input(int n){
	for(int i=0;i<n;++i){
		int a[3];
		scanf("%d%d%d",a,a+1,a+2);
        sort(a,a+3);

		//ֻ��һ�ֳߴ�
		if ( a[0] == a[2] ){
			Box[i].cnt = 1;
			Box[i].size[0][0] = Box[i].size[0][1] = a[0];
			continue;
		}

		//���ֳߴ�
		if ( a[0] == a[1] || a[1] == a[2] ){
			Box[i].cnt = 2;
			Box[i].size[0][0] = a[0];
			Box[i].size[0][1] = a[1];
			Box[i].size[1][0] = a[1];
			Box[i].size[1][1] = a[2];
			continue;
		}

		//���ֳߴ�
		Box[i].cnt = 3;
		Box[i].size[0][0] = a[0];
		Box[i].size[0][1] = a[1];
		Box[i].size[1][0] = a[0];
		Box[i].size[1][1] = a[2];
		Box[i].size[2][0] = a[1];
		Box[i].size[2][1] = a[2];
	}
    return;
}

//deepΪ�Ѿ����õ���������nΪ�����ȣ�s1,s2Ϊ��ǰ�ߴ�
void dfs(int deep,int n,int s1,int s2){
	if ( deep == n ) {
		Ans = n;
        isHalt = true;
		return;
	}

	bool isAva = false;//�ж���һ�εݹ����Ƿ��������
	for(int i=0;i<n;++i){
		//��������Ѿ�ʹ�ã����Թ�
		if ( Flag[i] ) continue;

		for(int j=0;j<Box[i].cnt;++j){
			//������ӵĳߴ粻���ʣ����Թ�
            if ( s1 < Box[i].size[j][0] || s2 < Box[i].size[j][1] )
				continue;

			//������
			Flag[i] = true;
			isAva = true;
			dfs(deep+1,n,Box[i].size[j][0],Box[i].size[j][1]);
			if ( isHalt ) return;
			Flag[i] = false;
		}
	}

	//�����һ�εݹ���û�аڹ��κ����ӣ�����Լ�¼�м���
	if ( !isAva && deep > Ans ) Ans = deep;
}

int main(){
	int n,kase = 0;
	while( scanf("%d",&n) && n ){
        input(n);

		Ans = 0;
		fill(Flag,Flag+n,false);
		isHalt = false;

		for(int i=0;i<n;++i){
			Flag[i] = true;
			for(int j=0;j<Box[i].cnt;++j){
			    //�Ե�i�����ӵĵ�j��Ϊ��
			    int s1 = Box[i].size[j][0];
			    int s2 = Box[i].size[j][1];

			    dfs(1,n,s1,s2);
			}
			Flag[i] = false;
		}

		++kase;
		printf("Case %d: %d\n",kase,Ans);
	}
	return 0;
}