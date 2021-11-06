/**
    �������ɸ��㣬�мӵ��ɾ�������ÿһ�β���Ҫ��
    S(x) = SIGMA{SIGMA{dij^2}}
    ����dij��ʾi���j����ĳ��ֱ����ͶӰ�ľ���
    �൱�����ɷַ���������ת�������Ժ�ȡ��һάΪx�ᣬ��
    S(x) = sqrt(2 * Var(x))
    ��ԭά����Э�������
    [cov(x, x), cov(x, y)]
    [cov(x, y), cov(y, y)]
    �þ���Ľϴ�����ֵ��������
    cov(x, y) = E[(x-Ex)(y-Ey)]
    cov(x, x) = E[(x-Ex)^2] = var(x) ���Ƿ���
    ���ڷ���
    var(x) = 1/n*(x1^2+x2^2+...+nxƽ��^2-2(x1+x2+...)xƽ��)
           = 1/n*(SIGMA{xi^2} - xƽ��^2
           = E(x^2) - (Ex)^2
    ����Э����
    cov(x, y) = E(xy) - E(x)*E(y)
    ��˶��ڶ�̬��ֻ��ά��һЩ�ܺͼ���
    2��2�ľ��������ֵ���̣�x^2-(a11+a22)x+(a11a22-a21a12)=0
    ʹ��longlong��WA��Ҫ��int128
*/
//#include <bits/stdc++.h>
#include <stdio.h>
#include <math.h>
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

typedef __int128_t llt;

//��һԪ���η��̣����ؽϴ�Ľ�
double f(double a,double b,double c){
    double delta = b*b-4.0*a*c;
    if(delta<0) delta = 0.0;
    return (-b+sqrt(delta))*0.5/a;
}

llt X[1000010],Y[1000010];
int main(){
    //freopen("1.txt","r",stdin);

    int nofkase = getInt();
    while(nofkase--){
        int q = getInt();
        int cmd, n = 0;


        int cnt = 0;
        llt x, y;
        llt x2 = 0LL, y2 = 0LL;
        llt xy = 0LL;
        llt xs = 0LL, ys = 0LL;

        for(int qi=1;qi<=q;++qi){
            if(1==(cmd=getInt())){
                ++cnt;

                x = X[qi] = getInt();
                y = Y[qi] = getInt();

                x2 += x * x;
                y2 += y * y;
                xy += x * y;
                xs += x;
                ys += y;


            }else{
                --cnt;

                int t = getInt();
                x = X[t];
                y = Y[t];

                x2 -= x * x;
                y2 -= y * y;
                xy -= x * y;
                xs -= x;
                ys -= y;

            }

            double a11 = (x2 - xs*xs/(double)(cnt))/(double)cnt;
            double a22 = (y2 - ys*ys/(double)(cnt))/(double)cnt;
            double a12 = (xy - xs*ys/(double)(cnt))/(double)cnt;

            printf("%.12f\n",sqrt(2.0*f(1.0,-(a11+a22),a11*a22-a12*a12)));
        }
    }
    return 0;
}
