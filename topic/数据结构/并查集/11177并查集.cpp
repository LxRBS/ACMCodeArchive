//简单的并查集
#include <iostream>
#include <set>
using namespace std;

#define SIZE 300001
int Father[SIZE] = {0};
int Cnt[SIZE] = {0};

void init(int n){
	for(int i=1;i<=n;++i)
		Father[i] = i, Cnt[i] = 1;
}

int find(int x){
    int k = Father[x];
	return k == x ? x : Father[x] = find(k);
}

void unite(int x,int y){
    x = find(x);
	y = find(y);
    if ( x == y ) return;

	Father[y] = x;
	Cnt[x] += Cnt[y];
}

int main(){
	int n,m;
	scanf("%d%d",&n,&m);

	init(n);

	for(int i=0;i<m;++i){
		int x,y;
		scanf("%d%d",&x,&y);
		unite(x,y);
	}

	set<int> ans;
	for(int i=1;i<=n;++i)
		ans.insert(find(i));

	int sum = 0;
	for(set<int>::iterator it=ans.begin();it!=ans.end();++it){
		int k = *it;
        sum += Cnt[k] / 8;
		if ( Cnt[k] % 8 >= 5 ) ++sum;
	}
	printf("%d\n",sum);
	return 0;
}
