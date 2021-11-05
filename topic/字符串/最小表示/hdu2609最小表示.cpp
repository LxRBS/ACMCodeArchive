#include <iostream>
#include <string>
#include <set>

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
	len = len + len;             /*将待测字符串重复一次*/
	while(1){
		if ( i + k >= len || j + k >= len ) break;
		if ( ch[i+k] == ch[j+k] ) k++;
		else{
			if ( ch[i+k] > ch[j+k] ) i += k+1;
			else                       j += k+1;
			k = 0;
			if ( i == j ) j++;    /*如果i、j指向相同位置，则以后的位置都相等，无法进行比较，i、j中选一个往后移一位*/
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