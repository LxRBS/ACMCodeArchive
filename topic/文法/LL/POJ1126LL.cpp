//Grammar
//S ::= p - z
//S ::= NS
//S ::= CSS | DSS | ESS | ISS
#include <cstdio>

using namespace std;

char S[300];
int Index;

bool match(char const ch){
    return ch == S[Index++];
}

bool parseS(){
    char ch = S[Index];
    if ( 'p' <= ch && ch <= 'z' ) return match(ch);
    switch( ch ){
    case 'N':return match('N') && parseS();
    case 'C':
    case 'D':
    case 'E':
    case 'I':return match(ch) && parseS() && parseS();
    default:return false;
    }
    return false;
}

int main()
{
    //freopen("1.txt","r",stdin);
    while( gets(S) ){
        Index = 0;
        printf( parseS() && '\0' == S[Index] ? "YES\n" : "NO\n" );
    }
    return 0;
}

