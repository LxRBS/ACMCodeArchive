/*
    �ⷽ�̣�x^(eb) = (eb)^x
    ȡ������ eb ln(x) = x ln(eb)
    ln(x) / x = ln(eb) / eb

    ���ǵ� f(x) = ln(x) / x ������
    f'(x) = ( 1 - lnx ) / x^2
    ������(0,e]�����������㣬��������ֵ��Ϊ(-INF,1/e]
    ��[e,INF)������С���㣬��������ֵ��Ϊ(0,1/E]
                                                         
    ����ʲô����������������                                                     
*/

#include <stdio.h>
#include <math.h>
#include <iostream>
#include <iomanip>
using namespace std;

long double const E = exp(1.0);
long double const invE = 1.0 / E;
long double const EPS = 1E-10;
inline bool is0(long double x){
    return -EPS <= x && x <= EPS;
}

long double proc(long double b){
    long double left = EPS, right = E, mid;
    long double fx;
    do{
        mid = left + ( right - left ) / 2.0;
        fx = log(mid) / mid;
        if ( is0( fx - b ) ) return mid;
        else if ( fx < b ) left = mid;
        else right = mid;
    }while( left < right );
}

int main(){
    long double b,y;
    while(cin>>y){
        b = y * E;
        b = log(b) / b;

        if ( !is0(b-invE) && b > invE ){
            cout<<"Happy to Women��s day!\n";
            continue;
        }

        if ( is0(b-invE) ){
            cout<<fixed<<setprecision(5)<<E<<endl;
            continue;
        }

        cout<<fixed<<setprecision(5)<<proc(b)<<" "<<E*y<<endl;
    }
}
