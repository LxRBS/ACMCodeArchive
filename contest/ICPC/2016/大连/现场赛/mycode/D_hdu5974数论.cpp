/**
   ����a��b����������x��y��ʹ��
   x+y=a
   lcm(x,y)=b
   ��g=gcd(x,y)����x��y���Ա�ʾ��ug��vg��
   ���У�uv���ʣ���
   (u+v)g = a
   uvg = b
   ��˵��g��a��b�Ĺ����ӣ�ö��ÿһ��g
   ��һ��һԪ���η��̼���
*/
#include <bits/stdc++.h>
using namespace std;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

typedef int llt;

llt gcd(llt a,llt b){
    while( b ){
        llt r = b;
        b = a % b;
        a = r;
    }
    return a;
}

bool f(int a,int b,int&x,int&y){
    int g = 1, t,delta;
    while(g<=a){
        if(a%g==0&&b%g==0){
            int na = a/g;
            int nb = b/g;
            //print("%d: %d %d\n",g,na,nb);
            if((delta=na*na-4*nb)>=0){
                t = sqrt(delta)+0.005;
                if(t*t==delta&&(na-t)%2==0){
                    x = (na-t)/2;
                    y = na - x;
                    //printf("%d: %d %d\n",g, x,y);
                    if(gcd(x,y)==1){
                        x *= g;
                        y *= g;
                        return true;
                    }
                }
            }
        }
        ++g;
    }
    return false;
}

int main(){
    //freopen("damage.in","r",stdin);
    //freopen("damage.out","w",stdout);
    //freopen("1.txt","r",stdin);
    int a,b,x,y;
    while(2==scanf("%d%d",&a,&b)){
        if(f(a,b,x,y))printf("%d %d\n",x,y);
        else printf("No Solution\n");
    }
    return 0;
}

