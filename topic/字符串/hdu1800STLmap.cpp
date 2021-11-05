#include <iostream>
#include <string>
#include <map>

using namespace std;

int main(){
	int n;
	map<string,int> m;
	map<string,int>::iterator it;
	while(cin>>n){
		if ( 0 == n ) continue;
		string str;
		while(n--){
			cin>>str;
			int i = 0;
			while( '0' == str[i] ) i++;
			m[str.substr(i,str.length()-i)]++;
		}
		int ans = 0;
		for(it=m.begin();it!=m.end();it++){
			int tmp = it->second;
			if ( ans < tmp ) ans = tmp;
		}
		cout<<ans<<endl;
		m.clear();
	}
}
