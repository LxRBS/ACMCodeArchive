#include <cstdio>
#include <algorithm>
using namespace std;

int const SIZE = 10000;
int const BLOCK_SIZE = 300;

struct query_t{
    int s;
    int e;
    int changedCnt;//��ʾ�ô�ѯ��֮ǰ�Ѿ��������޸Ĵ���
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
    int newColor;//Ҫ�޸ĵ�ֵ
    int preColor;//�˴��޸�֮ǰ��ֵ
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
    //��ʱ���޸Ļ�Ӱ�쵽MoAns��ֵ
    if ( curLeft <= pos && pos <= curRight ){
        remove(A[pos]);//pos��ԭ����ֵҪ�Ƴ���
        insert(color);//color��Ϊ��ֵ���
    }
    A[pos] = color;
}

void Mo(){
    sort(Query,Query+QCnt);

    curLeft = 1;
    curRight = 0;
    curChangedCnt = 0;//��ǰ�޸ĵĴ���
    MoAns = 0;

    for(int i=0;i<QCnt;++i){
        //��ǰ�޸Ĵ���δ�ﵽ��ִ���޸�
        while( curChangedCnt < Query[i].changedCnt ) change(Change[curChangedCnt].pos,Change[curChangedCnt].newColor),++curChangedCnt ;
        //��ǰ�޸Ĵ����ѳ����������޸�
        while( curChangedCnt > Query[i].changedCnt ) --curChangedCnt,change(Change[curChangedCnt].pos,Change[curChangedCnt].preColor);
        //����Ī�Ӳ���
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
