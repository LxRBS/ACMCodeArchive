//典型的文法规则，因为题目都已经给出了CFG的规则
//使用LL(1)文法，在匹配的时候使用语义
//也可以使用LR分析，不过LR分析的代码量应该大的多
#include <cstdio>
#include <cctype>
#include <set>
#include <string>
#include <algorithm>
using namespace std;

string const LAMBDA("lambda");
string const LEFTP("(");
string const RIGHTP(")");
string const JING("#");

int const SIZE = 10000010;
char Input[SIZE];
char* CurPtr;
string CurToken;

string getToken(){
    while( '(' != *CurPtr && ')' != *CurPtr && '-' != *CurPtr && !isalpha(*CurPtr) && '\n' != *CurPtr ) ++CurPtr;

    if ( '(' == *CurPtr ){
        ++CurPtr;
        return LEFTP;
    }

    if ( ')' == *CurPtr ){
        ++CurPtr;
        return RIGHTP;
    }

    if ( 'l' == *CurPtr && 'a' == *(CurPtr+1) && 'm' == *(CurPtr+2) && 'b' == *(CurPtr+3) && 'd' == *(CurPtr+4) && 'a' == *(CurPtr+5) && ( '-' != *(CurPtr+6) && !isalpha(*(CurPtr+6)) ) ){
        CurPtr += 6;
        return LAMBDA;
    }

    if ( '-' == *(CurPtr) || isalpha(*(CurPtr)) ){
        int k = 1;
        while( '-' == *(CurPtr+k) || isalpha(*(CurPtr+k)) ) ++k;

        char *tmp = CurPtr;
        return string(tmp,CurPtr+=k);
    }

    if ( '\n' == *CurPtr ) return JING;
}

void E(set<string>&);
void A(set<string>&ret){
    if ( LAMBDA == CurToken ){
        getToken();
        string s = getToken();
        getToken();
        CurToken = getToken();E(ret);
        ret.erase(s);
        CurToken = getToken();
    }else{
        E(ret);
        E(ret);
        CurToken = getToken();
    }
}

void E(set<string>&ret){
    if ( LEFTP == CurToken ){
        CurToken = getToken(); A(ret);
    }else{
        ret.insert(CurToken); CurToken = getToken();
    }
}

set<string> Ans;
int main(){
    //freopen("1.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);fgets(Input,SIZE,stdin);
    for(int kase=1;kase<=nofkase;++kase){
        fgets(Input,SIZE,stdin);

        CurPtr = Input;
        Ans.clear();
        CurToken = getToken();
        E(Ans);

        printf("Case #%d:",kase);
        for(set<string>::iterator it=Ans.begin();it!=Ans.end();++it)printf(" %s",it->c_str());
        if (Ans.empty())putchar(' ');
        putchar('\n');
    }
    return 0;
}
