/**
   2���ݴ����У���ĳ����Mȡģ���õ�һ������
   Ȼ������������˳�򣬸�����
   ����С�Ŀ��ܵ�M��
   �����ֻ����MΪ���������
   ��MΪ80��ʱ��ȡģ���Ϊ
   1 2 4 8 16 32 64 48 16 32 64 48
   ȥ��������1248��ѭ���ڳ���16�õ�1243����ǡ����5��ѭ����
   ���ģ������������������ֹ1������M��ȻΪ����
   ����ģ�����б�Ȼֻ��1��1����ʱM��ż����
   �ҵ�ʣ�µ��������2���ݵĹ�Լ����Ȼ��������������������2�ݹ�Լ��
   ��ʱ��ģ��������������Ȼ��ֹ1����������һ����������������У�����������������M
   �������������������M������M��������
   ģ����һ����1, 2, 4, ż��, ..., ż��, ����, ż��, ..., ż��, ����, ...
   ��{ż��, ..., ż��, ����}����������£�����������Ȼ������ż������
   ��ģ��������Ŀ����ǽضϵ������������, ..., ż��, ����, ż��, ..., ż��, {����ȱ��һ������}
   ��������£������ż�����ɵ����������û�и�������һ���дδ�ż���ʹδ�������
   ע��δ�������ָ��������µĴδ󣬴�ʱ����ʵ�������Ѹ��������е����������
   ���Զ���֪����������ż�����δ�ż���������������M��Ȼ�Ƕ���֮һ����֤һ�¼��ɡ�
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

//��m���еļ��У��ҵ�����ż�����������Լ��δ��ż��
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

//���ans�Ƿ����Ϊ��
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
    //���1������
    hash_t::const_iterator it = m.find(1);
    if(it==m.end()||it->se==0) throw runtime_error("XXXXXX");

    llt m1 = 0, m2 = 0, m4;
    maxEvenOdd(m, m1, m2, m4);

    //���1��ֹ1������һ��������1ֻ��1��;
    //��������������1��˵��ֻ��һ��ѭ���ڣ���һ��
    if(it->se>1 || m1>1){
        llt tmp = m4 + m4 - m1;
        if(tmp>m1&&tmp>m2&&check2(m, tmp)) return tmp;
        return m2 + m2 - m1;
    }

    //1ֻ��1��������ȫ��ż������Ҫ�Ȱ�2ȥ��
    int pmax = 100;
    for(hash_t::iterator it=m.begin();it!=m.end();++it){
        if(it->fi!=1)pmax = min(pmax, get2(it->fi));
    }

    hash_t mmm;
    //��һ����map
    for(hash_t::iterator it=m.begin();it!=m.end();++it){
        if(it->fi!=1){
            mmm.insert(mp(it->fi/Pow2[pmax], it->se));
        }
    }
    return dfs(mmm) * Pow2[pmax];//ʵ����ֻ�ݹ�һ��
}

llt proc(){
    int powmax = 0;
    while(Pow2[powmax]<=MMax) ++powmax;
    --powmax;
    //��һ����(2^powmax,2^(powmax+1)]֮��


    if(Map.find(0)!=Map.end()){//�����0����һ����2����
        return Pow2[powmax+1];
    }

    //���ǡ����2�������У���ÿ����ֻ��1��������2^powmax+1
    if(check1()){
        return Pow2[powmax] + 1;
    }

    //���½�����������
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
