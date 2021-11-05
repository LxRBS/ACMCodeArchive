#include <cstdio>
#include <cstring>
#include <set>
using namespace std;

int const SIZE = 50000 * 2 + 1;
#define lson(x) ( (x) << 1 )
#define rson(x) ( (x) << 1 | 1 )

#define MAX(x,y) ( (x) > (y) ? (x) : (y) )
#define MIN(x,y) ( (x) < (y) ? (x) : (y) )

struct _t{
    int v;
    int max;
    int min;
    int delay;
}ST[SIZE<<2];

void _pushUp(int rt){
    ST[rt].max = MAX(ST[lson(rt)].max,ST[rson(rt)].max);
    ST[rt].min = MIN(ST[lson(rt)].min,ST[rson(rt)].min);
    return;
}

void _pushDown(int rt){
    if ( !ST[rt].delay ) return;
    int x = ST[rt].delay;
    ST[rt].delay = 0;
    ST[lson(rt)].delay += x;
    ST[rson(rt)].delay += x;
    ST[lson(rt)].max += x;
    ST[rson(rt)].max += x;
    ST[lson(rt)].min += x;
    ST[rson(rt)].min += x;
}

void modify(int rt,int s,int e,int a,int b,int d){
    if ( a <= s && e <= b ){
    	ST[rt].delay += d;
        ST[rt].max += d;
        ST[rt].min += d;
        return;
    }

    _pushDown(rt);
    int mid = ( s + e ) >> 1;
    if ( a <= mid ) modify(lson(rt),s,mid,a,b,d);
    if ( mid < b ) modify(rson(rt),mid+1,e,a,b,d);
    _pushUp(rt);
}

void query(int rt,int s,int e,int a,int b,int ret[]){
    if ( a <= s && e <= b){
    	if ( ret[0] < ST[rt].max ) ret[0] = ST[rt].max;
    	if ( ret[1] > ST[rt].min ) ret[1] = ST[rt].min;
    	return;
    }
    _pushDown(rt);
    int mid = ( s + e ) >> 1;
    if ( a <= mid ) query(lson(rt),s,mid,a,b,ret);
    if ( mid < b ) query(rson(rt),mid+1,e,a,b,ret);
}

void build(int rt,int s,int e){
    memset(ST,0,sizeof(ST));
}

int C,N,O;
struct cmd_t{
	int c;
	int a;
	int b;
	int s;
}Cmd[SIZE];
set<int> Set;
int Idx[4587520+1];
int main() {
	//freopen("middle-random.in","r",stdin);
	//freopen("1.txt","w",stdout);
	scanf("%d%d%d",&C,&N,&O);

	char cmd[15];
    for(int i=0;i<O;++i){
    	scanf("%s%d",cmd,&Cmd[i].a);
    	++Cmd[i].a;
    	Set.insert(Cmd[i].a);
        if ( 'c' == *cmd ){
        	scanf("%d",&Cmd[i].s);
            Cmd[i].c = 0;
            Cmd[i].b = Cmd[i].a;
        }else if ( 'g' == *cmd ){
            scanf("%d%d",&Cmd[i].b,&Cmd[i].s);
            Cmd[i].c = 1;
            Set.insert(++Cmd[i].b);
        }else{
        	Cmd[i].c = 2;
        }
    }
    int k = 0;
    for(set<int>::iterator it=Set.begin();it!=Set.end();++it){
        Idx[*it] = ++ k;
    }

    //½¨Ê÷
    build(1,1,k);
    int ans[2];
    int a,b,s;
    for(int i=0;i<O;++i){
    	ans[0] = 0, ans[1] = N;
    	switch( Cmd[i].c ){
    	case 0:
    	case 1:
    		s = Cmd[i].s;
    		a = Idx[Cmd[i].a];
    		b = Idx[Cmd[i].b];
            query(1,1,k,a,b,ans);
            if ( s > 0 ) s = MIN(s,N-ans[0]);
            else s = MAX(s,-ans[1]);
            modify(1,1,k,a,b,s);
            printf("%d\n",s);
            break;
    	case 2:
    		a = Idx[Cmd[i].a];
    		query(1,1,k,a,a,ans);
    		printf("%d\n",ans[0]);
    	}
    }

	return 0;
}
