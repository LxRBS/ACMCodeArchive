/**
    ģ���⣬�����齫14���ƣ�Ҫ����һ�����ж�
    ÿ���ƿ�����������
*/
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
typedef vector<int> vi;

int const WAN = 0x10;
int const BIN = 0x20;
int const SUO = 0x40;
int const ZII = 0x80;
int const TOTAL = 34;
char PaiMian[0x100][3] = {0};
int BIANLI[40];
int L2I[256];

int Pai2Cnt[0x100];
vi Ans[0x100]; // ��¼��
vi AnsPai;

/// ��3���ƣ�n��ʾ�Ѿ��ҵ��˶���
bool dfs3(int n){
    if(4==n) { // �Ѿ��ҵ���4��
        return true;
    }

    /// ��ʣ�µ�ÿһ����
    for(int type,sn,cnt,pai,i=1;i<=TOTAL;++i){
        if(0==(cnt=Pai2Cnt[pai = BIANLI[i]])) continue;

        /// �����3��������
        if(cnt>=3){
            Pai2Cnt[pai] -= 3;
            bool b = dfs3(n+1);
            Pai2Cnt[pai] += 3;
            if(b) return true;
        }

        /// ����ֻ��˳��
        type = pai & 0xF0;
        sn = pai & 0xF;
        if(type!=ZII&&sn<=7&&Pai2Cnt[pai+1]&&Pai2Cnt[pai+2]){
            Pai2Cnt[pai] -= 1;
            Pai2Cnt[pai+1] -= 1;
            Pai2Cnt[pai+2] -= 1;
            bool b = dfs3(n+1);
            Pai2Cnt[pai] += 1;
            Pai2Cnt[pai+1] += 1;
            Pai2Cnt[pai+2] += 1;
            if(b) return true;
        }

        /// �����ǰ�ư��Ų���ȥ
        return false;
    }
    return false;
}

/// �ж��Ƿ����
bool isOK(){
    /// ��һ����
    for(int cnt,pai,i=1;i<=TOTAL;++i){
        if((cnt=Pai2Cnt[pai=BIANLI[i]])<2) continue;
        Pai2Cnt[pai] -= 2;
        bool b = dfs3(0);  //����
        Pai2Cnt[pai] += 2; //��ԭ
        if(b) return true;
    }
    return false;
}

/// ������ǰ�ƣ��Ƿ��ܹ����ƣ��Լ�����һ��
void proc(int cur){
    vi& vec = Ans[cur];
    --Pai2Cnt[cur];
    /// ��һ���ƣ��Ƿ��ܹ�����
    for(int cnt,pai,i=1;i<=TOTAL;++i){
        if(cur==(pai=BIANLI[i])) continue;
        //if(4==(cnt=Pai2Cnt[pai])) continue;

        ++Pai2Cnt[pai];
        if(isOK()){
            vec.pb(pai);
        }
        --Pai2Cnt[pai];
    }
    ++Pai2Cnt[cur];
    if(!vec.empty()) AnsPai.pb(cur);
}

int main(){
    //freopen("1.txt","r",stdin);
    L2I['w'] = WAN, L2I['z'] = ZII, L2I['b'] = BIN, L2I['s'] = SUO;
    for(int i=1;i<=9;++i){
        PaiMian[BIANLI[i] = WAN | i][0]
        = PaiMian[BIANLI[i+9] = BIN | i][0]
        = PaiMian[BIANLI[i+18] = SUO | i][0]
        = PaiMian[BIANLI[i+27] = ZII | i][0]
        = i+'0';

        PaiMian[WAN | i][1] = 'w';
        PaiMian[BIN | i][1] = 'b';
        PaiMian[SUO | i][1] = 's';
        PaiMian[ZII | i][1] = 'z';
    }

    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        //printf("case %d:\n", kase);
        char a[110];
        scanf("%s", a);
        /// ��ʼ��
        AnsPai.clear();
        memset(Pai2Cnt,0,sizeof(Pai2Cnt));
        for(int i=1;i<=TOTAL;++i)Ans[BIANLI[i]].clear();
        /// Ԥ����
        for(char const*p=a;*p;p+=2){
            ++Pai2Cnt[L2I[*(p+1)]|(*p-'0')];
        }
        /// �����ж��Ƿ�ֱ�Ӻ���
        if(isOK()){
            printf("Tsumo!\n");
            continue;
        }
        /// �����ÿһ����
        for(int cnt,pai,i=1;i<=TOTAL;++i){
            if(0==(cnt=Pai2Cnt[pai=BIANLI[i]])) continue;
            proc(pai);
        }
        /// ��ӡ��
        printf("%d\n",AnsPai.size());
        for(auto pai: AnsPai){
            printf("%s ", PaiMian[pai]);
            for(auto i: Ans[pai]){
                printf("%s", PaiMian[i]);
            }
            printf("\n");
        }

    }
    return 0;
}
