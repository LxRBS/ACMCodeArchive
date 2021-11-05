/*
    典型的求一个字符串的最小表示
*/
#include <iostream>
using namespace std;
int miniPre(char const str[]){
	int i = 0, j = 1;           /*维护两个指针，j相当于str的1次循环*/
	int len = strlen(str);
	int k = 0;                  /* 后移位数*/
	char* ch;
	ch = new char [2*len+1];
	for(int v=0;v<len;v++)
		ch[v] = ch[v+len] = str[v];
	ch[2*len] = 0;
	len = len + len;
	while(1){
		if ( i + k >= len || j + k >= len ) break;
		if ( ch[i+k] == ch[j+k] ) k++;
		else{
			if ( ch[i+k] > ch[j+k] ) i += k+1;  /*i大则i后移*/
			else                     j += k+1;
			k = 0;
			if ( i == j ) j++;   /*如果i、j指向相同位置，则以后的位置都相等，无法进行比较，i、j中选一个往后移一位*/
		}
	}
	delete [] ch;
	return i < j ? i : j ;
}
#define  SIZE 10001
char ch[SIZE];
int main(){
	int n,ans;
	scanf("%d",&n);
	while(n--){
        scanf("%s",ch);
        ans = miniPre(ch) + 1;
		printf("%d\n",ans);
	}
}
