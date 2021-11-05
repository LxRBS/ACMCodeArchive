/*
    POJ3461，标准的字符串匹配问题
	KMP算法
*/
#include <cstdio>
#include <cstring>
using namespace std;
#define SIZE 1000005

void getKMPNext(char const P[],int n,int Next[]){
    Next[0] = -1;
    int i = 0, k = -1;
    while( i < n ){
    	while( k >= 0 && P[i] != P[k] )
    		k = Next[k];
    	++i,++k;
    	if ( i == n ) return;
    	Next[i] = ( P[i] == P[k] ) ? Next[k] : k;
    }
}

int KMP(char const T[],char const P[],int Next[]){
    int ret = 0;
    int const plen = strlen(P);
    int const tlen = strlen(T);
    if ( tlen < plen ) return 0;
    int tp = 0, pp = 0;
    while( tp < tlen ){//搜索过程，tp永不回溯 
    	if ( -1 == pp || T[tp] == P[pp] )++tp,++pp;
    	else pp = Next[pp];
    	if ( plen == pp  ){
    		++ret;//找到一个完全匹配
    		pp = Next[plen];//多计算的特征数在这里用到
    	}
    }
    return ret;
}

char P[10001];
char T[SIZE];
int Next[10001];
int main(){
    int nofkase;
    scanf("%d",&nofkase);
    while(nofkase--){
    	scanf("%s%s",P,T);
    	getKMPNext(P,strlen(P)+1,Next);//多计算一个特征数
    	printf("%d\n",KMP(T,P,Next));
    }
	return 0;
}
