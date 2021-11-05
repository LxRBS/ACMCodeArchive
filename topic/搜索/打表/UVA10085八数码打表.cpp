/*
    给定一个八数码，问距离最远的八数码是什么
    并求出路径
    打表
*/
#include <stdio.h>
#include <sstream>
#include <queue>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

int const FAC[] = {
    1,1,2,6,24,120,720,5040,40320,362880
};

//康托展开
int Cantor(string const& a){
    int num,ret = 1;
    for(int i=0;i<9;++i){
        num = 0;
        for(int j=i+1;j<9;++j){
            if ( a[j] < a[i] ) ++num;
        }
        ret += num * FAC[9-i-1];
    }
    return ret;
}

//下左右上
char const CH[] = "DLRU";
int const P2Move[9][4] = {
    {3,-1,1,-1},
    {4,0,2,-1},
    {5,1,-1,-1},
    {6,-1,4,0},
    {7,3,5,1},
    {8,4,-1,2},
    {-1,-1,7,3},
    {-1,6,8,4},
    {-1,7,-1,5}
};
bool H[9][362880];//hash状态
struct _t{
    int status;
    string s;
    string cmd;
    _t(int a=0,string const&b="",string const&c=""):status(a),s(b),cmd(c){}
};

string InitialState[] = {
    "012345678","102345678","120345678",
    "123045678","123405678","123450678",
    "123456078","123456708","123456780"
};

string FarestCmd[9],FarestStatus[9];

int getPosOf0(string const&s){
    for(unsigned i=0,n=s.length();i<n;++i)if('0'==s[i])return i;
    return -1;
}

void bfs(int n){
    int state = Cantor(InitialState[n]);
    H[n][state] = true;

    queue<_t> q;
    q.push(_t(state,InitialState[n]));

    int k,m;
    while(!q.empty()){
        _t u = q.front();
        q.pop();

        for(int i=0;i<4;++i)if(-1!=(m=P2Move[k=getPosOf0(u.s)][i])){
            //移动
            swap(u.s[m],u.s[k]);
            if ( !H[n][state=Cantor(u.s)] ){
                H[n][state] = true;
                q.push(_t(state,u.s,u.cmd+CH[i]));
            }
            //还原
            swap(u.s[m],u.s[k]);
        }

        //记录最远
        FarestCmd[n] = u.cmd;
        FarestStatus[n] = u.s;
    }
}

char getChar(){
	char ch = getchar();
	while( ch < '0' || ch > 'z' || ( '9' < ch && ch < 'a' ) || ( 'Z' < ch && ch < 'a' ) ) ch = getchar();
	return ch;
}

char Map[256];
int main(){
    //freopen("1.txt","r",stdin);
    for(int i=0;i<9;++i) bfs(i);

    int nofkase;
    scanf("%d",&nofkase);
    string s(9,' ');
    for(int kase=1;kase<=nofkase;++kase){
        for(int i=0;i<9;++i)s[i] = getChar();
        int k = getPosOf0(s);
        //映射
        for(int i=0;i<9;++i)Map[InitialState[k][i]]=s[i];
        //输出
        printf("Puzzle #%d\n",kase);
        for(int i=0;i<9;++i){
            printf("%c",Map[FarestStatus[k][i]]);
            if ( 2 == i % 3 ) printf("\n");
            else printf(" ");
        }
        printf("%s\n",FarestCmd[k].c_str());
    }

    return 0;
}
