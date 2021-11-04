/**
  N�����2��ֱ��
  ��N������ѡ������ΪB��B'
  ֱ���ϸ�ѡһ����ΪA��A'
  ��ABA'B'��ƽ���ı���
  ��������
  N��100��

  �������뷨���ڵ㼯��ö��2���㣬��ҪO(N^2)���϶���ʱ
  ����Ӧ����O(NlogN)����O(N)��
  �����logN��һ��ÿ��Ƿ��Ρ����֡��������������ƫ���㷨���
  ��󾭹���ѧ�Ƶ���������ʵ��O(N)

  ��B(x1,y1),B'(x2,y2)
  ��A(u,v),��A'(x1+x2-u,y1+y2-v)
  ����A��A'����Ҫ����ֱ�߷���
  au+bv=0
  a'(x1+x2-u)+b'(y1+y2-v)=0
  ���Խ��
  u=b(a'(x1+x2)+b'(y1+y2))/(a'b-ab')
  v=a(a'(x1+x2)+b'(y1+y2))/(ab'-a'b)
  ƽ���ı��ε�������������Ĳ�ˣ���|A'-A|��|B'-B|
  S=2x1y2-2x2y1+2u(y1-y2)+2v(x2-x1)
  =[(aa'x1x1+bb'y1y1+(ab'+a'b)x1y1)-(aa'x2x2+bb'y2y2+(ab'+a'b)x2y2)]/(ab'-a'b)
  ��f(x,y)=aa'xx+bb'yy+(ab'+a'b)xy
  ��S=(f(x1,y1)-f(x2,y2))/(ab'-a'b)
  ������f(x,y)�����ֵ����Сֵ����
  ����O(N)
*/
#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;

int getInt(){
    int sgn = 1;
    char ch = getchar();
    while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = getchar();
    if ( '-' == ch ) {sgn = 0;ch=getchar();}

    int ret = (int)(ch-'0');
    while( '0' <= (ch=getchar()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
    return sgn ? ret : -ret;
}

typedef long long int llt;

llt A,B,Ap,Bp;
llt AAp,BBp,ABpBAp;

int main(){
    //freopen("2.txt","r",stdin);
    int a,b,ap,bp;
    while(EOF!=scanf("%d%d%d%d",&a,&b,&ap,&bp)){
        int n = getInt();

        A=a;B=b;Ap=ap;Bp=bp;
        AAp=A*Ap;BBp=B*Bp;ABpBAp=A*Bp+B*Ap;
        llt mmin = 0x7FFFFFFFFFFFFFFF;
        llt mmax = 0x8000000000000000;
        for(int i=0;i<n;++i){
            llt x = getInt();
            llt y = getInt();
            llt tmp = AAp*x*x+BBp*y*y+(ABpBAp)*x*y;
            if(tmp<mmin) mmin = tmp;
            if(mmax<tmp) mmax = tmp;
        }
        llt ret = fabs((double)(mmax-mmin)/(double)(A*Bp-Ap*B))+0.5;
        if(ret<0) ret=-ret;
        printf("%lld\n",ret);
    }
    return 0;
}
