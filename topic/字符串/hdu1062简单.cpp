/*
    ���⣬�������ÿ���������������ע��ά�ֵ����뵥��֮��Ŀո���Ŀ����
*/
#include <iostream>
#include <cstring>
using namespace std;
char ch[1005];
char word[1005];
int main(){
	int i,n,len;
	scanf("%d",&n);getchar();
	while(n--){
        gets(ch);
		int lench = strlen(ch);
		int k = 0;
		while( ' ' == ch[k] ) {
			putchar(' ');k++;
		}
		while( k < lench ){			
		    sscanf(ch+k,"%s",word);
			len = strlen(word);
			for(i=0;i<len;i++) putchar(word[len-1-i]);
			k += len;
			while( ' ' == ch[k] ){
				putchar(' ');k++;
			}
		}
		putchar('\n');
	}
	return 0;
}
