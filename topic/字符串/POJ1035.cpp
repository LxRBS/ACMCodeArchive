/*
    ����һ���ֵ��һϵ�п����д���ĵ��ʣ�����С�����Ŀ���
	    ��ν��С�������ǣ�����1����ĸ��ɾ��1����ĸ���滻1����ĸ
	���磺
	    ���룺i,me(�ֵ�),m(����)
		�����i��me
	���Ҫ���ո������ֵ�˳��
	��string���ͳ�ʱ
	�ĳ�char[]��AC
*/
#include <stdio.h>
#include <string.h>
/*
    ���ch1[pos1]...ch1[pos1-len+1]
	��  ch2[pos2]...ch2[pos2-len+1]
	�Ƿ����
*/
bool isSame(char const ch1[],int pos1,char const ch2[],int pos2,int len){
    int i;
	for ( i=0;i<len;i++ ){
		if ( ch1[pos1+i] != ch2[pos2+i] )
			return false;
	}
	return true;
}
bool match(char const dict[],char const word[]){
	int dictlen = strlen(dict);
	int wordlen = strlen(word);
	int i;
    if ( dictlen > wordlen + 1 ) return false;
	if ( dictlen < wordlen - 1 ) return false;
	if ( dictlen - 1 == wordlen ){ /*����1���ַ��������λ�ÿ�����wordlen+1��*/
		for(i=0;i<=wordlen;i++){
			if ( isSame(dict,0,word,0,i) 
				 && isSame(dict,i+1,word,i,wordlen-i) )
				return true;
		}
		return false;
	}
	if ( dictlen + 1 == wordlen ){ /*ɾ��1���ַ���ɾ����λ�ÿ�����wordlen��*/
		for ( i=0;i<wordlen;i++ ){
			if ( isSame(dict,0,word,0,i)
				&& isSame(dict,i,word,i+1,dictlen-i) )
				return true;
		}
		return false;
	}
	if ( dictlen == wordlen ){ /*�滻1���ַ����滻��λ�ÿ�����wordlen��*/
		for ( i=0;i<wordlen;i++ ){
			if ( isSame(dict,0,word,0,i)
				&& isSame(dict,i+1,word,i+1,wordlen-i-1) )
				return true;
		}
		return false;
	}
	return false;
}

#define  SIZE 10001
char dict[SIZE][16];
char tmpout[SIZE];

int main(){
	int i;
	int len;
	for(i=0;i<=SIZE;i++){
	    scanf("%s",dict[i]);
		if ( dict[i][0] == '#' ) break;
	}
	len = i ;         /*�ֵ�Ĵ�����*/
	char word[16];
	while(1){
		scanf("%s",word);
		if ( word[0] == '#' ) break;
		bool flag = false;
		memset(tmpout,0,sizeof(tmpout));
		strcat(tmpout,word);
		strcat(tmpout,":");
		for( i=0;i<len;i++ ){
			if ( strcmp(dict[i],word) == 0 ){
				flag = true;
                break;
			}
			if ( match(dict[i],word) ){
			    strcat(tmpout," ");
				strcat(tmpout,dict[i]);
			}
		}
		if ( flag ) printf("%s is correct\n",word);
		else        printf("%s\n",tmpout);
	}
	return 0;
}
