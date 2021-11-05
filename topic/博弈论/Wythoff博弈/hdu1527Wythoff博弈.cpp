/*
 * Wythoff Game
 * ����ʯ�ӵ���Ϸ����a=(sqrt(5)+1)/2, b = a + 1
 * ��(an,bn)Ϊ�ذܵ�
 * ��
 * an = floor(a^n), bn = floor(b^n)
 * ��
 * floor ( ( bn - an ) * a ) == an
 */

#include <cstdio>
#include <cmath>
double GOLD = (sqrt(5.0)+1.0) / 2.0;
int main(){
    int a,b;
    while( EOF != scanf("%d%d",&a,&b) ){
        if ( a > b ){int t=a;a=b;b=t;}

        if ( floor((b-a)*GOLD) == a ) puts("0");
        else puts("1");
    }
    return 0;
}

