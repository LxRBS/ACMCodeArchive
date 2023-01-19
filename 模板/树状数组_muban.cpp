struct FenwickTree{ // 树状数组

using value_type = long long int;
using vec_type = vector<value_type>;

int n;
vec_type c;

FenwickTree() = default;

static int lowbit(int x){return x & -x;}

void init(int nn){this->c.assign((this->n=nn) + 1, 0);}

void modify(int pos, value_type delta){
    for(int i=pos;i<=this->n;i+=lowbit(i)) this->c[i] += delta;
}

value_type query(int pos)const{
    value_type ans = 0;
    for(int i=pos;i;i-=lowbit(i)) ans += this->c[i];
    return ans;
}

value_type query(int s, int e)const{return this->query(e) - this->query(s - 1);}

};