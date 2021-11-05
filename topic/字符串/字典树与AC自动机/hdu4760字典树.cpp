#include <cstdio>
#include <set>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

//Just as its name
int const SIZE_OF_TRIE = 500000;//TODO
//The count of all valid letters
int const ALPHA_SIZE = 2;//TODO
//The map from letters to ints
int L2I[256];
//To initialize L2I array, don't forget calling it!!!
void initL2I(){
    L2I['0'] = 0;
    L2I['1'] = 1;//TODO
}

//The transition matrix of DFA
int Trie[SIZE_OF_TRIE][ALPHA_SIZE];
//int Flag[SIZE_OF_TRIE];
set<int> Policy[SIZE_OF_TRIE];
int SCnt;

int StartState;
int ErrorState;

//to new a state
inline int _newState(){
    fill(Trie[SCnt],Trie[SCnt]+ALPHA_SIZE,0);
    //Flag[SCnt] = 0;
    return SCnt++;
}



//to insert a string into Trie
void insert(char const word[],int idx=1){
    int state = StartState;
    for(char const*p=word;*p;++p){
        int sn = L2I[(int)*p];
        if ( 0 == Trie[state][sn] ) Trie[state][sn] = _newState();
        state = Trie[state][sn];
    }
    Policy[state].insert(idx);
}

vector<int> Vec[4];
vector<int>& find(char const word[],int offset){
    int cur = offset | 0;
    int next = offset | 1;
    Vec[cur].clear();Vec[next].clear();

    int state = StartState;
    if ( !Policy[state].empty() ) Vec[cur].assign(Policy[state].begin(),Policy[state].end());

    for(char const*p=word;*p;++p){
        int sn = L2I[(int)*p];
        int nextState = Trie[state][sn];
        if ( !Policy[nextState].empty() ){
            set_union(
                Policy[nextState].begin(),Policy[nextState].end(),
                Vec[cur].begin(),Vec[cur].end(),
                back_inserter(Vec[next])
            );
            cur ^= 1;
            next ^= 1;
            Vec[next].clear();
        }

        if ( 0 == nextState ) return Vec[cur];
        state = Trie[state][sn];
    }

    set_union(Policy[state].begin(),Policy[state].end(),Vec[cur].begin(),Vec[cur].end(),back_inserter(Vec[next]));
    return Vec[next];
}

void initTrie(){
    SCnt = 0;
    ErrorState = _newState();
    StartState = _newState();
}

void tr(int a,int b,int c,int d,char ip[]){
    for(int i=7;i>=0;--i){
        ip[i] = ( a & 1 ) + '0';
        a >>= 1;
    }
    for(int i=15;i>=8;--i){
        ip[i] = ( b & 1 ) + '0';
        b >>= 1;
    }
    for(int i=23;i>=16;--i){
        ip[i] = ( c & 1 ) + '0';
        c >>= 1;
    }
    for(int i=31;i>=24;--i){
        ip[i] = ( d & 1 ) + '0';
        d >>= 1;
    }
}

bool Enabled[1025] = {false};
bool read(){
    char cmd[3],ip[50] = {'\0'};
    int id,n,a,b,c,d;
    if ( EOF == scanf("%s%d",cmd,&id) ) return false;

    if ( 'D' == *cmd ){
        Enabled[id] = false;
        return true;
    }

    if ( 'F' ==  *cmd ){
        scanf(".%d.%d.%d",&b,&c,&d);
        tr(id,b,c,d,ip);
        vector<int>& sa = find(ip,0);

        scanf("%d.%d.%d.%d",&a,&b,&c,&d);
        tr(a,b,c,d,ip);
        vector<int>& sb = find(ip,2);

        vector<int> jia;
        set_intersection(sa.begin(),sa.end(),sb.begin(),sb.end(),back_inserter(jia));

        bool flag = false;
        for(vector<int>::iterator it=jia.begin();it!=jia.end();++it){
            if ( Enabled[*it] ){
                flag = true;
                break;
            }
        }
        printf(flag?"F\n":"D\n");

        return true;
    }


    Enabled[id] = true;
    scanf("%d",&n);

    int mask;
    for(int i=0;i<n;++i){
        scanf("%d.%d.%d.%d/%d",&a,&b,&c,&d,&mask);
        tr(a,b,c,d,ip);
        ip[mask] = '\0';
        insert(ip,id);
    }

    return true;
}

int main(){
    //freopen("1.txt","r",stdin);
    initL2I();
    initTrie();
    while( read() ) ;
    return 0;
}

