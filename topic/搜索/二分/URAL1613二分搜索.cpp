/*
    给定一个数组A，再给定Q个询问
    问：A[L...R]之间有没有num存在
    预处理，Vk记录值为k出现的位置
    对每个num，在Vnum中二分搜索有没有满足L<=Vnum,i<=R的存在
*/
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

struct hash_t{
    typedef int key_t;
    typedef int value_t;
    enum{MOD=0x1FFFFF};

    key_t keys[MOD+1];
    value_t values[MOD+1];

    int head[MOD+1];
    int next[MOD+1];

    int toUsed;

    hash_t():toUsed(0){fill(head,head+MOD+1,-1);}

    void clear(){toUsed=0;fill(head,head+MOD+1,-1);}

    void insert(key_t const&key,value_t const&value){
        int k = key & MOD;
        keys[toUsed] = key;
        values[toUsed] = value;
        next[toUsed] = head[k];
        head[k] = toUsed++;
    }

    value_t find(key_t const&key)const{
        int k = key & MOD;
        for(int i=head[k];i!=-1;i=next[i]){
            if ( keys[i] == key ) return values[i];
        }
        return -1;
    }
}Hash;

int const SIZE = 70010;
int A[SIZE];
vector<int> Vec[SIZE];
char Output[SIZE];

int main(){
    //freopen("1.txt","r",stdin);
    int n = getUnsigned();
    int cnt = 0,tmp;
    for(int i=1;i<=n;++i){
        A[i] = getUnsigned();
        if ( -1 == ( tmp = Hash.find(A[i]) ) ) Hash.insert(A[i],tmp=cnt++);
        Vec[tmp].push_back(i);
    }

    int a,b,num,q = getUnsigned();
    for(int i=0;i<q;++i){
        a = getUnsigned();
        b = getUnsigned();
        num = getUnsigned();
        if ( -1 != ( tmp = Hash.find(num) ) && lower_bound(Vec[tmp].begin(),Vec[tmp].end(),a) < upper_bound(Vec[tmp].begin(),Vec[tmp].end(),b) ) Output[i] = '1';
        else Output[i] = '0';
    }

    printf("%s\n",Output);
    return 0;
}
