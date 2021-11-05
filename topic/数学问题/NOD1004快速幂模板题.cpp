#include <iostream>
using namespace std;

typedef long long int_t;

//returns a^n%mod
int_t powerMod(int_t a,int_t n,int_t mod){
    int_t ret = 1;
    a %= mod;

    while( n ){
        if ( n & 1 ) ret = ret * a % mod;
        n >>= 1;
        a = a * a % mod;
    }
    return ret;
}

int main(){
    int_t n;
    cin >> n;
    cout<<powerMod(n,n,10LL)<<endl;
    return 0;
}
