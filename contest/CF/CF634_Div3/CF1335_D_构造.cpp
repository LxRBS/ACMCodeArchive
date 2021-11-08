/**
 * 给定一个数独，最多改变9个数，将其变为反数独
 * 反数独指每一行每一列每一个九宫至少有2个元素是相等的
 * 找到每个1，将其改为2即可
*/
#include <bits/stdc++.h>
using namespace std;
int getInt(){
	int sgn = 1;
	char ch = getchar();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = getchar();
	if ( '-' == ch ) {sgn = 0;ch=getchar();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=getchar()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}

char A[12][12];


int main(){
    //freopen("1.txt","r",stdin);
    int nofkase = getInt();
    while(nofkase--){
        for(int i=0;i<9;++i)scanf("%s",A[i]);
        for(int i=0;i<9;++i)for(int j=0;j<9;++j)if('1'==A[i][j]){
            A[i][j] = '2';
        }
        for(int i=0;i<9;++i)puts(A[i]);
    }
    return 0;
}

