//给定字符串T，问T[s,e]的不同子串的个数
//对T的每一个后缀建SAM，一共建立n个SAM，限于空间不保存，边建边处理
//每插入一个新节点所增加的后缀数量就是nn.step-nn.pre.step，也就是新增加的子串数量
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define SIZE 2001
struct _t{
	_t* son[26];
	_t* pre;//可接收链
	int step;//插入的秩序
}Node[SIZE*20];
int toUsed = 0;
_t* Init;//初态
_t* Last;//最后节点


//默认构造
inline void mkNode(_t* newNode){
	newNode->pre = (_t*)0;
	newNode->step = 0;
	fill(newNode->son,newNode->son+26,(_t*)0);
}
//拷贝构造
inline void mkNode(_t const*src,_t*dest){
	dest->pre = src->pre;
	dest->step = src->step;
	copy(src->son,src->son+26,dest->son);
}

//利用全局变量记录建立过程中出现过的子串总数
int Cnt = 0;
inline int calc(_t const* p){
	return NULL == p->pre ? 0 : p->step - p->pre->step;
}
//建立自动机
void mkSAM(char ch){
	int sn = ch - 'a';

	//新节点
	_t* nn = Node + toUsed ++;
	mkNode(nn);
	nn->step = Last->step + 1;

	//遍历可接收链
	_t* p = Last;
	Last = nn;
	while( p && NULL == p->son[sn] ){
		p->son[sn] = nn;
		p = p->pre;
	}
	if ( NULL == p ){
		nn->pre = Init;
		Cnt += calc(nn);
		return;
	}

	//找到有sn出边的p
	_t* q = p->son[sn];
	if ( p->step + 1 == q->step ){
		nn->pre = q;
		Cnt += calc(nn);
		return;
	}

	//拷贝构造q
	_t* nq = Node + toUsed ++;
	mkNode(q,nq);
	nq->step = p->step + 1;
	q->pre = nn->pre = nq;
	Cnt += calc(nn);
	while( p && q == p->son[sn] ){
		p->son[sn] = nq;
		p = p->pre;
	}
	return;
}
char A[SIZE];
int Ans[SIZE][SIZE];
inline void init(){
	toUsed = 1;
	Init = Last = Node;
	mkNode(Node);
}
int main(){
	int nofkase;
	scanf("%d",&nofkase);
	while(nofkase--){
		scanf("%s",A);
		int len = strlen(A);
		for(int i=0;i<len;++i){
			init();

			//建立第i个SAM
			Cnt = 0;
			for(int j=i;j<len;++j){
				mkSAM(A[j]);
				Ans[i][j] = Cnt;
			}
		}

		int n;
		scanf("%d",&n);
		for(int i=0;i<n;++i){
			int a,b;
			scanf("%d%d",&a,&b);
			printf("%d\n",Ans[a-1][b-1]);
		}
	}
	return 0;
}