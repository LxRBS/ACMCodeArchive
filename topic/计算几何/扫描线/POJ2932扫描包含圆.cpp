/**
    若干个不相交的圆，问有多少个圆是不被其他圆包含的
    规模4万，不能用暴力法
    因为圆只存在包含关系，按y坐标排序后，外圆一定比内圆
    所以对每一个圆，如果它不被已知圆包含，它必然是一个外圆
    同时，如果当前考察的y坐标已经超出了圆的最高坐标，则以后的圆必然跟它没关系
    同时判断一个圆是否被已知圆包含，利用x坐标，只需判断其中2个即可
*/
#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <set>
#include <vector>
using namespace std;

int const SIZE = 80010;

struct _t{
    double radius,x,y;
}Circle[SIZE];

struct _t2{
    double y;
    int idx;
    bool flag;//true表示加入
}Y[SIZE];

bool operator < (_t2 const&lhs,_t2 const&rhs){
    return lhs.y < rhs.y || (lhs.y==rhs.y&&lhs.idx<rhs.idx);
}

int N;
bool read(){
    if(EOF==scanf("%d",&N)) return false;
    for(int i=1,k=0;i<=N;++i,k+=2){
        scanf("%lf%lf%lf",&Circle[i].radius,&Circle[i].x,&Circle[i].y);
        Y[k].y = Circle[i].y-Circle[i].radius;
        Y[k+1].y = Circle[i].y+Circle[i].radius;
        Y[k].idx = Y[k+1].idx = i;
        Y[k].flag = true;
        Y[k+1].flag = false;
    }
    return true;
}

set<pair<double,int> >Set;
vector<int>Ans;

bool isOK(int idx,int jdx){
    double x = Circle[idx].x - Circle[jdx].x;
    double y = Circle[idx].y - Circle[jdx].y;
    return sqrt(x*x + y*y) > Circle[idx].radius +Circle[jdx].radius;
}

int main(){
    //freopen("1.txt","r",stdin);
    for(int kase=1;read();++kase){
        Set.clear();
        Ans.clear();
        sort(Y,Y+N+N);

        for(int i=0,n=N<<1;i<n;++i){
            int idx = Y[i].idx;//第idx个圆
            if(Y[i].flag){//检查是否要加入
                //找到x坐标比第idx个圆刚好靠右的圆
                set<pair<double,int> >::iterator it = Set.lower_bound(make_pair(Circle[idx].x,idx));
                if(Set.end()!=it&&!isOK(idx,it->second)) continue;
                if(Set.begin()!=it&&!isOK(idx,(--it)->second)) continue;
                //加入
                Set.insert(make_pair(Circle[idx].x,idx));
                Ans.push_back(idx);
            }else{//删除
                Set.erase(make_pair(Circle[idx].x,idx));
            }
        }

        sort(Ans.begin(),Ans.end());
        printf("%d\n",Ans.size());
        if(!Ans.empty()){
            printf("%d",*Ans.begin());
            for(vector<int>::const_iterator it=++Ans.begin();it!=Ans.end();++it){
                printf(" %d",*it);
            }
            printf("\n");
        }
    }
    return 0;
}
