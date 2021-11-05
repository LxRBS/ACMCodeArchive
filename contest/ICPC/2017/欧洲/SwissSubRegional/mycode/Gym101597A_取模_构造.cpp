/**
   2的幂次序列，对某个数M取模，得到一个数组
   然后将这个数组打乱顺序，给出。
   求最小的可能的M。
   打表发现只需解决M为奇数的情况
   当M为80的时候，取模结果为
   1 2 4 8 16 32 64 48 16 32 64 48
   去掉单独的1248，循环节除以16得到1243，这恰好是5的循环节
   如果模数组中奇数的数量不止1个，则M必然为奇数
   否则，模数组中必然只有1个1，此时M是偶数。
   找到剩下的数的最大2的幂的公约数，然后将所有数都除掉这个最大2幂公约数
   此时的模数组奇数数量必然不止1个（否则是一种特殊情况可以特判），可以用于求奇数M
   接下来考虑如何求奇数M。假设M是奇数，
   模数组一定是1, 2, 4, 偶数, ..., 偶数, 奇数, 偶数, ..., 偶数, 奇数, ...
   在{偶数, ..., 偶数, 奇数}完整的情况下，最大的奇数显然由最大的偶数生成
   但模数组给出的可能是截断的情况，即：数, ..., 偶数, 奇数, 偶数, ..., 偶数, {这里缺了一个奇数}
   这种情况下，由最大偶数生成的最大奇数并没有给出，那一定有次大偶数和次大奇数。
   注意次大奇数是指完整情况下的次大，此时该数实际上是已给出数组中的最大奇数。
   所以对已知数组求出最大偶数、次大偶数和最大奇数。则M必然是二者之一，验证一下即可。
*/
#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define mp make_pair

typedef long long int llt;
llt getULL(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	llt ret = (llt)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10LL + (llt)(ch-'0');
	return ret;
}

llt A[200010];
typedef unordered_map<llt,int> hash_t;
hash_t Map;

void insertMap(hash_t&m, llt key){
    hash_t::iterator it = m.find(key);
    if(it==m.end()){
        m.insert(it, mp(key, 1));
    }else{
        ++it->se;
    }
}

template<typename T>
void disp(const T a[],int n){
    for(int i=0;i<n;++i) cout<<a[i]<<" ";
    cout<<endl;
}

llt Pow2[65] = {1LL};
unordered_set<llt> PowSet;

int N;
llt MMax;

int get2(llt x){
    int k = 0;
    while((x&1)==0) x>>=1, ++k;
    return k;
}

bool check1(){
    for(hash_t::const_iterator it=Map.begin();it!=Map.end();++it){
        if(it->se>1) return false;
        if(PowSet.find(it->fi)==PowSet.end()) return false;
    }
    return true;
}

//在m所有的键中，找到最大的偶数和奇数，以及次大的偶数
void maxEvenOdd(hash_t const&m,llt&m1,llt&m2,llt&m4){
    m1 = m2 = m4 = 0;
    for(hash_t::const_iterator it=m.begin();it!=m.end();++it){
        if(it->fi&1) m1 = max(m1, it->fi);
        else if(it->fi>m2){
            m4 = m2, m2 = it->fi;
        }else if(it->fi>m4){
            m4 = it->fi;
        }
    }
}

//检查ans是否可以为答案
bool check2(hash_t&m, llt ans){
    llt x = 1;
    int n = m.size();
    for(int i=1;i<n;++i){
        x = x * 2 % ans;
        if(m.find(x)==m.end()) return false;
    }
    return true;
}


llt dfs(hash_t &m){
    //检查1的数量
    hash_t::const_iterator it = m.find(1);
    if(it==m.end()||it->se==0) throw runtime_error("XXXXXX");

    llt m1 = 0, m2 = 0, m4;
    maxEvenOdd(m, m1, m2, m4);

    //如果1不止1个，答案一定是奇数1只有1个;
    //且最大的奇数不是1，说明只有一个循环节，答案一样
    if(it->se>1 || m1>1){
        llt tmp = m4 + m4 - m1;
        if(tmp>m1&&tmp>m2&&check2(m, tmp)) return tmp;
        return m2 + m2 - m1;
    }

    //1只有1个，其他全是偶数，需要先把2去掉
    int pmax = 100;
    for(hash_t::iterator it=m.begin();it!=m.end();++it){
        if(it->fi!=1)pmax = min(pmax, get2(it->fi));
    }

    hash_t mmm;
    //造一个新map
    for(hash_t::iterator it=m.begin();it!=m.end();++it){
        if(it->fi!=1){
            mmm.insert(mp(it->fi/Pow2[pmax], it->se));
        }
    }
    return dfs(mmm) * Pow2[pmax];//实际上只递归一次
}

llt proc(){
    int powmax = 0;
    while(Pow2[powmax]<=MMax) ++powmax;
    --powmax;
    //答案一定在(2^powmax,2^(powmax+1)]之间


    if(Map.find(0)!=Map.end()){//如果有0，答案一定是2的幂
        return Pow2[powmax+1];
    }

    //如果恰好是2的幂数列，且每个数只有1个，答案是2^powmax+1
    if(check1()){
        return Pow2[powmax] + 1;
    }

    //以下进到正常流程
    return dfs(Map);
}

int main(){
    freopen("1.txt","r",stdin);
    PowSet.insert(1LL);
    for(int i=1;i<64;++i) {
        Pow2[i] = Pow2[i-1]<<1;
        if(Pow2[i]>0) PowSet.insert(Pow2[i]);
    }

    while(EOF!=scanf("%d",&N)){
        Map.clear();MMax = 0;

        for(int i=0;i<N;++i){
            insertMap(Map, A[i]=getULL());
            MMax = max(A[i], MMax);
        }
        printf("%lld\n", proc());
    }

    return 0;
}
