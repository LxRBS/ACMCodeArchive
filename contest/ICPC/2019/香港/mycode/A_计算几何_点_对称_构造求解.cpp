/**
   给定若干个横平竖直的矩形，保证矩形的交集的面积为0
   把所有矩形看成一个整体，求出该整体的所有对称轴
   只有可能有4个对称轴，水平、竖直、斜线与反斜线。
   注意如果矩形与矩形共边，则内部的边不需要再考虑
   矩形与矩形共同构成的大图形，其顶点一定是原矩形中的顶点
   而且出现次数为偶数的顶点不需要再考虑。
   且由题意，只需验证顶点对称即可。
*/
#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define mp make_pair

int getInt(){
	int sgn = 1;
	char ch = getchar();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = getchar();
	if ( '-' == ch ) {sgn = 0;ch=getchar();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=getchar()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}

typedef pair<int,int> pii;
struct pair_hash{
	inline size_t operator()(const pii&p)const{
		return p.first * 1331 + p.second;
	}
};

typedef unordered_map<pii, int, pair_hash> hash_t;

void insertMap(hash_t &m, pii const&key){
    hash_t::iterator it = m.find(key);
    if(it==m.end()){
        m.insert(mp(key, 1));
    }else{
        ++it->se;
    }
}

struct ans_t{
    int a,b,c;
    ans_t(int aa=0,int bb=0,int cc=0):a(aa),b(bb),c(cc){}
    bool operator<(const ans_t&rhs)const{
        return a>rhs.a||(a==rhs.a&&b>rhs.b)||(a==rhs.a&&b==rhs.b&&c>rhs.c);
    }
};

hash_t Map;
int N;
int Xmin,Xmax,Ymin,Ymax;
vector<ans_t> Ans;

//检查水平对称轴
void check1(){
    int a = 0, b = 2, c = Ymin + Ymax;

    //每个点都必须有对称点
    for(hash_t::const_iterator it=Map.begin();it!=Map.end();++it){
        if(it->fi.se*2==c) continue;
        if(Map.find(mp(it->fi.fi, c-it->fi.se))!=Map.end())continue;
        return;
    }

    if(c%2==0) b = 1, c >>= 1;
    Ans.push_back(ans_t(a,b,c));
    return;
}

//竖直
void check2(){
    int a = 2, b = 0, c = Xmin + Xmax;

    //每个点都必须有对称点
    for(hash_t::const_iterator it=Map.begin();it!=Map.end();++it){
        if(it->fi.fi*2==c) continue;
        if(Map.find(mp(c-it->fi.fi, it->fi.se))!=Map.end())continue;
        return;
    }

    if(c%2==0) a = 1, c >>= 1;
    Ans.push_back(ans_t(a,b,c));
    return;
}

//正对角线
void check3(){
    //一定过中心点
    int a = 2, b = -2, c = (Xmin+Xmax) - (Ymin+Ymax);
    if(c&1) return;

    c >>= 1;

    //每个点都必须有对称点
    for(hash_t::const_iterator it=Map.begin();it!=Map.end();++it){
        //printf("%d %d\n",it->fi.fi,it->fi.se);
        if(it->fi.fi-it->fi.se==c) continue;
        if(Map.find(mp(it->fi.se+c,it->fi.fi-c))!=Map.end())continue;
        return;
    }

    Ans.push_back(ans_t(1,-1,c));
    return;
}

void check4(){
    //一定过中心点
    int a = 2, b = 2, c = (Xmin+Xmax) + (Ymin+Ymax);
    if(c&1) return;

    c >>= 1;

    //每个点都必须有对称点
    for(hash_t::const_iterator it=Map.begin();it!=Map.end();++it){
        if(it->fi.fi-it->fi.se==c) continue;
        if(Map.find(mp(c-it->fi.se, c-it->fi.fi))!=Map.end())continue;
        return;
    }

    Ans.push_back(ans_t(1,1,c));
    return;
}

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase = getInt();
    while(nofkase--){
        Map.clear();

        int N = getInt();
        for(int x1,y1,x2,y2,i=0;i<N;++i){
            x1 = getInt();
            y1 = getInt();
            x2 = getInt();
            y2 = getInt();
            insertMap(Map, pii({x1,y1}));
            insertMap(Map, pii({x1,y2}));
            insertMap(Map, pii({x2,y1}));
            insertMap(Map, pii({x2,y2}));
        }

        //把奇数数量去掉
        hash_t::iterator it = Map.begin();
        while(it!=Map.end()){
            if(it->se&1){
                ++it;
            }else{
                it = Map.erase(it);
            }
        }

        //最大最小值
        Xmin = Ymin = 2000000000;
        Xmax = Ymax = -2000000000;
        for(hash_t::const_iterator it=Map.begin();it!=Map.end();++it){
            Xmin = min(Xmin, it->fi.fi);
            Ymin = min(Ymin, it->fi.se);
            Xmax = max(Xmax, it->fi.fi);
            Ymax = max(Ymax, it->fi.se);
        }

        Ans.clear();
        check1();
        check2();
        check3();
        check4();

        sort(Ans.begin(),Ans.end());
        printf("%d\n",(int)Ans.size());
        for(auto ans: Ans)printf("%d %d %d ",ans.a,ans.b,ans.c);
        printf("\n");
    }
    return 0;
}
