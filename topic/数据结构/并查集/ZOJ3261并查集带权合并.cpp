/*
    ����֮����ͨ�������������ɲ���
    destroy a b���ƻ�a��b֮�����ϵ
    query a���ҳ���a������Ȩֵ��������

    ���鼯ֻ���������Ӳ�����
    �����ֶϿ����������Կ������߶����ٷ������

    �����ںϲ���ʱ��Ҫʼ�հ�Ȩֵ��Ľڵ���Ϊ����
*/

#include <stdio.h>
#include <string.h>
#include <map>
#include <utility>
#include <algorithm>
using namespace std;

struct ufs_t{
    enum{UF_SIZE=10010};
    int father[UF_SIZE+1];
    int peak[UF_SIZE+1];

    void init(int n){for(int i=0;i<=n;++i)father[i]=i;}
    int find(int x){return father[x]==x?x:father[x]=find(father[x]);}

    //Ҫѡ��peak������Ϊ����peak��ͬѡ����Ž�С��
    void unite(int x,int y){
        x = find(x);
        y = find(y);
        if ( peak[y] < peak[x] || ( peak[y] == peak[x] && x < y ) ) father[y] = x;
        else father[x] = y;
    }
}UF;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

int N,M,Q;
pair<int,int> Conn[20000+10];
map<pair<int,int>,int > Map;
bool Flag[20000+10];

struct cmd_t{
    int cmd,a,b;
}Cmd[50000+10];

bool read(){
    if ( EOF == scanf("%d",&N) ) return false;

    for(int i=1;i<=N;++i) UF.peak[i] = getUnsigned();

    Map.clear();
    fill(Flag,Flag+M,false);
    M = getUnsigned();
    for(int i=0;i<M;++i){
        Conn[i].first = getUnsigned() + 1;
        Conn[i].second = getUnsigned() + 1;
        if ( Conn[i].first > Conn[i].second ) swap(Conn[i].first,Conn[i].second);
        Map.insert(make_pair(Conn[i],i));
    }

    Q = getUnsigned();
    char s[20];
    for(int i=0;i<Q;++i){
        scanf("%s",s);
        if ( 'd' == *s ){
            Cmd[i].cmd = 1;
            Cmd[i].a = getUnsigned() + 1;
            Cmd[i].b = getUnsigned() + 1;
            if ( Cmd[i].a > Cmd[i].b ) swap(Cmd[i].a,Cmd[i].b);
            Flag[Map[make_pair(Cmd[i].a,Cmd[i].b)]] = true;
        }else{
            Cmd[i].cmd = 2;
            Cmd[i].a = getUnsigned() + 1;
        }
    }

    return true;
}

int Ans[50000+10];
int main(){
    //freopen("1.txt","r",stdin);

    for(int kase=0;read();++kase){
        UF.init(N);

        //��������
        for(int i=0;i<M;++i)if(!Flag[i]){
            UF.unite(Conn[i].first,Conn[i].second);
        }

        //Ȼ������ִ��ָ��
        for(int i=Q-1;i>=0;--i){
            if ( 1 == Cmd[i].cmd ){
                UF.unite(Cmd[i].a,Cmd[i].b);
                Ans[i] = -2;
            }else{
                int t = UF.find(Cmd[i].a);
                Ans[i] = UF.peak[t] > UF.peak[Cmd[i].a] ? t - 1 : -1;
            }
        }

        //���
        if ( kase ) putchar('\n');
        for(int i=0;i<Q;++i)if(-2!=Ans[i]){
            printf("%d\n",Ans[i]);
        }

    }

    return 0;
}


