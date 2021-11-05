#include <cstdio>
#include <map>
#include <set>

std::map<int,int> Map;

void initMap(int n){
    Map.clear();
	for(int i=1;i<=n;i++)
		Map[i] = 0;
}

int query(int a,int b){
	if ( a == b ) return a;

	std::set<int> Set;
	Set.insert(a);
	while ( 0 != a  ) {
        a = Map[a];
		Set.insert(a);
	}

	while( 1 ){
        if ( Set.find(b) != Set.end() )
			return b;

		b = Map[b];
	}
	return 0;
}

int main(){
	int t;
	scanf("%d",&t);

	while(t--){
        int i,n;
		int father,son;
		int a,b;
		scanf("%d",&n);

		initMap(n);
		for(i=0;i<n-1;i++){
            scanf("%d%d",&father,&son);
			Map[son] = father;
		}

		scanf("%d%d",&a,&b);
        printf("%d\n",query(a,b));
	}

	return 0;
}