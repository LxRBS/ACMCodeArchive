/*
    给定一系列字符串，求最长公共子串
	如果最长公共子串小于3，则当做没有
	如果有多个最长，输出字母序的第一个
	利用KMP算法，穷举第一个字符的所有子串当做模式P，去匹配后续字符串
*/
#include <stdio.h>
#include <string>
#include <iostream>
#include <cstring>

using namespace std;


/*  函数3
	求优化后的KMP特征向量，专为KMP算法
	arg1：模式P，C char*类型
	arg2：特征向量数组，特征向量保存在该数组中
	arg3：模式P的长度，也是特征向量数组的有效长度
*/
bool getKMPNext(char const P[],int kmp[],int n){
	int i=0,k = -1;
	kmp[0] = -1;
	while( i < n ){
		while( k>=0 && P[i]!=P[k] )
			k = kmp[k];
		i++;
		k++;
		if ( i == n ) break;
		if ( P[i] == P[k] ) kmp[i] = kmp[k];
		else                kmp[i] = k;
	}
	return true;
}
/*
    函数4
	利用KMP算法查找在T中查找P
	arg1：目标T
	arg2：模式P
	返回值：如果找到，返回找到的位置，否则返回-1
*/
int KMPpos(char const T[],char const P[]){
	int *kmp;
	int plen = strlen(P);
	int tlen = strlen(T);
	if ( tlen < plen ) return -1;
	kmp = new int [plen];
	int i = 0;       /* 模式的下标*/
	int j = 0;        /*目标的下标*/
	getKMPNext(P,kmp,plen);
#if 0
	for(int i=0;i<plen;i++) printf("%-3d",kmp[i]);
	printf("\n");
#endif
	while( i < plen && j < tlen ){
		if ( -1 == i || T[j] == P[i] )
			i++,j++;
		else
			i = kmp[i];
	}
	delete kmp;
	if ( i >= plen ) return j - plen + 1;
	else             return -1;
}

char base[10][61];

int main(){
	int num_of_case;
	scanf("%d",&num_of_case);
	while(num_of_case--){
        int num;
		scanf("%d",&num);
		int i;
		for( i=0;i<num;i++ ) scanf("%s",base[i]);
		char P[61];
		int len = strlen(base[0]);
		for( i=1;i<num;i++ ){
			if ( -1 == KMPpos(base[i],base[0]) )
				goto LL;
		}
		printf("%s\n",base[0]);
		continue;
LL:
		int n;
		int j;
		string tmpstr,str2;
		for( n=len-1;n>2;n-- ){
			bool flag = false;             /*某个长度的子串是否匹配*/
			for( i=0;i<len-n+1;i++ ){      /*取出所有base[0]长度为n的子串*/
			    for(j=0;j<n;j++) P[j] = base[0][j+i];
				P[n] = 0;
				for(j=1;j<num;j++)
					if ( -1 == KMPpos(base[j],P) )		 
					    goto LLAGAIN;     /*若有某一个base不匹配，则取下一个子串*/
                                          /*所有base都匹配该子串，则成功*/
				if ( !flag ) {		      /*该长度的第一次成功*/
                    flag = true; 
					tmpstr = string(P);
				}else{                    /*多次成功则按字母序排序*/
                    str2 = string(P);
                    if ( str2 < tmpstr ) 
					    tmpstr = str2;   
				}
LLAGAIN:
				;
			}
			if ( flag ) {
				strcpy(P,tmpstr.c_str());
				goto LLSUCCESS;	
			}
		}
		printf("no significant commonalities\n"); /*到此处说明所有子串都不能匹配后续base*/
		continue;
LLSUCCESS:
        printf("%s\n",P);
	}
	return 0;
}
