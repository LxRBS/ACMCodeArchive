struct FenwickTree2D{ // 二维树状数组

using value_type = long long int;
using vec_type = vector<value_type>;

int n, m;
vector<vec_type> c;

FenwickTree2D() = default;

static int lowbit(int x){return x & -x;}

void init(int nn, int mm){this->c.assign((this->n=nn) + 1, vec_type((this->m=mm) + 1, 0));}

void modify(int x, int y, value_type delta){
    for(int i=x;i<=this->n;i+=lowbit(i))for(int j=y;j<=this->m;j+=lowbit(j))this->c[i][j] += delta;
}

value_type query(int x, int y)const{
    value_type ans = 0;
    for(int i=x;i;i-=lowbit(i))for(int j=y;j;j-=lowbit(j)) ans += this->c[i][j];
    return ans;
}

value_type query(int xs, int xe, int ys, int ye)const{
    return query(xe, ye) + query(xs - 1, ys - 1) - query(xe, ys - 1) - query(xs - 1, ye);
}

};