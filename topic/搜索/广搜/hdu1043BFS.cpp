//八数码问题，广搜以后打表
#include <cstdio>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;

int const SIZE_OF_FAC = 9;
int const FAC[] = {
    1,1,2,6,24,120,720,5040,40320,362880
};

//康托展开
int Cantor(int const a[]){
    int num,ret = 1;
    for(int i=0;i<SIZE_OF_FAC;++i){
        num = 0;
        for(int j=i+1;j<SIZE_OF_FAC;++j){
            if ( a[j] < a[i] ) ++num;
        }
        ret += num * FAC[SIZE_OF_FAC-i-1];
    }
    return ret;
}

struct _t{
    int a[9];
    int pos;
    int code;
    _t(int const aa[],int pp,int ccode):pos(pp),code(ccode){copy(aa,aa+9,a);}
};
int const DR[] = {-1,1,0,0};
int const DC[] = {0,0,-1,1};
char const DL[] = "durl";
int S[] = {1,2,3,4,5,6,7,8,0};
int const TARGET = Cantor(S);
string Ans[362882];
bool Flag[362882];
queue<_t> q;

void bfs(){
    fill(Flag,Flag+362882,false);
    
    q.push(_t(S,8,TARGET));
    Flag[TARGET] = true;

    while( !q.empty() ){
        _t u = q.front();
        q.pop();

        for(int i=0;i<4;++i){
            int x = u.pos / 3;
            int y = u.pos % 3;
            int dx = x + DR[i];
            int dy = y + DC[i];

            if ( 0 <= dx && dx < 3 && 0 <= dy && dy < 3 ){
                int dpos = dx * 3 + dy;
                swap(u.a[u.pos],u.a[dpos]);
                int code = Cantor(u.a);

                if ( !Flag[code] ){
                    Flag[code] = true;
                    Ans[code] = DL[i] + Ans[u.code];
                    q.push(_t(u.a,dpos,code));
                }
                //还原
                swap(u.a[u.pos],u.a[dpos]);
            }
        }
    }
}

char A[1000];
int main(){
    bfs();

    while( fgets(A,999,stdin) ){
        //处理输入
        int k = 0;
        for(char*p=A;*p!='\n';++p){
            if ( 'x' == *p ) S[k++] = 0;
            else if ( '1' <= *p && *p <= '8' ) S[k++] = *p - '0';
        }

        int code = Cantor(S);
        if ( TARGET == code ){
            printf("\n");
        }else if ( "" == Ans[code] ){//无解
            printf("unsolvable\n");
        }else{
            printf("%s\n",Ans[code].c_str());
        }

    }
    return 0;
}
