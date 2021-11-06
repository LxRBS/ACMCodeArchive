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

//����
int BX[SIZE], BY[SIZE], EX[SIZE], EY[SIZE];
int VH[SIZE]; //1��ʾ���ߣ�2��ʾ����

vi Coor[SIZE]; // Coor[i]��ʾ��i���߶��ϵ����н���㣬�����˵�

//���㵽�߶ε�ӳ�䣬ÿ������������������߶�
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

// idx��jdx�Ƿ��ཻ
inline bool inter(int idx, int jdx){
    return VH[idx] ^ VH[jdx]
        && min(BX[idx], EX[idx]) <= max(BX[jdx], EX[jdx])
        && min(BX[jdx], EX[jdx]) <= max(BX[idx], EX[idx])
        && min(BY[idx], EY[idx]) <= max(BY[jdx], EY[jdx])
        && min(BY[jdx], EY[jdx]) <= max(BY[idx], EY[idx]) ;
}

//��idx��jdx�Ľ���
bool inter(int idx,int jdx,int ans[]){
    if(!inter(idx, jdx)) return false;

    // idx������
    if(VH[idx]&2){
        ans[1] = BX[idx], ans[2] = BY[jdx];
        return true;
    }

    // idx�Ǻ���
    ans[1] = BX[jdx], ans[2] = BY[idx];
    return true;
}

void preProc(){
    // ���ȰѶ˵�����ȥ
    for(int i=1;i<=N;++i){
        Jiao2Xian.insert(mp(mp(BX[i], BY[i]), mp(i, i)));
        Jiao2Xian.insert(mp(mp(EX[i], EY[i]), mp(i, i)));

        if(VH[i]&1){//����
            Coor[i].pb(BX[i]);
            Coor[i].pb(EX[i]);
        }else if(VH[i]&2){//����
            Coor[i].pb(BY[i]);
            Coor[i].pb(EY[i]);
        }else{
            throw runtime_error("XXX32456677");
        }
    }

    // ��ÿ���߶��󽻵�
    for(int i=1;i<N;++i)for(int j=i+1;j<=N;++j){
        int ans[5];
        if(!inter(i, j, ans)) continue;

        //������x���꣬������y
        Coor[i].pb(ans[VH[i]]);
        Coor[j].pb(ans[VH[j]]);

        Jiao2Xian.insert(mp(mp(ans[1], ans[2]), mp(i, j)));
    }

    //����Ÿ���
    for(int i=1;i<=N;++i){
        sort(Coor[i].begin(), Coor[i].end());
        /*�������
        cout<<i<<": ";
        for(auto c: Coor[i]){
            cout<<c<<" ";
        }
        cout<<endl;//*/
    }
}


//0123�ֱ��ʾ��������
//����ת
inline int turnLeft(int t){
    if(0==t) return 2;
    if(1==t) return 3;
    if(2==t) return 1;
    if(3==t) return 0;
    throw runtime_error("XXX1257");
}
//��ͷ
inline int turnBack(int t){
    if(0==t) return 1;
    if(1==t) return 0;
    if(2==t) return 3;
    if(3==t) return 2;
    throw runtime_error("XXX2341");
}

//sx,sy�����, ex��ey���յ㣬ori���·���, vec��Ҫ�ߵ�������
int moveUp(int sx, int sy, int& ori, int& ex, int& ey, vi const& v){
    //�ҵ���������ϵ�λ��
    auto p = equal_range(v.begin(), v.end(), sy);
    if(p.fi+1!=p.se||v.end()==p.se) throw runtime_error("XXXX2356");

    //������
    ex = sx;
    ey = *p.se;

    //ȷ������Ҫô��תҪô��ͷ
    ori = (p.se+1!=v.end()) ? 2 : 1;
    return ey - sy;
}

int moveDown(int sx, int sy, int& ori, int& ex, int& ey, vi const& v){
    //�ҵ���������ϵ�λ��
    auto p = equal_range(v.begin(), v.end(), sy);
    if(p.fi+1!=p.se||v.begin()==p.fi) throw runtime_error("XXXX down");

    //������
    ex = sx;
    ey = *--p.fi;

    //ȷ������Ҫô��תҪô��ͷ
    ori = (p.fi!=v.begin()) ? 3 : 0;
    return sy - ey;
}


int moveRight(int sx, int sy, int& ori, int& ex, int& ey, vi const& v){
    //�ҵ���������ϵ�λ��
    auto p = equal_range(v.begin(), v.end(), sx);
    if(p.fi+1!=p.se||v.end()==p.se) throw runtime_error("XXXX right");

    //������
    ex = *p.se;
    ey = sy;

    //ȷ������Ҫô��תҪô��ͷ
    ori = (p.se+1!=v.end()) ? 0 : 2;
    return ex - sx;
}


int moveLeft(int sx, int sy, int& ori, int& ex, int& ey, vi const& v){
    //�ҵ���������ϵ�λ��
    auto p = equal_range(v.begin(), v.end(), sx);
    if(p.fi+1!=p.se||v.begin()==p.fi){
        int x=3;
        throw runtime_error("XXXX left");
    }

    //������
    ex = *--p.fi;
    ey = sy;

    //ȷ������Ҫô��תҪô��ͷ
    ori = (p.fi!=v.begin()) ? 1 : 3;
    return sx - ex;
}


//*
//��㣬ori������������������ر���������ʱ��
int move(int sx,int sy,int&ori, int&ex,int&ey){
    //printf("%d %d\n", sx, sy);

    //�����ҵ�������������߶�
    It = Jiao2Xian.find(mp(sx, sy));
    if(Jiao2Xian.end()==It) throw runtime_error("XXX12789");

    //�ҵ�Ҫ�������߶�
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

//��һ�֣�������㷵��true�����򷵻�false
bool go(int sx, int sy, int&ori, int&ex, int&ey, int &time){
    time = 0;

    while(1){
        time += move(sx, sy, ori, ex, ey);
        sx = ex, sy = ey;
        if(time>=T) return false;
        if(ex==BX[1]&&ey==BY[1]) return true;
    }
}

//����n��
void backMove(int sx, int sy, int ori, int n, int&ex, int&ey){
    //ȷ�����˵ķ�������Ƕ˵��򲻶�������Ҫ��ת
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
    read(); // ����
    preProc(); // ȷ��ÿ������

    // ȷ����һ���˵��ǰ���ķ���
    int ori = 0;
    if(VH[1]&1){//����
        if(BX[1]<EX[1]) ori = 3; //����
        else ori = 2; //��
    }else if(VH[1]&2){
        ori = (BY[1]<EY[1])?0:1;
    }else{
        throw runtime_error("XXXX123");
    }

    int ex, ey, time;

    //�����������㣬��Ҫ����һ��
    if(go(BX[1], BY[1], ori, ex, ey, time)){
        T %= time;
        //printf("time = %d\n", time);
        go(BX[1], BY[1], ori, ex, ey, time);
    }

    backMove(ex, ey, ori, time-T, ex, ey);
    printf("%d %d\n", ex, ey);
    return 0;
}
