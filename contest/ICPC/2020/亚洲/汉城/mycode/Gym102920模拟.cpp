#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getUnsigned(){
	char ch = __hv007();
	while( ch < '0' || ch > '9' ) ch = __hv007();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = __hv007() ) && ch <= '9' ) ret = (ret<<1) + (ret<<3) + (int)(ch-'0');
	return ret;
}

typedef pair<int,int> pii;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
typedef vector<int> vi;

struct pair_hash{
	inline size_t operator()(const pii&p)const{
		return p.first * 1331 + p.second;
	}
};

bool operator < (const pii&lhs,const pii&rhs){
    return lhs.fi<rhs.fi||(lhs.fi==rhs.fi&&lhs.se<rhs.se);
}


int const SIZE = 550;
int N,T;

//坐标
int BX[SIZE], BY[SIZE], EX[SIZE], EY[SIZE];
int VH[SIZE]; //1表示横线，2表示竖线

vi Coor[SIZE]; // Coor[i]表示第i条线段上的所有交叉点，包括端点

//交点到线段的映射，每个交点最多属于两条线段
unordered_map<pii, pii, pair_hash> Jiao2Xian;
unordered_map<pii, pii, pair_hash>::iterator It;

void read(){
    N = getUnsigned();
    T = getUnsigned();
    for(int i=1;i<=N;++i){
        BX[i]=getUnsigned(),
        BY[i]=getUnsigned(),
        EX[i]=getUnsigned(),
        EY[i]=getUnsigned();
        VH[i] = (BX[i]==EX[i])?2:1;
    }
}

// idx和jdx是否相交
inline bool inter(int idx, int jdx){
    return VH[idx] ^ VH[jdx]
        && min(BX[idx], EX[idx]) <= max(BX[jdx], EX[jdx])
        && min(BX[jdx], EX[jdx]) <= max(BX[idx], EX[idx])
        && min(BY[idx], EY[idx]) <= max(BY[jdx], EY[jdx])
        && min(BY[jdx], EY[jdx]) <= max(BY[idx], EY[idx]) ;
}

//求idx和jdx的交点
bool inter(int idx,int jdx,int ans[]){
    if(!inter(idx, jdx)) return false;

    // idx是竖线
    if(VH[idx]&2){
        ans[1] = BX[idx], ans[2] = BY[jdx];
        return true;
    }

    // idx是横线
    ans[1] = BX[jdx], ans[2] = BY[idx];
    return true;
}

void preProc(){
    // 首先把端点塞进去
    for(int i=1;i<=N;++i){
        Jiao2Xian.insert(mp(mp(BX[i], BY[i]), mp(i, i)));
        Jiao2Xian.insert(mp(mp(EX[i], EY[i]), mp(i, i)));

        if(VH[i]&1){//横线
            Coor[i].pb(BX[i]);
            Coor[i].pb(EX[i]);
        }else if(VH[i]&2){//竖线
            Coor[i].pb(BY[i]);
            Coor[i].pb(EY[i]);
        }else{
            throw runtime_error("XXX32456677");
        }
    }

    // 对每条线段求交点
    for(int i=1;i<N;++i)for(int j=i+1;j<=N;++j){
        int ans[5];
        if(!inter(i, j, ans)) continue;

        //横线塞x坐标，竖线塞y
        Coor[i].pb(ans[VH[i]]);
        Coor[j].pb(ans[VH[j]]);

        Jiao2Xian.insert(mp(mp(ans[1], ans[2]), mp(i, j)));
    }

    //最后排个序
    for(int i=1;i<=N;++i){
        sort(Coor[i].begin(), Coor[i].end());
        /*测试输出
        cout<<i<<": ";
        for(auto c: Coor[i]){
            cout<<c<<" ";
        }
        cout<<endl;//*/
    }
}


//0123分别表示上下左右
//向左转
inline int turnLeft(int t){
    if(0==t) return 2;
    if(1==t) return 3;
    if(2==t) return 1;
    if(3==t) return 0;
    throw runtime_error("XXX1257");
}
//调头
inline int turnBack(int t){
    if(0==t) return 1;
    if(1==t) return 0;
    if(2==t) return 3;
    if(3==t) return 2;
    throw runtime_error("XXX2341");
}

//sx,sy是起点, ex、ey是终点，ori是新方向, vec是要走的那条链
int moveUp(int sx, int sy, int& ori, int& ex, int& ey, vi const& v){
    //找到起点在链上的位置
    auto p = equal_range(v.begin(), v.end(), sy);
    if(p.fi+1!=p.se||v.end()==p.se) throw runtime_error("XXXX2356");

    //保存结果
    ex = sx;
    ey = *p.se;

    //确定方向，要么左转要么调头
    ori = (p.se+1!=v.end()) ? 2 : 1;
    return ey - sy;
}

int moveDown(int sx, int sy, int& ori, int& ex, int& ey, vi const& v){
    //找到起点在链上的位置
    auto p = equal_range(v.begin(), v.end(), sy);
    if(p.fi+1!=p.se||v.begin()==p.fi) throw runtime_error("XXXX down");

    //保存结果
    ex = sx;
    ey = *--p.fi;

    //确定方向，要么左转要么调头
    ori = (p.fi!=v.begin()) ? 3 : 0;
    return sy - ey;
}


int moveRight(int sx, int sy, int& ori, int& ex, int& ey, vi const& v){
    //找到起点在链上的位置
    auto p = equal_range(v.begin(), v.end(), sx);
    if(p.fi+1!=p.se||v.end()==p.se) throw runtime_error("XXXX right");

    //保存结果
    ex = *p.se;
    ey = sy;

    //确定方向，要么左转要么调头
    ori = (p.se+1!=v.end()) ? 0 : 2;
    return ex - sx;
}


int moveLeft(int sx, int sy, int& ori, int& ex, int& ey, vi const& v){
    //找到起点在链上的位置
    auto p = equal_range(v.begin(), v.end(), sx);
    if(p.fi+1!=p.se||v.begin()==p.fi){
        int x=3;
        throw runtime_error("XXXX left");
    }

    //保存结果
    ex = *--p.fi;
    ey = sy;

    //确定方向，要么左转要么调头
    ori = (p.fi!=v.begin()) ? 1 : 3;
    return sx - ex;
}


//*
//起点，ori是输入输出参数，返回本步所花的时间
int move(int sx,int sy,int&ori, int&ex,int&ey){
    //printf("%d %d\n", sx, sy);

    //首先找到起点属于哪条线段
    It = Jiao2Xian.find(mp(sx, sy));
    if(Jiao2Xian.end()==It) throw runtime_error("XXX12789");

    //找到要走哪条线段
    int t = It->se.fi;
    if(0==ori||1==ori){
        if((VH[t]^2)) t = It->se.se;
        if((VH[t]^2)) throw runtime_error("XXXX2165");
    }else if(2==ori||3==ori){
        if((VH[t]^1)) t = It->se.se;
        if((VH[t]^1)){
            int  x=3;
            throw runtime_error("XXXX54");
        }
    }

    switch(ori){
    case 0:return moveUp(sx, sy, ori, ex, ey, Coor[t]);
    case 1:return moveDown(sx, sy, ori, ex, ey, Coor[t]);
    case 2:return moveLeft(sx, sy, ori, ex, ey, Coor[t]);
    case 3:return moveRight(sx, sy, ori, ex, ey, Coor[t]);
    }

    throw runtime_error("XXXX3456");
}
//*/

//走一轮，返回起点返回true，否则返回false
bool go(int sx, int sy, int&ori, int&ex, int&ey, int &time){
    time = 0;

    while(1){
        time += move(sx, sy, ori, ex, ey);
        sx = ex, sy = ey;
        if(time>=T) return false;
        if(ex==BX[1]&&ey==BY[1]) return true;
    }
}

//后退n秒
void backMove(int sx, int sy, int ori, int n, int&ex, int&ey){
    //确定回退的方向，如果是端点则不动，否则要左转
    It = Jiao2Xian.find(mp(ex, ey));
    if(Jiao2Xian.end()==It) throw runtime_error("YYYY");
    if(It->se.fi!=It->se.se) ori = turnLeft(ori);

    switch(ori){
    case 0:ex=sx;ey=sy+n;return;
    case 1:ex=sx;ey=sy-n;return;
    case 2:ey=sy;ex=sx-n;return;
    case 3:ey=sy;ex=sx+n;return;
    }
    throw runtime_error("ZZZER");
}

int main(){
    //freopen("1.txt","r",stdin);
    read(); // 读入
    preProc(); // 确定每个交点

    // 确定第一个端点的前进的方向
    int ori = 0;
    if(VH[1]&1){//横线
        if(BX[1]<EX[1]) ori = 3; //向右
        else ori = 2; //左
    }else if(VH[1]&2){
        ori = (BY[1]<EY[1])?0:1;
    }else{
        throw runtime_error("XXXX123");
    }

    int ex, ey, time;

    //如果返回了起点，还要再走一轮
    if(go(BX[1], BY[1], ori, ex, ey, time)){
        T %= time;
        //printf("time = %d\n", time);
        go(BX[1], BY[1], ori, ex, ey, time);
    }

    backMove(ex, ey, ori, time-T, ex, ey);
    printf("%d %d\n", ex, ey);
    return 0;
}