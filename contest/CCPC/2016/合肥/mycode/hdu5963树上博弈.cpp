/*
  ���ϲ��ģ�ÿ����һ����ÿһ��:
  ѡ��һ����Ϊ���Ľڵ��ҵ�����ȨΪ1��Ȼ�󽫸õ㵽����·����ת
  �����ߵ�����
  40000���㣬1s
  ����һ�����������ֲ�����
  0 x:��xΪ����˭���ʤ��Ů���к�
  1 xyz����xy�ߵ�Ȩֵ�޸ĳ�z
  ��Ϊ��ÿһ��������Ҫ����һ�Σ������ж�ʤ��Ӧ����һ����Լ򵥵���
  ����rΪ���ڵ㣬��x��1�ߺ�y��0�ߡ�
  վ�����ֵĽǶȣ����������ĳ��1�߽����Ϊ0��
  �����ֻ�����ֿ��ܣ���һ����·���ߣ��ڶ��ֲ������²�ڵ㽫0�ٱ��1
  ���ֵ�ÿһ���ڶ��ֲ��������ֶ���Ȼ��·���ߡ�
  �������ֻ��1��1�ߣ����������²����Σ����ֶ���ʤ
  ��һ����xΪ���������ֱ�ʤ
  ���Ը���û�л���������ֻ���ѯָ���ڵ㵱ǰ�ߵ�Ȩֵ����
*/
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

vector<int> Graph[40010];
int N,M;

//��xΪ������ѯʤ��
void f0(int x){
    //����Ůʤ��ż����ʤ
    printf(Graph[x].size()&1?"Girls win!\n":"Boys win!\n");
}

//v��һ�У�to����һ���㣬w��0����1
void f(vector<int>&v,int to,int w){
    vector<int>::iterator it = v.begin();
    while(it!=v.end()&&*it!=to)++it;
    if(v.end()==it){
        if(w) v.push_back(to);
    }else{
        if(!w) v.erase(it);
    }
}

void f1(int x,int y,int z){
    f(Graph[x],y,z);
    f(Graph[y],x,z);
}

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase = getUnsigned();
    while(nofkase--){
        N = getUnsigned();
        M = getUnsigned();
        for(int i=1;i<=N;++i)Graph[i].clear();

        for(int i=1;i<N;++i){
            int a=getUnsigned();
            int b=getUnsigned();
            int c=getUnsigned();
            if(c){
                Graph[a].push_back(b);
                Graph[b].push_back(a);
            }
        }

        while(M--){
            int op = getUnsigned();
            int x=getUnsigned();
            if(op){
                int y=getUnsigned();
                int z=getUnsigned();
                f1(x,y,z);
            }else{
                f0(x);
            }
        }
    }
    return 0;
}


