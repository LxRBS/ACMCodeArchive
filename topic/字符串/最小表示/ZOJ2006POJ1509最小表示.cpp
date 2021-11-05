#include <stdio.h>
#include <string.h>
#include <malloc.h>

int miniPre(char const str[]){
    int i = 0, j = 1;
	int len = strlen(str);
	int k = 0,v;
	char* ch;
	ch = (char*)malloc((2*len+1)*sizeof(char));
    for(v=0;v<len;v++) ch[v] = ch[v+len] = str[v];
	ch[2*len] = 0;
	len = len + len;
	while(1){
		if ( i + k >= len || j + k >= len )
			break;
		if ( ch[i+k] == ch[j+k] ) k++;
		else{
			if ( ch[i+k] > ch[j+k] ) i += k + 1;
			else                     j += k + 1;
			k = 0;
			if ( i == j ) j++;
		}
	}
	free(ch);
	return i < j ? i : j;
}

char T[10000+2];

int main(){
	int n;
	scanf("%d",&n);
	while(n--){
		scanf("%s",T);
		printf("%d\n",miniPre(T)+1);
	}
	return 0;
}