#include <cstdio>
#include <algorithm>
using namespace std;

int const SIZE = 10000;
int const BLOCK_SIZE = 300;

struct query_t{
    int s;
    int e;
    int changedCnt;//表示该次询问之前已经经过的修改次数
    int idx;
}Query[SIZE];

bool operator < (query_t const&lhs,query_t const&rhs){
    int la = lhs.s / BLOCK_SIZE;
    int ra = rhs.s / BLOCK_SIZE;
    int lb = lhs.e / BLOCK_SIZE;
    int rb = rhs.e / BLOCK_SIZE;
    return la < ra || ( la == ra && lb < rb ) || ( la == ra && lb == rb && lhs.changedCnt < rhs.changedCnt );
}

struct change_t{
    int pos;
    int newColor;//要修改的值
    int preColor;//此次修改之前的值
}Change[SIZE];

int N,M;
int A[SIZE];
int PreColor[SIZE];
int MoAns;
int QCnt,CCnt;
int Cnt[1000100];
int Ans[SIZE];
int curLeft,curRight,curChangedCnt;

inline void insert(int n){
    if ( 1 == ++Cnt[n] ) ++MoAns;
}

inline void remove(int n){
    if ( 0 == --Cnt[n] ) --MoAns;
}

inline void change(int pos,int color){
    //此时，修改会影响到MoAns的值
    if ( curLeft <= pos && pos <= curRight ){
        remove(A[pos]);//pos上原来的值要移除掉
        insert(color);//color作为新值添加
    }
    A[pos] = color;
}

void Mo(){
    sort(Query,Query+QCnt);

    curLeft = 1;
    curRight = 0;
    curChangedCnt = 0;//当前修改的次数
    MoAns = 0;

    for(int i=0;i<QCnt;++i){
        //当前修改次数未达到，执行修改
        while( curChangedCnt < Query[i].changedCnt ) change(Change[curChangedCnt].pos,Change[curChangedCnt].newColor),++curChangedCnt ;
        //当前修改次数已超过，撤销修改
        while( curChangedCnt > Query[i].changedCnt ) --curChangedCnt,change(Change[curChangedCnt].pos,Change[curChangedCnt].preColor);
        //基本莫队操作
        while( curRight < Query[i].e  ) insert(A[++curRight]);
        while( curLeft > Query[i].s ) insert(A[--curLeft]);
        while( curRight > Query[i].e ) remove(A[curRight--]);
        while( curLeft < Query[i].s ) remove(A[curLeft++]);
        Ans[Query[i].idx] = MoAns;
    }
}
int getUnsigned(){
	char ch = getchar();
	while( ch > '9' || ch < '0' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= (ch=getchar()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}
char getChar(){
	char ch = getchar();
	while( ch < 'A' || ch > 'z' || ( 'Z' < ch && ch < 'a' ) ) ch = getchar();
	return ch;
}
bool read(){
    if ( EOF == scanf("%d",&N) ) return false;
    M = getUnsigned();

    fill(Cnt,Cnt+1000100,0);
    for(int i=1;i<=N;++i) A[i] = PreColor[i] = getUnsigned();

    QCnt = CCnt = 0;

    char cmd;
    int a,b;
    for(int i=0;i<M;++i){
        cmd = getChar();
        a = getUnsigned();
        b = getUnsigned();
        if ( 'Q' == cmd ) Query[QCnt].s = a, Query[QCnt].e = b, Query[QCnt].idx = QCnt, Query[QCnt++].changedCnt = CCnt;
        else Change[CCnt].preColor = PreColor[a], Change[CCnt].pos = a, Change[CCnt++].newColor = PreColor[a] = b;
    }
    return true;
}
int main(){
    //freopen("1.txt","r",stdin);
    while( read() ){
        Mo();
        for(int i=0;i<QCnt;++i)printf("%d\n",Ans[i]);
    }
    return 0;
}
