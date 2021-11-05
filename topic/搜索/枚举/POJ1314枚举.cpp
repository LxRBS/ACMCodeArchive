/**
    给定一系列点，问能构成多少个横平竖直的矩形。从左上点开始，逆时针输出
*/
#include <iostream>

int X[26],Y[26];
bool Flag[26];
char Coor[50][50];

char Ans[5] = {0,0,0,0,0};
void proc(){
	int cnt = -1;
	for(int i=0;i<26;++i)if(Flag[i]){
		Ans[0] = i + 'A';
		for(int j=0;j<26;++j)if(j!=i&&Flag[j]){
			if ( Y[j] == Y[i] && X[j] > X[i] ){
				Ans[1] = j + 'A';
				for(int k=0;k<26;++k)if(k!=i&&k!=j&&Flag[k]){
					if ( X[j] == X[k] && Y[k] < Y[j] ){
						Ans[2] = k + 'A';
						if ( Coor[X[i]][Y[k]] ){
							Ans[3] = Coor[X[i]][Y[k]];
							++cnt;
							if ( 0 == cnt % 10 ) printf("\n");
							printf(" %s",Ans);
						}
					}
				}
			}
		}
	}
	if ( -1 == cnt ) printf(" No rectangles\n");
	if ( cnt >= 0 ) printf("\n");
}

int main(){
	int n;
	int kase = 0;
	while( scanf("%d",&n) && n ){
		memset(Flag,0,sizeof(Flag));
		memset(Coor,0,sizeof(Coor));

		while( '\n' != getchar() );

		for(int i=0;i<n;++i){
			char ch;
			scanf("%c",&ch);
			
			int k = ch - 'A';
			scanf("%d%d",X+k,Y+k);
			while( '\n' != getchar() );
			
			Flag[k] = true;
			Coor[X[k]][Y[k]] = ch;
		}

		++kase;
		printf("Point set %d:",kase);
        proc();
	}
	return 0;
}