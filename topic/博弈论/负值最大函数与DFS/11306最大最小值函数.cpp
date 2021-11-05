#include <climits>
#include <iostream>
#include <algorithm>
using namespace std;

#define PLUS 1
#define MINUS 2
#define MULTI 3
#define DIVID 4

char const OP[] = {0,'+','-','*','/'};

//算式结构，a op b，双向链表
struct _t{
	int op;
	int a;
	int b;
	int prev;
	int next;
};

_t A[11];

//计算第i个表达式
int calc(int idx){
	switch( A[idx].op ){
		case PLUS:return A[idx].a + A[idx].b;
		case MINUS:return A[idx].a - A[idx].b;
		case MULTI:return A[idx].a * A[idx].b;
		case DIVID:return A[idx].a / A[idx].b;
	}
	return 0xCCCCC;
}

int MaxRet;
int MinRet;
int Max1st;
int Min1st;
bool Flag[11];
int M;

int min(int);
int max(int depth){
    if ( M == depth ) return calc(0);

    int ret = INT_MIN;
    for(int i=1;i<=M;++i){
        if (Flag[i]) continue;

        //变化
        int t = calc(i);
		A[A[i].prev].b = t;
		A[A[i].next].a = t;
		A[A[i].prev].next = A[i].next;
		A[A[i].next].prev = A[i].prev;
		Flag[i] = true;
		//递归
		int v = min(depth+1);
        //还原
        A[A[i].prev].b = A[i].a;
		A[A[i].next].a = A[i].b;
		A[A[i].prev].next = i;
		A[A[i].next].prev = i;
		Flag[i] = false;
		//判断
		if ( v > ret ) ret = v;
    }
    return ret;
}

int min(int depth){
    if ( M == depth ) return calc(0);

    int ret = INT_MAX;
    for(int i=1;i<=M;++i){
        if (Flag[i]) continue;

        //变化
        int t = calc(i);
		A[A[i].prev].b = t;
		A[A[i].next].a = t;
		A[A[i].prev].next = A[i].next;
		A[A[i].next].prev = A[i].prev;
		Flag[i] = true;
		//递归
		int v = max(depth+1);
        //还原
        A[A[i].prev].b = A[i].a;
		A[A[i].next].a = A[i].b;
		A[A[i].prev].next = i;
		A[A[i].next].prev = i;
		Flag[i] = false;
		//判断
		if ( v < ret ) ret = v;
    }
    return ret;
}

void read(){
    cin >> M;

	int a,b;
	cin>>a;

	char op;
	for(int i=1;i<=M;++i){
		cin>>op>>b;
		switch(op){
			case '+':A[i].op = PLUS;break;
			case '-':A[i].op = MINUS;break;
			case '*':A[i].op = MULTI;break;
			case '/':A[i].op = DIVID;break;
			default:A[i].op=0;cout<<"Haha"<<endl;
		}
		A[i].a = a;
		A[i].b = b;
		A[i].prev = i - 1;
		A[i].next = i + 1;
		a = b;
	}

	A[0].op = A[M+1].op = PLUS;
	A[0].a = A[M+1].b = 0;
	A[0].b = A[1].a;
	A[M+1].a = A[M].b;
	A[0].next = 1;
	A[M+1].prev = M;
}

int main(){
    //freopen("1.txt","w",stdout);
	int nofkase;
	cin>>nofkase;
	for(int kase=1;kase<=nofkase;++kase){
        fill(Flag,Flag+M+2,false);
		MaxRet = INT_MIN;
		MinRet = INT_MAX;
		Max1st = Min1st = 0;

        read();

		//第一步手工写
		for(int i=1;i<=M;++i){
			int t = calc(i);
			A[i-1].b = t;
			A[i+1].a = t;
			A[i-1].next = i + 1;
			A[i+1].prev = i - 1;
			Flag[i] = true;
			int v1 = min(1);
			int v2 = max(1);
			Flag[i] = false;
			A[i-1].b = A[i].a;
			A[i+1].a = A[i].b;
			A[i-1].next = A[i+1].prev = i;

			if ( v1 > MaxRet ) MaxRet = v1, Max1st = i;
			if ( v2 < MinRet ) MinRet = v2,Min1st = i;
		}

		cout<<"Case "<<kase<<':'<<endl;
		cout<<"Player 1 ("<<A[Max1st].a<<OP[A[Max1st].op]<<A[Max1st].b<<") leads to "<<MaxRet<<endl;
		cout<<"Player 2 ("<<A[Min1st].a<<OP[A[Min1st].op]<<A[Min1st].b<<") leads to "<<MinRet<<endl;
		if ( MaxRet > - MinRet )
			cout<<"Player 1 wins"<<endl;
		else if ( MaxRet < - MinRet )
			cout<<"Player 2 wins"<<endl;
		else
			cout<<"Tie"<<endl;
	}
	return 0;
}
