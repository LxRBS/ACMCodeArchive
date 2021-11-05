/*
    ����n���ַ���
    ������ڲ�����k/2���ַ����е�������Ӵ� 
*/
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

int const SIZE = 1005 * 100;
//�ָ������മ����ʱ��Ҫ�õ�����0��Ϊ���������϶��õ�
char const DELIMETER[] = {'#'};
int const DELIMETER_CNT = 100;
//��ĸ�����ĸ����
int const ALPHA_SIZE = DELIMETER_CNT + 26;
//charתint
inline int tr(char ch){
    return ch - 'a' + 1;
}
//�����꣬���»��߿�ͷ
#define _F(x) ((x)/3+((x)%3==1?0:tb))
#define _G(x) ((x)<tb?(x)*3+1:((x)-tb)*3+2)
//�������飬���»��߿�ͷ
int _wa[SIZE],_wb[SIZE],_wv[SIZE],_ws[SIZE];
//��������
int _c0(int const r[],int a,int b){
	return r[a] == r[b]
		&& r[a+1] == r[b+1]
		&& r[a+2] == r[b+2];
}
int _c12(int k,int *r,int a,int b){
	if( 2 == k ) return r[a]<r[b] || ( r[a]==r[b]&&_c12(1,r,a+1,b+1) );
    return r[a]<r[b] || ( r[a]==r[b]&&_wv[a+1]<_wv[b+1] );
}
void _sort(int const r[],int *a,int *b,int n,int m){
    int i;
    for(i=0;i<n;i++) _wv[i] = r[a[i]];
    for(i=0;i<m;i++) _ws[i] = 0;
    for(i=0;i<n;i++) _ws[_wv[i]]++;
    for(i=1;i<m;i++) _ws[i] += _ws[i-1];
    for(i=n-1;i>=0;i--) b[--_ws[_wv[i]]] = a[i];
    return;
}
//��׺�����dc3�㷨��ʹ�ô�dc3�㷨һ��Ҫ��֤r��sa����󳤶Ȳ�С��3��ԭ����
//r: Դ���飬�ҳ�r[n-1]�⣬����r[i]>0
//n: r�ĳ���
//m: r�е�Ԫ��ȡֵ���Ͻ磬������r[i]<m
//sa:��׺���飬�����
void dc3(int r[],int n,int m,int sa[]){
    int i,j,*rn=r+n,*san=sa+n,ta=0,tb=(n+1)/3,tbc=0,p;
    r[n] = r[n+1] = 0;
    for(i=0;i<n;i++) if(i%3!=0) _wa[tbc++]=i;
    _sort(r+2,_wa,_wb,tbc,m);
    _sort(r+1,_wb,_wa,tbc,m);
    _sort(r,_wa,_wb,tbc,m);
    for(p=1,rn[_F(_wb[0])]=0,i=1;i<tbc;i++)
        rn[_F(_wb[i])] = _c0(r,_wb[i-1],_wb[i])?p-1:p++;
    if(p<tbc) dc3(rn,tbc,p,san);
    else for(i=0;i<tbc;i++) san[rn[i]]=i;
    for(i=0;i<tbc;i++) if(san[i]<tb) _wb[ta++] = san[i]*3;
    if(n%3==1) _wb[ta++]=n-1;
    _sort(r,_wb,_wa,ta,m);
    for(i=0;i<tbc;i++) _wv[_wb[i] = _G(san[i])] = i;
    for(i=0,j=0,p=0;i<ta&&j<tbc;p++)
        sa[p] = _c12(_wb[j]%3,r,_wa[i],_wb[j]) ? _wa[i++] : _wb[j++];
    for(;i<ta;p++) sa[p] = _wa[i++];
    for(;j<tbc;p++) sa[p] = _wb[j++];
    return;
}
//����rank������height����
//r:  Դ����
//sa: ��׺����
//n:  Դ����ĳ���
//rank: rank���飬��������
//height: height���飬��������
void calHeight(int const r[],int const sa[],int n,int rank[],int height[]){
    int i,j,k=0;
    for(i=1;i<n;i++) rank[sa[i]]=i;
    for(i=0;i<n-1;height[rank[i++]]=k)
    for(k?k--:0,j=sa[rank[i]-1];r[i+k]==r[j+k];k++);
    return;
}

void dispArray(int const a[],int n){
	for(int i=0;i<n;++i)printf("%d ",a[i]);
	printf("\n");
}

int R[SIZE*3],SA[SIZE*3];//3��!!!
int Rank[SIZE],Height[SIZE];

int N;
char A[1005];
int Len[105],Start[105];
int MiniLen;
bool read(){
	scanf("%d",&N);
	if ( 0 == N ) return false;

	if ( 1 == N ){
		scanf("%s",A);
		printf("%s\n",A);
		return true;
	}

	Start[0] = 0;
	MiniLen = SIZE;
	for(int i=0;i<N;++i){
		scanf("%s",A);
		Len[i] = strlen(A);
		if ( MiniLen > Len[i] ) MiniLen = Len[i];
		for(int j=0;j<Len[i];++j) R[j+Start[i]] = tr(A[j]);
		R[Start[i] + Len[i]] = i + 27;
		Start[i+1] = Start[i] + Len[i] + 1;
	}
	R[Start[N]-1] = 0;
	return true;
}

//���غ�׺���ڵ��ַ������
int _g(int sa){
    for(int i=1;i<N;++i){
    	if ( Start[i-1] <= sa && sa < Start[i] )
		    return i - 1;
    }
    return N - 1;
}
//���v�Ƿ��������
//Height�д���[i...j]����С��v
//��SA[i-1,...,j]�ֱ�����N/2������������������
bool check(int v){
    int cnt = 0;
    bool a[100] = {false};
    a[_g(SA[0])] = true;
    cnt = 1;
    for(int i=1;i<Start[N];++i){
        if ( Height[i] >= v ){
            int t = _g(SA[i]);
            if ( !a[t] ) a[t] = true, ++cnt;
            if ( cnt + cnt > N ) return true;
        }else{
            memset(a,0,sizeof(a));
            a[_g(SA[i])] = true;
            cnt = 1;
        }
    }
    return false;
}
int proc(){
	dc3(R,Start[N],ALPHA_SIZE,SA);
	calHeight(R,SA,Start[N],Rank,Height);
	/*
	dispArray(Start,N+1);
	dispArray(R,Start[N]);
	dispArray(SA,Start[N]);
	dispArray(Rank,Start[N]);
	dispArray(Height,Start[N]);
	//*/

	//���ַ���������������ֵ
	int left = 1;//��������0
	int right = MiniLen;//�����MiniLen������һ��BUG��������û������ 
	do{
		int mid = ( left + right ) >> 1;
		if ( check(mid) ) left = mid + 1;
		else right = mid - 1;
	}while( left <= right );
    return right;
}
inline char itr(int v){return v-1+'a';}

void output(int v,int saidx){
	int k = SA[saidx];
    for(int i=0;i<v;++i)printf("%c",itr(R[k++]));
    printf("\n");
}
//����������������ĳ���Ϊt���Ӵ�
void output(int v){
	int i = 1;
	while( i < Start[N] ){
        while( Height[i] < v ) ++i;
        if ( i == Start[N] ) return;

        int k = 0;
        int cnt = 1;
        bool a[100] = {false};
        int t = _g(SA[i-1]);
        a[t] = true;
        while( i + k < Start[N] && Height[i+k] >= v ){
        	int tt = _g(SA[i+k]);
        	if ( !a[tt] ){
        		a[tt] = true, ++cnt;
        	}
        	++k;
        }
        if ( cnt + cnt > N ) output(v,i-1);
        i += k;
	}
}
int main() {
	bool flag = false;
	while( read() ){
		if ( flag ) printf("\n");
		flag = true;
		int t = proc();
		if ( 0 == t ) printf("?\n");
		else output(t);
	}
	return 0;
}
