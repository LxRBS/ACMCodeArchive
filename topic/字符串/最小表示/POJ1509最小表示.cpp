/*
    ���͵���һ���ַ�������С��ʾ
*/
#include <iostream>
using namespace std;
int miniPre(char const str[]){
	int i = 0, j = 1;           /*ά������ָ�룬j�൱��str��1��ѭ��*/
	int len = strlen(str);
	int k = 0;                  /* ����λ��*/
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
			if ( ch[i+k] > ch[j+k] ) i += k+1;  /*i����i����*/
			else                     j += k+1;
			k = 0;
			if ( i == j ) j++;   /*���i��jָ����ͬλ�ã����Ժ��λ�ö���ȣ��޷����бȽϣ�i��j��ѡһ��������һλ*/
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
