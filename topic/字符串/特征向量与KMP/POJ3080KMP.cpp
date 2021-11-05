/*
    ����һϵ���ַ�������������Ӵ�
	���������Ӵ�С��3������û��
	����ж����������ĸ��ĵ�һ��
	����KMP�㷨����ٵ�һ���ַ��������Ӵ�����ģʽP��ȥƥ������ַ���
*/
#include <stdio.h>
#include <string>
#include <iostream>
#include <cstring>

using namespace std;


/*  ����3
	���Ż����KMP����������רΪKMP�㷨
	arg1��ģʽP��C char*����
	arg2�������������飬�������������ڸ�������
	arg3��ģʽP�ĳ��ȣ�Ҳ�����������������Ч����
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
    ����4
	����KMP�㷨������T�в���P
	arg1��Ŀ��T
	arg2��ģʽP
	����ֵ������ҵ��������ҵ���λ�ã����򷵻�-1
*/
int KMPpos(char const T[],char const P[]){
	int *kmp;
	int plen = strlen(P);
	int tlen = strlen(T);
	if ( tlen < plen ) return -1;
	kmp = new int [plen];
	int i = 0;       /* ģʽ���±�*/
	int j = 0;        /*Ŀ����±�*/
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
			bool flag = false;             /*ĳ�����ȵ��Ӵ��Ƿ�ƥ��*/
			for( i=0;i<len-n+1;i++ ){      /*ȡ������base[0]����Ϊn���Ӵ�*/
			    for(j=0;j<n;j++) P[j] = base[0][j+i];
				P[n] = 0;
				for(j=1;j<num;j++)
					if ( -1 == KMPpos(base[j],P) )		 
					    goto LLAGAIN;     /*����ĳһ��base��ƥ�䣬��ȡ��һ���Ӵ�*/
                                          /*����base��ƥ����Ӵ�����ɹ�*/
				if ( !flag ) {		      /*�ó��ȵĵ�һ�γɹ�*/
                    flag = true; 
					tmpstr = string(P);
				}else{                    /*��γɹ�����ĸ������*/
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
		printf("no significant commonalities\n"); /*���˴�˵�������Ӵ�������ƥ�����base*/
		continue;
LLSUCCESS:
        printf("%s\n",P);
	}
	return 0;
}
