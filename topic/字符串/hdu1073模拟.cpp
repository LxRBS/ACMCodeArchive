#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

char A[5005],B[5005];
char Ans[3][20] = {
	"Presentation Error",
	"Wrong Answer",
	"Accepted",
};
bool isEnd(char const *p){
    return 'E'==p[0] && 'N'==p[1] && 'D'==p[2] && '\0'==p[3];
}
bool isEq(char const*p1,int n1,char const*p2,int n2){
    if ( n1 != n2 ) return false;
	for(int i=0;i<n1;++i)
		if ( p1[i] != p2[i] )
			return false;
	return true;
}
int solve(int na,int nb){
    if ( isEq(A,na,B,nb) ) return 2;
	char* pa = remove(A,A+na,' ');
	na = pa - A;
	pa = remove(A,A+na,'\n');
	na = pa - A;
	pa = remove(A,A+na,'\t');
	na = pa - A;
	pa = remove(B,B+nb,' ');
	nb = pa - B;
	pa = remove(B,B+nb,'\n');
	nb = pa - B;
	pa = remove(B,B+nb,'\t');
	nb = pa - B;
	return isEq(A,na,B,nb) ? 0 : 1;
}
int main(){
    int nofkase;
	scanf("%d%*c",&nofkase);
	while(nofkase--){
        gets(A);
		int ka = 0;
		while(1){
			gets(A+ka);
			if ( isEnd(A+ka) ) break;
			while( A[ka] ) ++ka;
			A[ka++] = '\n';
		}
		A[ka] = '\0';

		gets(B);
		int kb = 0;
		while(1){
			gets(B+kb);
			if ( isEnd(B+kb) ) break;
			while( B[kb] ) ++kb;
			B[kb++] = '\n';
		}
		B[kb] = '\0';

		printf("%s\n",Ans[solve(ka,kb)]);
	}
	return 0;
}