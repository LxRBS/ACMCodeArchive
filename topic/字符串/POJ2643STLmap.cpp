#include <iostream>
#include <map>
#include <string>
#include <utility>

using namespace std;

typedef pair<string,int> pair_t;
map<string,pair_t> Map;

int main(){
	int n;
	scanf("%d%*c",&n);

	char party[100];
	char name[100];
	pair_t p;
	for(int i=0;i<n;++i){
        gets(name);gets(party);
        p.first = string(party);
		p.second = 0;
		Map[string(name)] = p;
	}

	scanf("%d%*c",&n);

	int ans = 0;
	//判断最大值有没有重复，初始均为0，有重复
	bool flag = true;
	string max_name;
	for(int i=0;i<n;++i){
		gets(name);
		int& vote = Map[string(name)].second;
		if ( vote == ans ){
			++vote;
			++ans;
			flag = false;
			max_name = string(name);
		}else if ( vote == ans - 1 ){
			flag = true;
			++vote;
		}else{
			++vote;
		}
	}

	if ( flag ){
		printf("tie\n");
		return 0;
	}

	map<string,pair_t>::iterator it;
	it = Map.find(max_name);
    printf("%s\n",((it->second).first).c_str());

	return 0;
}