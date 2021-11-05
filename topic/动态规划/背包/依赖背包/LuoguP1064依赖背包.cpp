#include <bits/stdc++.h>
using namespace std;

int const INF = 2000000000;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

int N,M;
int ZhuCost[66];
int ZhuGain[66];
vector<int> FuCost[66];
vector<int> FuGain[66];

void read(){
    N = getUnsigned();
    M = getUnsigned();

    int v,p,q;
    for(int i=1;i<=M;++i){
        v = getUnsigned();
        p = getUnsigned();
        if( q=getUnsigned() ){//����
            FuCost[q].push_back(v);
            FuGain[q].push_back(v*p);
        }else{//����
            ZhuGain[i] = ( ZhuCost[i] = v ) * p;
        }
    }
}

int TotalF[33000];
int GroupCnt[66];
int GroupCost[66][33000];
int GroupGain[66][33000];
int Cnt;

int main(){
    //freopen("1.txt","r",stdin);
    read();

    //��ÿһ�������µĸ���������һ��01����
    for(int i=1;i<=M;++i)if(ZhuCost[i]){
        int maxv = N - ZhuCost[i];
        fill(TotalF+1,TotalF+maxv+1,-INF);

        for(unsigned j=0,n=FuCost[i].size();j<n;++j){
            int cost = FuCost[i][j];
            for(int v=maxv;v>=cost;--v){
               TotalF[v] = max(TotalF[v],TotalF[v-cost]+FuGain[i][j]);
            }
        }

        //�����������丽������һ�����鱳��
        int&cnt = GroupCnt[++Cnt];
        int*c = GroupCost[Cnt];
        int*g = GroupGain[Cnt];
        for(int cost=0;cost<=maxv;++cost)if(TotalF[cost]>=0){
            c[++cnt] = cost + ZhuCost[i];
            g[cnt] = TotalF[cost] + ZhuGain[i];
        }
    }

    //��һ�����鱳��
    fill(TotalF,TotalF+N+1,0);
    for(int i=1;i<=Cnt;++i){
        for(int v=N;v>=0;--v){
            for(int j=1;j<=GroupCnt[i];++j)if(v>=GroupCost[i][j]){
                TotalF[v] = max(TotalF[v],TotalF[v-GroupCost[i][j]]+GroupGain[i][j]);
            }
        }
    }

    printf("%d\n",TotalF[N]);
    return 0;
}
