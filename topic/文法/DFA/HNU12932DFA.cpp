#include <cstdio>

int const T[7][7] = {
//    A,B,C,D,E,F,other
/*0*/{0},
/*1*/{2,3,3,3,3,3,0},
/*2*/{2,0,0,0,0,4,0},
/*3*/{2,0,0,0,0,0,0},
/*4*/{0,0,5,0,0,4,0},
/*5*/{6,6,5,6,6,6,0}, //final state
/*6*/{0,0,0,0,0,0,0}  //final state
};

inline int tr(char ch){
	return 'A' <= ch && ch <= 'F' ? ch - 'A' : 6;
}

char A[210];
int main(){
	int n;
	scanf("%d",&n);
	gets(A);
	while(n--){
		gets(A);
		int state = 1;
		for(char*p=A;*p;++p){
			state = T[state][tr(*p)];
			if ( 0 == state ) break;
		}
		printf(5==state||6==state?"Infected!\n":"Good\n");
	}
	return 0;
}

