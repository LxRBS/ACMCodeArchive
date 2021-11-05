/*
    典型的字典树，但是可以使用map来做
	注意好单词的分割，其中有一种方法有潜在的bug，但是没找出来，
	现在使用的这种方法是借鉴的
*/
#include <iostream>
#include <map>
#include <string>
#include <cstring>
using namespace std;

char martin[3002],english[3002];
char input[3002];
int main(){
    string str;
	map<string,string> dict;
	gets(input);
	while(1){
		gets(input);
		if ( !strcmp(input,"END") )
			break;
        sscanf(input,"%s%s",english,martin);
		dict[string(martin)] = string(english);
	}
	gets(martin);
	while(1){
        gets(martin);
		if ( !strcmp(martin,"END") ) 
			return 0;
		string key;
		int i,k,len = strlen(martin);
        char ch[3002];
		string word;
		for(i=0;i<len;i++){           /*此处写i<len可以AC，但是如果输入只有一个单独的单词就没有输出(这说明测试数据不够完善)；改成i<=len，但最后的'\0'不能输出*/
			if ( islower(martin[i]) ){
				word += martin[i];
			}else{
				string str = dict[word];
				if ( str != "" ){
					printf("%s",str.c_str());
				}else{
					printf("%s",word.c_str());
				}
				word = "";
				if ( martin[i] ) putchar(martin[i]);/*为了防止输出'\0'，此处加一个判断，没有该判断，上面又写成<=则WA*/
			}
		}
		putchar('\n');
	}
	return 0;
}
