#include <iostream>
using namespace std;
typedef long long int int_t;

int_t const MOD = 100003LL;

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
    int_t m,n;
    cin >> m >> n;
    int_t ret = powerMod(m,n,MOD);
    ret = ( ret - m * powerMod(m-1,n-1,MOD) % MOD ) % MOD;
    if ( ret < 0 ) ret += MOD;
    cout << ret << endl;
    return 0;
}

