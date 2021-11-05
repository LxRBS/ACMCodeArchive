//�����ַ���T����T[s,e]�Ĳ�ͬ�Ӵ��ĸ���
//��T��ÿһ����׺��SAM��һ������n��SAM�����ڿռ䲻���棬�߽��ߴ���
//ÿ����һ���½ڵ������ӵĺ�׺��������nn.step-nn.pre.step��Ҳ���������ӵ��Ӵ�����
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define SIZE 2001
struct _t{
	_t* son[26];
	_t* pre;//�ɽ�����
	int step;//���������
}Node[SIZE*20];
int toUsed = 0;
_t* Init;//��̬
_t* Last;//���ڵ�


//Ĭ�Ϲ���
inline void mkNode(_t* newNode){
	newNode->pre = (_t*)0;
	newNode->step = 0;
	fill(newNode->son,newNode->son+26,(_t*)0);
}
//��������
inline void mkNode(_t const*src,_t*dest){
	dest->pre = src->pre;
	dest->step = src->step;
	copy(src->son,src->son+26,dest->son);
}

//����ȫ�ֱ�����¼���������г��ֹ����Ӵ�����
int Cnt = 0;
inline int calc(_t const* p){
	return NULL == p->pre ? 0 : p->step - p->pre->step;
}
//�����Զ���
void mkSAM(char ch){
	int sn = ch - 'a';

	//�½ڵ�
	_t* nn = Node + toUsed ++;
	mkNode(nn);
	nn->step = Last->step + 1;

	//�����ɽ�����
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

	//�ҵ���sn���ߵ�p
	_t* q = p->son[sn];
	if ( p->step + 1 == q->step ){
		nn->pre = q;
		Cnt += calc(nn);
		return;
	}

	//��������q
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

			//������i��SAM
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