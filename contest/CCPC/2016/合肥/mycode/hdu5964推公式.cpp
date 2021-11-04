/**
  N个点和2条直线
  在N个点中选两个点为B、B'
  直线上各选一个点为A、A'
  且ABA'B'是平行四边形
  求面积最大
  N在100万

  基本的想法是在点集中枚举2个点，需要O(N^2)，肯定超时
  所以应该有O(NlogN)或者O(N)，
  如果是logN，一般得考虑分治、二分、倍增，更多的是偏向算法设计
  最后经过数学推导，发现其实是O(N)

  令B(x1,y1),B'(x2,y2)
  令A(u,v),则A'(x1+x2-u,y1+y2-v)
  由于A和A'各自要满足直线方程
  au+bv=0
  a'(x1+x2-u)+b'(y1+y2-v)=0
  所以解出
  u=b(a'(x1+x2)+b'(y1+y2))/(a'b-ab')
  v=a(a'(x1+x2)+b'(y1+y2))/(ab'-a'b)
  平行四边形的面积等于向量的叉乘，即|A'-A|×|B'-B|
  S=2x1y2-2x2y1+2u(y1-y2)+2v(x2-x1)
  =[(aa'x1x1+bb'y1y1+(ab'+a'b)x1y1)-(aa'x2x2+bb'y2y2+(ab'+a'b)x2y2)]/(ab'-a'b)
  令f(x,y)=aa'xx+bb'yy+(ab'+a'b)xy
  则S=(f(x1,y1)-f(x2,y2))/(ab'-a'b)
  因此求出f(x,y)的最大值与最小值即可
  所以O(N)
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
