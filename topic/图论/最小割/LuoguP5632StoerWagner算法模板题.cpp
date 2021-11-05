/**
    ȫ����С�StoerWagner�㷨��ģ����
*/
#include <bits/stdc++.h>
using namespace std;

typedef int weight_t;
int const SIZE_OF_VERTIECES = 650;
weight_t const INF = 2000000000;

weight_t Graph[SIZE_OF_VERTIECES][SIZE_OF_VERTIECES];//ͼ���ڽӱ�������1��ʼ
weight_t _W[SIZE_OF_VERTIECES];//Ȩֵ���飬��������
bool _Flag[SIZE_OF_VERTIECES];//��������,Flag[i]Ϊ���ʾ��i�Ѿ������
bool _Behalf[SIZE_OF_VERTIECES];//��������,Behalf[i]Ϊ��˵����i���Ƕ����Ķ��Ǳ������˱�ĵ���

inline void initGraph(int vn=0){
    memset(Graph,0,sizeof(Graph));
}

//�������������������������С��ֵ�Լ�S��T,O(N*N)
weight_t contract(int vn,int&s,int&t){
    fill(_W,_W+vn+1,0);
    fill(_Flag,_Flag+vn+1,false);

    weight_t ans;
    for(int j,k,i=1;i<=vn;++i){
        k = 0;
        //�ҵ������м�������Ȩֵ���ĵ�k
        for(j=1;j<=vn;++j)if(!_Behalf[j]&&!_Flag[j]&&(!k||_W[j]>_W[k])) k = j;
        if (!k) break;
        //������¼s��t�����ҽ�k�����м���
        s = t; _Flag[t=k] = true;
        ans = _W[k];
        for(j=1;j<=vn;++j)if(!_Behalf[j]&&!_Flag[j]) _W[j] += Graph[k][j];
    }
    return ans;
}

//vnΪ����������w��flag��behalf�Ǹ�������
weight_t StoerWagner(int vn){
    weight_t ans = INF;
    fill(_Behalf,_Behalf+vn+1,0);

    for(int s,t,i=1;i<vn;++i){
        ans = min(ans,contract(vn,s,t));
        //˵��ͼ����Ͳ���ͨ
        if ( 0 == ans ) return 0;
        //��t����s��
        _Behalf[t] = true;
        for(int j=1;j<=vn;++j)if(!_Behalf[j])Graph[s][j] += Graph[t][j],Graph[j][s] += Graph[j][t];
    }
    return ans;
}

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

int main(){
    int n = getUnsigned();
    int m = getUnsigned();
    while(m--){
        int a = getUnsigned();
        int b = getUnsigned();
        Graph[a][b] = Graph[b][a] = getUnsigned();
    }
    printf("%d\n",StoerWagner(n));
    return 0;
}
