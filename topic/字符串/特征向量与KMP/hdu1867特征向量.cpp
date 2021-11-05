//ba ab
//应该输出aba, 而不是bab
//最后答案要尽可能短, 其次字典序小 
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int const SIZE = 100005;
char A[SIZE+SIZE],B[SIZE+SIZE];
char C1[SIZE+SIZE],C2[SIZE+SIZE];
int Next[SIZE+SIZE];

void getNext(char const P[],int n,int next[]){
	next[0] = 0;
	for(int i=1;i<n;++i){
		int k = next[i-1];
		while( k > 0 && P[k] != P[i] ) k = next[k-1];
		next[i] = ( P[i] == P[k] ) ? k + 1 : 0;
	}
	return;
}

bool cmp(char const a[],char const b[]){
	int la = strlen(a);
	int lb = strlen(b);
	if ( la != lb ) return la < lb;
	for(int i=0;i<la;++i){
		if ( a[i] != b[i] ) return a[i] < b[i];
	}
	return false;
}
int main(){
	while( EOF != scanf("%s%s",A,B) ){
		int la = strlen(A);
		int lb = strlen(B);
		B[lb] = '#';//special character
		copy(A,A+la,B+lb+1);
		B[la+lb+1] = '\0';
		getNext(B,la+lb+1,Next);
		
		int x = Next[la+lb];
		B[lb] = '\0';
		
		if ( x ){
			sprintf(C1,"%s%s",A,B+x);
		}else{
			if ( strcmp(A,B) < 0 ) sprintf(C1,"%s%s",A,B);
			else sprintf(C1,"%s%s",B,A);			
		}
		
		A[la] = '#';
		copy(B,B+lb,A+la+1);
		A[la+lb+1] = '\0';
		getNext(A,la+lb+1,Next);
		x = Next[la+lb];
		A[la] = '\0';
		if ( x ){
			sprintf(C2,"%s%s",B,A+x);
		}else{
			if ( strcmp(A,B) < 0 ) sprintf(C2,"%s%s",A,B);
			else sprintf(C2,"%s%s",B,A);			
		}
		
		printf("%s\n",(cmp(C1,C2)?C1:C2));

	}
}
