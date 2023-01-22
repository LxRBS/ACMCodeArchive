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
