#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getInt(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}

using llt = long long;
using vll = vector<llt>;
using vvll = vector<vll>;
using v3ll = vector<vvll>;


struct PBDS_BBT{ // pbds的红黑树实现二叉平衡树

using T = int;
using key_t = pair<T, int>; // 加时间戳，可以处理相同的键值
using value_t = int;

__gnu_pbds::tree<
    key_t, value_t, std::less<key_t>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update
>shu;

/// 插入键值对，k是键，timestamp是时间戳
void insert(const T & k, int timestamp, const value_t & v = 0){
    this->shu.insert({{k, timestamp}, v});
}

/// 删除键，保证k至少存在一个
void erase(const T & k){
    auto it = this->shu.lower_bound({k, 0});
    assert(it->first.first == k);
    this->shu.erase(it);
}

/// 查询k在树中的排名，最小的数排名为1
/// k可以不存在于树中，此时为假设k在树中的排名
int rank(const T & k)const{
    auto ret = this->shu.order_of_key({k, 0});
    return ret + 1;
}

/// 取出排名为第sn的键，最小的数为第1名
T select(int sn)const{
    assert(0 < sn && sn <= this->shu.size());
    auto it = this->shu.find_by_order(sn - 1);
    return it->first.first;
}

/// 求k的前驱，即比k小的最大的键，保证有
T pred(const T & k)const{
    auto it = this->shu.lower_bound({k, 0});
    assert(it != this->shu.begin());
    --it;
    return it->first.first;
}

/// 求k的后继，即比k大的最小的键，保证有
/// 需要传一个比目前时间戳更大的数
T succ(const T & k, int largestStamp = INT32_MAX)const{
    auto it = this->shu.upper_bound({k, largestStamp});
    assert(it != this->shu.end());
    return it->first.first;
}

int size()const{return this->shu.size();}

/// 返回最小值，保证树不为空
T min()const{return this->shu.begin()->first.first;}

/// 返回最大值，保证树不为空
T max()const{return (--this->shu.end())->first.first;}

}Tree;


int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif 
    int ans = 0;
    int stamp = 0;
    int last = 0;
    int n = getInt();
    int q = getInt();
    for(int i=0;i<n;++i){
        Tree.insert(getInt(), ++stamp);
    }
    while(q--){
        int cmd = getInt();
        switch(cmd){
            case 1:Tree.insert(getInt()^last, ++stamp);break;
            case 2:Tree.erase(getInt()^last);break;
            case 3:ans^=last=Tree.rank(getInt()^last);break;
            case 4:ans^=last=Tree.select(getInt()^last);break;
            case 5:ans^=last=Tree.pred(getInt()^last);break;
            case 6:ans^=last=Tree.succ(getInt()^last);break;
            default:assert(0);
        }
    }
    printf("%d\n", ans);
    return 0;
}
