/**
 * 德州扑克，两个人各有手牌，有公共牌
 * 手牌选2张，公共牌选3张，组成一副最大的牌
 * 另外还有一个比low操作。
 * 根据胜负情况，分取奖金
*/
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
typedef vector<int> vi;

int const THSH = 9; // 同花顺
int const FOUR = 8; // 四条
int const HULU = 7; // 葫芦
int const FLSH = 6; // 同花
int const SHUN = 5; // 顺子
int const THRE = 4; // 三条
int const P222 = 3; // 两对
int const PAIR = 2; // 一对
int const HIGH = 1; // 高牌

int const WINN = 1;
int const LOST = 2;
int const DRAW = 4;

int MASK = 0xF;
int KIND = 0xF0;

int S2I[256];

inline void getPoint(const vi& a, int p[], bool b=false){
    for(int i=0;i<5;++i) {
        p[i] = a[i] & MASK;
        if(b && 14 == p[i]) p[i] = 1;
    }
    sort(p, p+5, greater<int>());
}

bool isTHSH(const vi&v, int tmp[]){
    int kind = v[0] & KIND;
    for(int i=1;i<5;++i){
        if(kind != (v[i] & KIND)){
            return false;
        }
    }

    getPoint(v, tmp);

    /// 首先看12345
    if(2==tmp[4]&&3==tmp[3]&&4==tmp[2]&&5==tmp[1]&&14==tmp[0]){
        for(int i=0;i<5;++i) tmp[i] = 5 - i;
        return true;
    }
    for(int i=1;i<5;++i){
        if(tmp[i-1]!=tmp[i]+1){
            return false;
        }
    }    
    return true;
}

bool isFOUR(const vi&v, int tmp[]){
    getPoint(v, tmp);

    int cnt[15] = {0};
    for(int i=0;i<5;++i) ++cnt[tmp[i]];

    int c4 = -1, c1 = -1;
    for(int i=2;i<=14;++i){
        if(cnt[i]==4){
            c4 = i;
        }else if(cnt[i]==1){
            c1 = i;
        }else if(cnt[i]!=0){
            return false;
        }
    }

    if(c4!=-1){
        assert(c1!=-1);
        tmp[0]=tmp[1]=tmp[2]=tmp[3]=c4;
        tmp[4] = c1;
        return true;
    }

    return false;
}

bool isHULU(const vi&v, int tmp[]){
    getPoint(v, tmp);
    int cnt[15] = {0};
    for(int i=0;i<5;++i) ++cnt[tmp[i]];

    int c3 = -1, c2 = -1;
    for(int i=2;i<=14;++i){
        if(cnt[i]==3){
            c3 = i;
        }else if(cnt[i]==2){
            c2 = i;
        }else if(cnt[i]!=0){
            return false;
        }
    }     
    assert(c3!=-1&&c2!=-1);
    tmp[0] = tmp[1] = tmp[2] = c3;
    tmp[3] = tmp[4] = c2;
    return true;   
}

bool isFLSH(const vi&v, int tmp[]){    
    int kind = v[0] & KIND;
    for(int i=1;i<5;++i){
        if(kind != (v[i] & KIND)){
            return false;
        }
    } 
    getPoint(v, tmp);
    return true;   
}

bool isSHUN(const vi&v, int tmp[]){
    getPoint(v, tmp);

    /// 首先看12345
    if(2==tmp[4]&&3==tmp[3]&&4==tmp[2]&&5==tmp[1]&&14==tmp[0]){
        for(int i=0;i<5;++i) tmp[i] = 5 - i;
        return true;
    }
    for(int i=1;i<5;++i){
        if(tmp[i-1]!=tmp[i]+1){
            return false;
        }
    }    
    return true;    
}

int getType(const vi&v, int tmp[]){
    getPoint(v, tmp); 

    int cnt[15] = {0};
    for(int i=0;i<5;++i) ++cnt[tmp[i]];

    vi c3, c2, c1;
    for(int i=14;i>=2;--i){
        if(cnt[i]==3){
            c3.pb(i);
        }else if(cnt[i]==2){
            c2.pb(i);
        }else if(cnt[i]==1){
            c1.pb(i);
        }
    }  
    if(!c3.empty()){
        assert(c3.size()==1&&c1.size()==2);
        tmp[0] = tmp[1] = tmp[2] = c3[0];
        tmp[3] = c1[0]; tmp[4] = c1[1];
        return THRE;        
    }
    if(c2.empty()){
        assert(c1.size()==5);
        return HIGH;
    }
    if(c2.size()==2){
        assert(c1.size()==1);
        tmp[0]=tmp[1]=c2[0];
        tmp[2]=tmp[3]=c2[1];
        tmp[4]=c1[0];
        return P222;
    }
    assert(c2.size()==1&&c1.size()==3);
    tmp[0]=tmp[1]=c2[0];
    copy(c1.begin(),c1.end(),tmp+2);
    return PAIR;
}

struct _t{
    int pai[5]; // 5张牌
    int type; // 牌型
    _t():type(0){memset(pai, 0, sizeof(pai));}
    _t(const vi& v):type(0){
        if(isTHSH(v, pai)){
            type = THSH;
            return;
        }
        if(isFOUR(v, pai)){
            type = FOUR;
            return;
        }
        if(isHULU(v, pai)){
            type = HULU;
            return;
        }
        if(isFLSH(v, pai)){
            type = FLSH;
            return;
        }
        if(isSHUN(v, pai)){
            type = SHUN;
            return;
        }
        type = getType(v, pai);
        return;
    }
    void disp()const{
        cout<<"Type: "<<type<<", ["<<pai[0];
        for(int i=1;i<5;++i)cout<<", "<<pai[i];
        cout<<"]"<<endl;
    }
};

int A[4], B[4], D[5];

inline void read(int a[], int n){
    char s[10];
    for(int i=0;i<n;++i){
        scanf("%s", s);
        a[i] = S2I[s[0]] | S2I[s[1]];
    }
}

/// 比高操作
int cmpHigh(const _t &a, const _t&b){
    if(a.type != b.type) return a.type < b.type ? LOST : WINN;
    for(int i=0;i<5;++i){
        if(a.pai[i] != b.pai[i]) return a.pai[i] < b.pai[i] ? LOST : WINN;
    }
    return DRAW;
}

/// 比低操作，确保可以比
int cmpLow(const _t &a, const _t&b){
    assert(a.type || b.type); // 不能同时为0
    if(a.type == 0) return LOST;
    if(b.type == 0) return WINN;
    for(int i=0;i<5;++i){
        if(a.pai[i] != b.pai[i]) return a.pai[i] > b.pai[i] ? LOST : WINN;
    }
    return DRAW;
}

/// 手牌和底牌选出最高的牌
_t mkHigh(int const sh[], int const di[]){
    _t ans;    
    for(int i=0;i<3;++i)for(int j=i+1;j<4;++j)
    for(int x=0;x<3;++x)for(int y=x+1;y<4;++y)for(int z=y+1;z<5;++z){        
        _t tmp({sh[i], sh[j], di[x], di[y], di[z]});
        if(ans.type == 0 || WINN == cmpHigh(tmp, ans)){
            ans = tmp;
        }
    }
    return ans;
}

bool getLow(_t &a, const vi &v){
    a.type = 0;
    getPoint(v, a.pai, true);
    if(a.pai[0] > 8) return false;
    
    int cnt[15] = {0};
    for(int i=0;i<5;++i) ++cnt[a.pai[i]];

    for(int i=1;i<=8;++i){
        if(cnt[i]>1) return false;
    }
    a.type = -1;
    return true;
}

_t mkLow(int const sh[], int const di[]){
    _t ans, tmp;
    for(int i=0;i<3;++i)for(int j=i+1;j<4;++j)
    for(int x=0;x<3;++x)for(int y=x+1;y<4;++y)for(int z=y+1;z<5;++z){        
        if(getLow(tmp, {sh[i], sh[j], di[x], di[y], di[z]})){
            if(ans.type == 0 || WINN == cmpLow(tmp, ans)){
                ans = tmp;
            }
        }

    }    
    return ans;
}

inline void output(int status, int salary){
    switch(status){
        case DRAW:printf("%d %d\n", salary-salary/2, salary/2);break;
        case WINN:printf("%d 0\n", salary, 0);break;
        case LOST:printf("0 %d\n", salary);break;
        throw runtime_error("wrong status");
    }
}

inline void get(int status, int salary, int a[]){
    switch(status){
        case DRAW:a[0]=salary-salary/2, a[1]=salary/2; break;
        case WINN:a[0]=salary, a[1]=0; break;
        case LOST:a[0]=0, a[1] = salary;break;
        throw runtime_error("wrong status");
    }    
}

void proc(const _t &ah, const _t &bh, const _t &al, const _t &bl, int salary){
#ifndef ONLINE_JUDGE    
    ah.disp(); bh.disp();
    al.disp(); bl.disp();
#endif    

    int hh[2];   
    if(al.type==0 && bl.type==0){ // 只比高
        get(cmpHigh(ah, bh), salary, hh);
        printf("%d %d\n", hh[0], hh[1]);
        return;
    } 
    
    int lmoney = salary / 2;
    int hmoney = salary - lmoney;
    int ll[2];
    get(cmpHigh(ah, bh), hmoney, hh);
    get(cmpLow(al, bl), lmoney, ll);
    printf("%d %d\n", hh[0]+ll[0], hh[1]+ll[1]);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif
    S2I['C'] = 0x10; S2I['D'] = 0x20; S2I['H'] = 0x30; S2I['S'] = 0x40;
    S2I['A'] = 14; S2I['T'] = 10; S2I['J'] = 11; S2I['Q'] = 12; S2I['K'] = 13;
    for(int i=2;i<=9;++i) S2I[i+'0'] = i;

    int nofkase;
    scanf("%d", &nofkase);
    while(nofkase--){
        int salary;
        scanf("%d", &salary);
        read(A, 4); read(B, 4); read(D, 5);

        _t ah = mkHigh(A, D);
        _t bh = mkHigh(B, D);
        _t al = mkLow(A, D);
        _t bl = mkLow(B, D);
        proc(ah, bh, al, bl, salary);
    } 

    return 0;
}
