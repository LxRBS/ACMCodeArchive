#include <iostream>
#include <string>
#include <set>

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
	len = len + len;             /*�������ַ����ظ�һ��*/
	while(1){
		if ( i + k >= len || j + k >= len ) break;
		if ( ch[i+k] == ch[j+k] ) k++;
		else{
			if ( ch[i+k] > ch[j+k] ) i += k+1;
			else                       j += k+1;
			k = 0;
			if ( i == j ) j++;    /*���i��jָ����ͬλ�ã����Ժ��λ�ö���ȣ��޷����бȽϣ�i��j��ѡһ��������һλ*/
		}
	}
	delete [] ch;
	return i < j ? i : j ;
}

char T[102];

int main(){
	int n;
	while(EOF!=scanf("%d",&n)){
		set<string> s;
		while(n--){
			scanf("%s",T);
			getchar();

			int ans = miniPre(T);
			int len = strlen(T);
			string str(len,0);
			
			int i,j;
			for(i=0,j=ans;i<len;i++,j=(j+1)%len)
				str[i] = T[j];

			s.insert(str);
		}

		printf("%d\n",s.size());

	}
	return 0;
}