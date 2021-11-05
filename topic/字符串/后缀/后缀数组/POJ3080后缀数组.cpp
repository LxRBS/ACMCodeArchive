//����ַ�����������Ӵ�����Ҫ�󳤶Ȳ�С��3����Ҫ�����
//����ʹ��KMP����������������

#include <cstdio>

int const SIZE = 1100;
//�ָ������മ����ʱ��Ҫ�õ�����0��Ϊ���������϶��õ�
char const DELIMETER[] = {'#','$'};
int const DELIMETER_CNT = 10;
//��ĸ�����ĸ����
int const ALPHA_SIZE = 4;
//charתint
int L2I[256];
//�������ȵ���һ��
void initL2I(){
    L2I['A'] = 1;
    L2I['C'] = 2;
    L2I['G'] = 3;
    L2I['T'] = 4;
}

//�������飬���»��߿�ͷ
int _wa[SIZE],_wb[SIZE],_wv[SIZE],_ws[SIZE];
//��������
int _cmp(int const r[],int a,int b,int l){return r[a]==r[b]&&r[a+l]==r[b+l];}
//���׺����ı����㷨
//r: Դ���飬�ҳ�r[n-1]�⣬����r[i]>0
//n: r�ĳ���
//m: r�е�Ԫ��ȡֵ���Ͻ磬������r[i]<m
//sa:��׺���飬�����
void da(int const r[],int n,int m,int sa[]){
	int i,j,p,*x=_wa,*y=_wb,*t;
    for(i=0;i<m;i++) _ws[i] = 0;
    for(i=0;i<n;i++) _ws[x[i] = r[i]]++;
    for(i=1;i<m;i++) _ws[i] += _ws[i-1];
    for(i=n-1;i>=0;i--) sa[--_ws[x[i]]]=i;
    for(j=1,p=1;p<n;j*=2,m=p){
        for(p=0,i=n-j;i<n;i++) y[p++]=i;
        for(i=0;i<n;i++) if(sa[i]>=j) y[p++]=sa[i]-j;
        for(i=0;i<n;i++) _wv[i]=x[y[i]];
        for(i=0;i<m;i++) _ws[i]=0;
        for(i=0;i<n;i++) _ws[_wv[i]]++;
        for(i=1;i<m;i++) _ws[i] += _ws[i-1];
        for(i=n-1;i>=0;i--) sa[--_ws[_wv[i]]] = y[i];
        for(t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1;i<n;i++)
            x[sa[i]]=_cmp(y,sa[i-1],sa[i],j)?p-1:p++;
    }
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

int N,M;
char A[10][66];
int L[10],S[10],MinL;
int Rank[SIZE],Height[SIZE],SA[SIZE],R[SIZE];

int Ans,Start;
int const Flag[] = {0,1,3,7,0xF,0x1F,0x3F,0x7F,0xFF,0x1FF,0x3FF,0x7FF};
//�ж�idx��������һ���ַ���
int _g(int idx){
    for(int i=1;i<M;++i)if(idx<S[i]) return i - 1;
    return M - 1;
}

//����Ƿ�߱�length���ȵĹ����Ӵ�
//������ԣ�Height��������M��ֵ��С��length���Ҹ��ڸ���λ��
//startΪ�Ӵ���ʼideλ��
bool check(int length,int&start){
    int i = 1;
    while( i < N ){
        int flag = 0;
        start = 10000000;
        while( i < N && Height[i] >= length ){
            int pos = _g(SA[i-1]);
            if ( 0 == pos && SA[i-1] < start ) start = SA[i-1];
            flag |= 1 << pos;
            if ( Flag[M] == flag ){
                Start = start;
                return true;
            }
            ++i;
        }
        //*
        int pos = _g(SA[i-1]);
        if ( 0 == pos && SA[i-1] < start ) start = SA[i-1];
        flag |= 1 << pos;
        if ( Flag[M] == flag ){
            Start = start;
            return true;
        }
        //*/
        while( i < N && Height[i] < length ) ++i;
    }
    return false;
}

//��������
void proc(){
    int left = 1;    //������Ӵ�����С���ܴ�+1
    int right = MinL;//�����ܴ�
    int start;
    Ans = 0;

    do{
        int mid = ( left + right ) >> 1;
        if ( check(mid,start) ){
            left = mid + 1;
            if ( Ans < mid ) Ans = mid, Start = start;
        }else{
            right = mid - 1;
        }
    }while( left <= right );
}

void read(){
    scanf("%d",&M);
    for(int i=0;i<M;++i) scanf("%s",A[i]);

    //Ԥ�����ַ���
    N = 0 ;MinL = 10000000;
    for(int i=0;i<M;++i){
        L[i] = 0;S[i] = N;
        for(char*p=A[i];*p;++p,++L[i]) R[N++] = L2I[(int)*p];

        if ( L[i] < MinL ) MinL = L[i];
        R[N++] = ALPHA_SIZE + i + 1;
    }
    S[M] = N - 1;
    R[N-1] = 0;
}

int main(){
    //freopen("1.txt","r",stdin);

    initL2I();
    int nofkase;
    scanf("%d",&nofkase);
    while(nofkase--){
        read();

        da(R,N,ALPHA_SIZE+DELIMETER_CNT,SA);
        calHeight(R,SA,N,Rank,Height);

        proc();

        if ( Ans < 3 ){
            printf("no significant commonalities\n");
            continue;
        }

        for(int i=0,j=Start;i<Ans;++i,++j){
            putchar(A[0][j]);
        }
        putchar('\n');
    }
    return 0;
}
