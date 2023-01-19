/// 解二次同余方程的Cipolla算法
namespace Cipolla{

using llt = long long;

llt powerMod(llt a, llt n, llt mod){
	llt ret = 1;
	a %= mod;
	while(n){
		if(n & 1) ret = ret * a % mod;
		n >>= 1;
		a = a * a % mod;
	}
	return ret;
}

/// 仿复数运算
using complex_t = pair<llt, llt>;

complex_t mul(const complex_t & a, const complex_t & b, llt const i2, llt p){
    return make_pair
	(
		(a.first*b.first%p+i2*a.second%p*b.second%p)%p,
		(a.first*b.second%p+a.second*b.first%p)%p
    );
}

complex_t powerMod(complex_t a,llt n,llt const i2,llt p){
    complex_t ans = make_pair(1,0);
    while(n){
        if(n&1) ans = mul(ans,a,i2,p);
        a = mul(a,a,i2,p);
        n>>=1;
    }
    return ans;
}

/**
 * @brief 勒让德符号，判断a是否为p的二次剩余
 * @param a 
 * @param p 正奇数
 * @return int 是返回1，否返回-1
 */
int Legendre(llt a, llt p){
    a %= p;
	if(0 == a || 1 == a) return 1;
	if(-1 == a)switch(p % 4){
		case 1:return 1; case 3: return -1; default: return 0;
	}
	if(2 == a)switch(p % 8){
		case 1: case 7: return 1; case 3: case 5: return -1; default: return 0;
	}
	/// 分解出-1
	if(a < 0) return Legendre(-a, p) * Legendre(-1, p);
	/// 分解出2
	int k = 0;
	while(!(a & 1)) a >>= 1, ++k;
	if(k) return (-1 == Legendre(2, p) && (k & 1)) ? -Legendre(a, p) : Legendre(a, p);
    /// 上下颠倒
	return 1 == a % 4 || 1 == p % 4 ? Legendre(p, a) : -Legendre(p, a);
}

/**
 * @brief Cipolla算法，解二次同余方程 x^2 = n (mod p)
 *  
 * @param n 
 * @param p 
 * @param x0 
 * @param x1 
 * @return int 返回解的数量，必然是012之一
 */
int run(llt n, llt p, llt & x0, llt & x1){
    /// 特判
	if(0 == n) return x0 = x1 = 0, 1;
	if(1 == n) return x0 = 1, x1 = p - 1, 2;
	if(-1 == Legendre(n, p)) return 0;

	n %= p;
	if(n < 0) n += p;

    if(3 == p % 4){//n^((p+1)/2)必然是一个解
        x0 = powerMod(n, (p+1)>>2, p);
    }else if(5 == p % 8){//n^((p+3)/8)与2n*(4n)^((p-5)/8)其中必然有一个是解
        x0 = powerMod(n, (p+3)>>3, p);
        if((x0 * x0 - n) % p) x0 = (n + n) % p * powerMod(4*n%p, (p-5)>>3, p);
    }else{//Cipolla算法
        llt a = rand() % p;
        while(0 == a || 1==Legendre(a * a - n, p)) a = rand()%p;
        x0 = powerMod(make_pair(a, 1), (p+1)>>1, (a * a - n + p) % p, p).first;
    }

    x1 = p - x0;
    if(x0 == x1) return 1;
    if(x0 > x1) swap(x0, x1);
    return 2;
}

}
