/**
    1��n����վ��
    1�˳����ͣ����x��վ��
    �����ͣ������յ㼰��֮��ļ�����ڵ���x������������վ
    ����m�˳���
    ������Ҫ���ٸ����������������
    ͣ��վ�ļ��������ڲ�ͣ���ĳ�վ
    ������һ����
    ��������
*/
#include <bits/stdc++.h>
using namespace std;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

int InDeg[1100];
int G[1010][1010];
int D[1100];

int main(){
    //freopen("1.txt","r",stdin);
    int n = getUnsigned();
    int m = getUnsigned();
    while(m--){
        int s = getUnsigned();
        vector<int> a,b;
        a.push_back(getUnsigned());
        for(int i=1;i<s;++i){
            int t = getUnsigned();
            for(int j=a.back()+1;j<t;++j)b.push_back(j);
            a.push_back(t);
        }
        for(vector<int>::const_iterator it=a.begin();it!=a.end();++it){
            for(vector<int>::const_iterator jt=b.begin();jt!=b.end();++jt){
                G[*it][*jt] = 1;
            }
        }
    }
    for(int i=1;i<=n;++i)for(int j=1;j<=n;++j)InDeg[j]+=G[i][j];
    //��һ����������
    int ans = 0;
    queue<int> q;
    for(int i=1;i<=n;++i)if(0==InDeg[i])q.push(i);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int i=1;i<=n;++i)if(G[u][i]){
            if(0==--InDeg[i]){
                q.push(i);
                ans = max(ans, D[i] = D[u] + 1);
            }
        }
    }
    printf("%d\n",ans+1);
    return 0;
}
