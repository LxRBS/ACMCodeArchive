#include <iostream>
#include <map>
#include <string>

using namespace std;

map<string,int> Map;

int main(){
	int m,n;
	char input[18];
	int salary;
	scanf("%d%d",&m,&n);
	getchar();

	for(int i=0;i<m;++i){
		scanf("%s%d",input,&salary);
		Map[string(input)] = salary;
	}

	map<string,int>::iterator it;
	while(n--){
		int ans = 0;
		while(1){			
			scanf("%s",input);
			if ( '.' == *input ) break;
			it = Map.find(string(input));
			if ( it != Map.end() ) ans += it->second;
		}
		printf("%d\n",ans);
	}

	return 0;
}