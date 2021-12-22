typedef long long llt;

#ifndef ONLINE_JUDGE
int const SIZE = 140;
#else
int const SIZE = 1010010;
#endif

bool isComp[SIZE] = {false};
llt P[SIZE] = {0};
int PCnt = 0;
llt Euler[SIZE] = {0,1};
bool HasRoot[SIZE] = {false, false, true, true, true};

/// 筛质数以及原根判别
void sieve(){
    llt tmp;
	for(int i=2;i<SIZE;++i){
		if ( !isComp[i] ) P[PCnt++] = i, Euler[i] = i - 1;
		
		for(int j=0;j<PCnt&&(tmp=i*P[j])<SIZE;++j){
			isComp[tmp] = true;
			
			if ( 0 == i % P[j] ){
				Euler[tmp] = Euler[i] * P[j];
				break;
			}else{
				Euler[tmp] = Euler[i] * ( P[j] - 1 );
			}
		}
	}
	for(int i=1;i<PCnt;++i){
		llt p = P[i];
		for(llt j=p;j<SIZE;j*=p) HasRoot[j] = true;
		for(llt j=p+p;j<SIZE;j*=p) HasRoot[j] = true;
	}
}

/// 质因子分解，n是待分解的数,p保存质因子，cnt是不同质因子的数量
void primeFactor(llt n, llt p[], int&cnt){
    cnt = 0;
    for(int i=0;i<PCnt&&P[i]*P[i]<=n;++i){
        if ( 0 == n % P[i] ){
            p[cnt++] = P[i];
            while( 0 == n % P[i] ) n /= P[i];
        }
    }
    if ( n != 1 ) p[cnt++] = n;
}

//returns a^n%mod
llt powerMod(llt a,llt n,llt mod){
    llt ret = 1;
    a %= mod;

    while( n ){
        if ( n & 1 ) ret = ret * a % mod;
        n >>= 1;
        a = a * a % mod;
    }
    return ret;
}

/// 找n的最小原根，保证有，tmp保存phi(n)的质因子分解
llt minPrimitiveRoot(llt n, llt tmp[]){
    /// 对phi(n)做质因子分解
	int cnt;
	llt phi = Euler[n];
    primeFactor(phi, tmp, cnt);
	for(llt g=2;g<n;++g){
		if(powerMod(g, phi, n) != 1) continue;

		bool flag = true;
		for(int i=0;i<cnt;++i){
			if(1 == powerMod(g, phi/tmp[i], n)){
				flag = false;
                break;
			}
		}
		if(flag) return g;
	}
	throw runtime_error("should not here");
}

llt gcd(llt a,llt b){
    while( b ){
        llt r = b;
        b = a % b;
        a = r;
    }
    return a;
}

/// 给定n求原根，放在a中，返回原根的数量
int getPrimitiveRoot(llt n, llt a[], llt tmp[]){
	if(!HasRoot[n]) return 0;
	if(2 == n) return a[0] = 1;

	int ans = 0;
    /// 找最小原根
    llt g = minPrimitiveRoot(n, tmp);

    /// 如果gcd(k, phi(n))=1, 则g^k是一个原根
	llt t = 1;
    for(int i=1,phi=Euler[n];i<phi;++i){
		(t *= g) %= n; // g^i
		if(1 == gcd(i, phi)){
			a[ans++] = t;
		}
	}
	return ans;
}
