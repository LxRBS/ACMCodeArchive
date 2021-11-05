/*
    求[1,n]之间约数和为偶数的数的个数

    令fn为n的约数和
    f(n)=(1+p1+p1^2+...+p1^k1)...

    如果n只包含奇质因子，则只要有一个1+k为偶数，fn必然为偶数
    所以要求所有的k为偶数，则fn为奇数
    所有的k为偶数，则n是平方数。

    如果n包含质因子2，则如果n只有一个2的因子，则当n是平方数时，
    仍然可以保持fn是奇数
    如果n含有2个及2个以上的2的因子，则仍然可以将n视为某个平方数的2倍

    所以，综合起来，如果n是平方数或者平方数的2倍，fn是奇数
    其他情况，fn是偶数
    也就是求出n以内平方数的数量以及2倍平方数的数量
*/

#include <math.h>
#include <iostream>
using namespace std;

int main(){
    int nofkase;
    cin>>nofkase;
    for(int kase=1;kase<=nofkase;++kase){
        long long n;
        cin>>n;
        cout<<"Case "<<kase<<": "<<n-(long long)sqrt(n)-(long long)sqrt(n>>1)<<endl;
    }
}
