/*
    给定一个字典和一系列可能有错误的单词，求最小改正的可能
	    所谓最小改正就是：插入1个字母，删除1个字母和替换1个字母
	例如：
	    输入：i,me(字典),m(单词)
		输出：i，me
	输出要按照给定的字典顺序
	用string类型超时
	改成char[]则AC
*/
#include <stdio.h>
#include <string.h>
/*
    检查ch1[pos1]...ch1[pos1-len+1]
	与  ch2[pos2]...ch2[pos2-len+1]
	是否相等
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
	if ( dictlen - 1 == wordlen ){ /*插入1个字符，插入的位置可能有wordlen+1个*/
		for(i=0;i<=wordlen;i++){
			if ( isSame(dict,0,word,0,i) 
				 && isSame(dict,i+1,word,i,wordlen-i) )
				return true;
		}
		return false;
	}
	if ( dictlen + 1 == wordlen ){ /*删除1个字符，删除的位置可能有wordlen个*/
		for ( i=0;i<wordlen;i++ ){
			if ( isSame(dict,0,word,0,i)
				&& isSame(dict,i,word,i+1,dictlen-i) )
				return true;
		}
		return false;
	}
	if ( dictlen == wordlen ){ /*替换1个字符，替换的位置可能有wordlen个*/
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
	len = i ;         /*字典的词数量*/
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
