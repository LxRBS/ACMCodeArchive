/*
    ���͵��ֵ��������ǿ���ʹ��map����
	ע��õ��ʵķָ������һ�ַ�����Ǳ�ڵ�bug������û�ҳ�����
	����ʹ�õ����ַ����ǽ����
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
		for(i=0;i<len;i++){           /*�˴�дi<len����AC�������������ֻ��һ�������ĵ��ʾ�û�����(��˵���������ݲ�������)���ĳ�i<=len��������'\0'�������*/
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
				if ( martin[i] ) putchar(martin[i]);/*Ϊ�˷�ֹ���'\0'���˴���һ���жϣ�û�и��жϣ�������д��<=��WA*/
			}
		}
		putchar('\n');
	}
	return 0;
}
