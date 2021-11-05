//01������K�Ž�
#include <cstdio>
#include <vector>
#include <cstring>
#include <functional>
#include <algorithm>
using namespace std;

typedef int gains_t;//type of gains

int N,V,K;
int Tmp[31];//��ʱ����
//one iteration of 01 knapsack problem
//d is the result array
//maxv is the upper bound of the cost namely it is volume in classical problem
//cost is the current cost
//gains is the current gains
//cnt���ڼ�¼ÿһ��v���Ž���еĳ���
void zeroOneKnapsack(gains_t (*d)[31],int maxv,int cost,gains_t gains,int cnt[]){
    for(int v=maxv;v>=cost;--v){
        //d[v] = max(d[v],d[v-cost]+gains);
        //����׼01�����޸ĳɶ��м���
        int dv = v - cost;
        for(int i=0;i<cnt[dv];++i){
            Tmp[i] = d[dv][i] + gains;//�˴�Ҫʹ����ʱ����
        }

        //�ϲ�d[v]��Tmp
        vector<int> vec(cnt[v]+cnt[dv]);
        merge(d[v],d[v]+cnt[v],Tmp,Tmp+cnt[dv],vec.begin(),greater<int>());
        //�ظ���ȡֵ������������K����ֵ������
        vector<int>::iterator it = unique(vec.begin(),vec.end());
        if ( vec.begin() + K < it ) it = vec.begin() + K;
        cnt[v] = copy(vec.begin(),it,d[v]) - d[v];
    }
}

int Gain[110],Cost[110];
void read(){
    scanf("%d%d%d",&N,&V,&K);
    for(int i=0;i<N;++i) scanf("%d",Gain+i);
    for(int i=0;i<N;++i) scanf("%d",Cost+i);
}

int D[1010][31];//Dvk��ʾǰi����Ʒ�����Ϊv�ĵ�k�Ž⣬����iά���ǹ�����
int Cnt[1010];//Cntv���ڼ�¼���v���Ž����
void dp(){
    memset(D,0,sizeof(D));
    fill(Cnt,Cnt+V+1,1);

    for(int i=0;i<N;++i) zeroOneKnapsack(D,V,Cost[i],Gain[i],Cnt);
}

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);
    while(nofkase--){
        read();
        dp();
        printf("%d\n",D[V][K-1]);
    }
    return 0;
}
