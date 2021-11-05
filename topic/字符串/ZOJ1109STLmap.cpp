#include <string>
#include <iostream>
#include <map>
#include <cstdio>
#include <cstring>

using namespace std;

map<string,string> Dic;

int main(){
	char ch[23],ch1[11],ch2[11];
	while( gets(ch) && strlen(ch) ){
		sscanf(ch,"%s%s",ch1,ch2);
		Dic[string(ch2)] = string(ch1);
	}
	while( gets(ch1) ){
		string str(Dic[string(ch1)]);
		if ( str.size() ) printf("%s\n",str.c_str());
		else              printf("eh\n");
	}
	return 0;
}
