/*
�������ɸ��ַ���������������Ӵ��Ƕ���
�˴���Ϊ�����������򶼿��Լ���
��Сд��ĸ���
���磺����  ab
            ba
      ���  2   
���ڲ������ݵĲ�������������ֱ��ʹ�ñ�����
���������������̵��ַ�����Ȼ�����εõ����ַ�������Ϊn��n-1��n-2.....���Ӵ���������
�������������������Ƿ񶼴��ڸ��Ӵ�����
�÷���Ӧ����O(m��n��n��n)��mΪ���������nΪ����
����SA,Ӧ�ÿ��ԴﵽO(m��n��lgn��lgn)���ø��Ӷ�û�о�����ϸ�Ƶ��������ο�
*/

#include <iostream>
#include <cctype>
#include <cstring>

int const SIZE = 104; 
void dispArray(char const array[],int n){
	int i;
	for(i=0;i<n;i++){
		if ( i % 5 == 0 ) printf("\n");
		printf("%c",array[i]);
	}
	if ( i % 5 == 1 ) printf("\n");
	printf("\n");
	return ;
}
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
int KMPpos(char const T[],char const P[]){
	int *kmp;
	int plen = strlen(P);
	int tlen = strlen(T);
	if ( tlen < plen ) return -1;
	kmp = new int [plen];
	int i = 0;       /* ģʽ���±�*/
	int j = 0;        /*Ŀ����±�*/
	getKMPNext(P,kmp,plen);
	while( i < plen && j < tlen ){
		if ( -1 == i || T[j] == P[i] )
			i++,j++;
		else
			i = kmp[i];
	}
	delete [] kmp;
	if ( i >= plen ) return j - plen + 1;
	else             return -1;
}
char input[100][SIZE];
char sub[200][SIZE];
/*��source�������dest������Ϊn*/
void revers(char dest[],char const source[],int n){
    int i;
	for ( i=0;i<n;i++ )
		dest[i] = source[n-i-1];
	dest[n] = 0;
}
/*�õ�str���г���Ϊn���Ӵ�������sub����*/
void getSub(char const str[],int n){
    int i;
	int len = strlen(str);
	int k;
	for ( i=0;i<len-n+1;i++ ){
		for(k=0;k<n;k++)
			sub[i][k] = str[i+k];
		sub[i][k] = 0;
	}
	for(i=0;i<len-n+1;i++) revers(sub[len-n+1+i],sub[i],n);
}
/*����sub�����Ƿ����ַ����Ƿ�Ϊinput��������Ӵ�*/
/*n��input��size��subn��sub��size/2*/
bool isOK(int n,int subn){
    int kmp[2][102];
	int i,k;
	int len = strlen(sub[0]);
	for( i=0;i<subn;i++ ){
		memset(kmp,0,sizeof(kmp));
		getKMPNext(sub[i],kmp[0],len);
		getKMPNext(sub[i+subn],kmp[1],len);
		for(k=0;k<n;k++){
			if ( -1 == KMPpos(input[k],sub[i]) 
				&& -1 == KMPpos(input[k],sub[i+subn])
			   )
				goto NEXT;
		}
		return true;
NEXT:
		;
	}
	return false;
}
int main(){
	int numofcase;
	scanf("%d",&numofcase);
	while(numofcase--){
        int n,i;
		int mini = 0;  /*��������̵��ַ���*/
		scanf("%d",&n);
		for(i=0;i<n;i++){
			scanf("%s",input[i]);
			if ( strlen(input[i]) < strlen(input[mini]) )
				mini = i;
		}
        int ans;
		for( ans=strlen(input[mini]);ans>0;ans-- ){
            getSub(input[mini],ans);
			if ( isOK(n,strlen(input[mini])-ans+1) ){
				printf("%d\n",ans);
				goto SUCCESS;
			}
		}
		printf("0\n");
SUCCESS:
		;
	}
	return 0;
}
