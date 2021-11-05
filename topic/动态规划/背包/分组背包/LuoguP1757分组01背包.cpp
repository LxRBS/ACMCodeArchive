/**
   分组背包，模板题
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

map<int,vector<int> > Zu;
int Cost[1010];
int Gain[1010];
int D[1010];
int main(){
    //freopen("1.txt","r",stdin);
    int m = getUnsigned();
    int n = getUnsigned();
    for(int i=1;i<=n;++i){
        Cost[i] = getUnsigned();
        Gain[i] = getUnsigned();
        Zu[getUnsigned()].push_back(i);
    }
    //for每一组
    //for每个体积
    //for每组里面的每个物品
    for(map<int,vector<int> >::const_iterator it=Zu.begin();it!=Zu.end();++it){
        vector<int>const&vec=it->second;
        for(int v=m;v>=0;--v){
            for(vector<int>::const_iterator jt=vec.begin();jt!=vec.end();++jt){
                if(v-Cost[*jt]>=0){
                    D[v] = max(D[v],D[v-Cost[*jt]]+Gain[*jt]);
                }
            }
        }
    }
    printf("%d\n",D[m]);
    return 0;
}
