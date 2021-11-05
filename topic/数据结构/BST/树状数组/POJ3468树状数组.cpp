/*
    �ɶ��޸ģ��������
*/
#include <stdio.h>
typedef long long llt;

int getInt(){
	int sgn = 1;
	char ch = getchar();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = getchar();
	if ( '-' == ch ) {sgn = 0;ch=getchar();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=getchar()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}

int const SIZE = 100010;

//��״����
llt C[SIZE],C2[SIZE];
int N,Q;

inline int lowbit(int n){return n&-n;}
//��xλ������delta
void modify(int x,llt delta){
    for(;x<=N;x+=lowbit(x))C[x] += delta;
}
//��ѯ[1,x]�������
llt query(int x){
    llt sum = 0;
    for(;x;x-=lowbit(x)) sum += C[x];
    return sum;
}
//�ڶ�����״����
void modify2(int x,llt delta){
    for(;x<=N;x+=lowbit(x))C2[x] += delta;
}
//��ѯ[1,x]�������
llt query2(int x){
    llt sum = 0;
    for(;x;x-=lowbit(x)) sum += C2[x];
    return sum;
}
//�ش�Դ����[1,x]�������
inline llt answer(int x){
    return x * query(x) - query2(x);
}
inline llt answer(int s,int e){
    return answer(e) - answer(s-1);
}

llt A[SIZE];
int main(){
    //freopen("1.txt","r",stdin);
    N = getInt();
    Q = getInt();
    for(int i=1;i<=N;++i)A[i]=getInt();

    modify(1,A[1]);
    //����������״����
    for(int i=2;i<=N;++i){
        modify(i,A[i]-A[i-1]);
        modify2(i,(i-1)*(A[i]-A[i-1]));
    }

    //������
    char cmd[3];
    int a,b,c;
    while(Q--){
        scanf("%s",cmd);
        a = getInt();
        if('Q' == *cmd){
            printf("%lld\n",answer(a,getInt()));
        }else{
            b = getInt();
            //�޸Ĳ������
            modify(a,c=getInt());
            modify(b+1,-c);
            //�޸�(i-1)�˲������
            modify2(a,(a-1)*(llt)c);
            modify2(b+1,(llt)b*-c);
        }

    }
    return 0;
}


