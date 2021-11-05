/*
    本质上是一个集合求交
*/
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

typedef vector<int> vit;
typedef vector<vit> v2it;

void dispVec(vit const&v){
    for(vit::const_iterator it=v.begin();it!=v.end();++it){
        printf("%d ",*it);
    }
    printf("\n");
}

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

v2it Monkeys;
v2it Places;

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase = getUnsigned();
    for(int kase=0;kase<nofkase;++kase){
        if (kase) printf("\n");

        int n = getUnsigned();
        int m = getUnsigned();

        Monkeys.assign(51,vit());
        Places.assign(51,vit());

        for(int i=0;i<n;++i){
            int x = getUnsigned();
            Monkeys[x].push_back(getUnsigned());
        }

        for(int i=0;i<m;++i){
            int x = getUnsigned();
            Places[getUnsigned()].push_back(x);
        }

        for(int i=1;i<=50;++i){
            sort(Monkeys[i].begin(),Monkeys[i].end());
            Monkeys[i].erase(unique(Monkeys[i].begin(),Monkeys[i].end()),Monkeys[i].end());
            sort(Places[i].begin(),Places[i].end());
            Places[i].erase(unique(Places[i].begin(),Places[i].end()),Places[i].end());

            //printf("%d: ",i);dispVec(Monkeys[i]);
            //printf("%d: ",i);dispVec(Places[i]);
        }

        for(int i=1;i<=50;++i)for(int j=1;j<=50;++j){
            vit v;
            set_intersection(Monkeys[i].begin(),Monkeys[i].end(),Places[j].begin(),Places[j].end(),back_inserter(v));
            if (!v.empty()) printf("%d %d\n",i,j);
        }
    }
    return 0;
}
