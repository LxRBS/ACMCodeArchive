/**
 * N个人，M轮。每一轮由一个人扔6个骰子，每个人轮流扔。
 * 根据扔出的点数组合，有不同的种类，当前玩家可以获得对应的种类的分数
 * 问最后，每个人每个种类各有多少分
 * 
 * 一秀和二举可以与某些种类并行
 * 满堂黑要拿走所有剩下的分数，除了状元
 * 状元要最后单独处理
 * 输入为空行即轮空，与之前的输入是对应，因此可以只根据输入来判断是否轮空
*/
#include<bits/stdc++.h>
using namespace std;

#define pb push_back
typedef vector<int> vi;

template<typename T>string value2string(const T &t){
    stringstream ss;
    ss<<t;
    return ss.str();
}

#ifndef ONLINE_JUDGE
int const SIZE = 120;
#else
int const SIZE = 1001000;
#endif

int const KONG = 0x10000; // 轮空
int const ZYAN = 1;    // 状元
int const DTAN = 2;    // 对堂
int const SHON = 4;    // 三红
int const SJIN = 8;    // 四进
int const ERJU = 0x10; // 二举
int const YXIU = 0x20; // 一秀
int const MHEI = 0x40; // 满堂黑

int const SIHONG = 0x100;  // 四红
int const WZDEKE = 0x200;  // 五子登科
int const WUHONG = 0x400;  // 五红
int const MNDJIN = 0x800;  // 满地锦
int const MTNCAI = 0x1000; // 满堂彩
int const JINHUA = 0x2000; // 状元插金花

int const WINN = 1;
int const LOST = 2;
int const DRAW = 4;

struct _t{
    int point[6];
    int type;
    int round; // 轮数，用来比较状元的
    _t():type(0){memset(point, 0, sizeof(point));}
    _t(const char s[]):type(0){
        memset(point, 0, sizeof(point));

        if('\0'==*s||'\n'==*s){
            return;
        }

        sscanf(s, "#%d#%d#%d#%d#%d#%d", point, point+1, point+2, point+3, point+4, point+5);
        // for(int i=0;i<6;++i)point[i] = vec[i];
        sort(point, point+6);
        if(0 == point[0]){ // NULL
            return;
        }

        int cnt[7] = {0};
        for(int i=0;i<6;++i)++cnt[point[i]];

        /// 挨个检查
        if(6 == cnt[4]){ // 状元满堂彩
            type = ZYAN | MTNCAI;
            return;
        }
        if(6 == cnt[3] || 6 == cnt[1] || 6 == cnt[2] || 6 == cnt[5] || 6 == cnt[6]){
            type = ZYAN | MNDJIN;
            if(6 == cnt[6]) type |= MHEI;
            return;
        }
        if(4 == cnt[4] && 2 == cnt[1]){
            type = ZYAN | JINHUA;
            return;
        }
        if(5 == cnt[4]){
            type = ZYAN | WUHONG;
            if(point[0] != 4) swap(point[0], point[5]);
            return;
        }
        if(5 == cnt[3] || 5 == cnt[1] || 5 == cnt[2] || 5 == cnt[5] || 5 == cnt[6]){
            type = ZYAN | WZDEKE;
            if(5!=cnt[point[0]]) swap(point[0], point[5]);
            if(4 == point[5]) type |= YXIU;
            return;
        }        
        if(4 == cnt[4]){
            type = ZYAN | SIHONG;
            vi v;
            for(int i=0;i<6;++i)if(4!=cnt[point[i]])v.pb(point[i]);
            assert(v.size()==2);
            point[0]=point[1]=point[2]=point[3]=4;
            point[4]=v[0];point[5]=v[1];
            return;
        }
        if(1==point[0]&&2==point[1]&&3==point[2]&&4==point[3]&&5==point[4]&&6==point[5]){
            type = DTAN;
            return;
        }
        if(3 == cnt[4]){
            type = SHON;
            vi v;
            for(int i=0;i<6;++i)if(4!=point[i])v.pb(point[i]);
            assert(v.size()==3);
            point[0] = point[1] = point[2] = 4;
            point[3] = v[0], point[4] = v[1], point[5] = v[2];
            return;
        }
        if(4 == cnt[1] || 4 == cnt[2] || 4 == cnt[3] || 4 == cnt[5] || 4 == cnt[6]){
            type = SJIN;
            vi v;
            int four = -1;
            for(int i=0;i<6;++i){
                if(4!=cnt[point[i]])v.pb(point[i]);
                else if(4==cnt[point[i]])four = point[i];
            }
            if(v.size()!=2 || four==-1) while(1);
            assert(v.size()==2 && four!=-1);
            point[0] = point[1] = point[2] = point[3] = four;
            point[4] = v[0]; point[5] = v[1];
            if(4 == point[5] && 4 == point[4]) type |= ERJU;
            else if(4==point[5] || 4==point[4]) type |= YXIU;
            return;
        }        
        if(2 == cnt[4]){
            type = ERJU;
            vi v;
            for(int i=0;i<6;++i)if(4!=point[i])v.pb(point[i]);
            // assert(v.size()==4);
            
            // if(v.size()!=4){
            //     while(1);
            //     throw runtime_error("v.size() == "+value2string(v.size()));
            // }
            point[0] = point[1] = 4;
            point[2] = v[0], point[3] = v[1], point[4] = v[2], point[5] = v[3];
            return;
        }
        if(1 == cnt[4]){
            type = YXIU;
            return;
        }
        return;
    }
    void disp()const{
        printf("%X:", type);
        for(int i=0;i<6;++i) printf(" %d", point[i]);
        printf("\n");
    }
};

int ZYanScore[SIZE]; // 状元
int DTanScore[SIZE]; // 对堂
int SHonScore[SIZE]; // 三红
int SJinScore[SIZE]; // 四进
int ErJuScore[SIZE]; // 二举
int YXiuScore[SIZE]; // 一秀

// int TotalZYan;
int TotalDtan;
int TotalSHon;
int TotalSJin;
int TotalErJu;
int TotalYXiu;

int N, M;

_t ZZ[SIZE];

bool Kong[SIZE] = {false};

int cmpZY(const _t &a, const _t &b){
    assert((a.type&ZYAN) && (b.type&ZYAN));
    int atype = a.type & 0xFF00;
    int btype = b.type & 0xFF00;
    if(atype != btype) return atype < btype ? LOST : WINN;

    if(atype & SIHONG){ // 四红
        int asum = a.point[4] + a.point[5];
        int bsum = b.point[4] + b.point[5];
        if(asum != bsum) return asum < bsum ? LOST : WINN;
    }else if(atype & WZDEKE){
        if(a.point[0] != b.point[0]) return *a.point < *b.point ? LOST : WINN;
        if(a.point[5] != b.point[5]) return a.point[5] < b.point[5] ? LOST : WINN;
    }else if(atype & WUHONG){
        if(a.point[5] != b.point[5]) return a.point[5] < b.point[5] ? LOST : WINN;    
    }else if(atype & MNDJIN){
        if(a.point[0] != b.point[0]) return *a.point < *b.point ? LOST : WINN;
    }else if(atype & MTNCAI){

    }else if(atype & JINHUA){

    }else{
        while(1);
        // throw runtime_error("wrong zhuangyuan");
    }
    if(a.round != b.round) return a.round < b.round ? WINN : LOST;
    return WINN;
}

/// 第index人
void proc(const _t &a, int index, int round){
    if(!a.type) return;

    if((a.type & YXIU) && TotalYXiu){ // 一秀是可以并行的
        --TotalYXiu;
        ++YXiuScore[index];
    }        
    if((a.type & ERJU) && TotalErJu){ // 二举
        ++ErJuScore[index];
        --TotalErJu;
    }
    if(a.type & MHEI){ // 满堂黑，全拿走
        DTanScore[index] += TotalDtan; TotalDtan = 0;
        SHonScore[index] += TotalSHon; TotalSHon = 0;
        SJinScore[index] += TotalSJin; TotalSJin = 0;
        ErJuScore[index] += TotalErJu; TotalErJu = 0;
        YXiuScore[index] += TotalYXiu; TotalYXiu = 0;
    }
    if(a.type & ZYAN){ // 状元要最后计算
        ZZ[index] = a;
        ZZ[index].round = round;
        return;
    }

    if(a.type & DTAN){
        if(TotalDtan){
            ++DTanScore[index];
            --TotalDtan;
        }
    }else if(a.type & SHON){
        if(TotalSHon){
            ++SHonScore[index];
            --TotalSHon;
        }
    }else if(a.type & SJIN){
        if(TotalSJin){
            ++SJinScore[index];
            --TotalSJin;
        }
    }else if(a.type & ERJU){

    }else if(a.type & YXIU){

    }else{
        while(1);
        throw runtime_error("wrong type");
    }
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif
    TotalDtan = 2;
    scanf("%d%d%d%d%d%d", &N, &M, &TotalSHon, &TotalSJin, &TotalErJu, &TotalYXiu);
    char s[110];
    fgets(s, 100, stdin);
    for(int b,c,d,e,f,g,i=1,j=0;i<=M;++i,++j%=N){
        // if(Kong[j+1]){
        //     Kong[j+1] = false;
        //     continue;
        // }
        // scanf("%s", s);
        // sscanf(s, "#%d#%d#%d#%d#%d#%d", &b, &c, &d, &e, &f, &g);
        // _t a({b,c,d,e,f,g});
        fgets(s, 100, stdin);
        _t a(s);
#ifndef ONLINE_JUDGE
        a.disp();
#endif
        proc(a, j+1, i);
    }
    /// 看状元
    int k = 1;
    while(k<=N && 0==ZZ[k].type) ++k;
    if(k<=N){
        for(int i=k+1;i<=N;++i){
            if(ZZ[i].type && (cmpZY(ZZ[k], ZZ[i]) & LOST)){
                k = i;
            }
        }
        ZYanScore[k] = 1;
    }

    for(int i=1;i<=N;++i){
        printf("%d %d %d %d %d %d\n", ZYanScore[i], DTanScore[i], SHonScore[i], SJinScore[i], ErJuScore[i], YXiuScore[i]);
    }
    return 0;
}

