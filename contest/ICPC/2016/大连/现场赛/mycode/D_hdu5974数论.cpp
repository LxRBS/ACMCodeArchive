/**
   给定a和b，求两个数x、y，使得
   x+y=a
   lcm(x,y)=b
   令g=gcd(x,y)，则x和y可以表示成ug与vg，
   其中，uv互质，且
   (u+v)g = a
   uvg = b
   这说明g是a、b的公因子，枚举每一个g
   解一个一元二次方程即可
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
