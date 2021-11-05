#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

//Just as its name
int const SIZE = 1000000;
//The count of all valid letters
int const ALPHA_SIZE = 128;
//The map from letters to ints
int L2I[256];
//To initialize L2I array, don't forget calling it!!!
void initL2I(){
    for(int i=0;i<ALPHA_SIZE;++i) L2I[i] = i;
}

//The transition matrix of DFA
int Trie[SIZE][ALPHA_SIZE];
int Flag[SIZE];//Flag[i] means the index of the current pattern
int Fail[SIZE];
int toUsed;

int StartState;
int ErrorState;

//to new a state
inline int _newState(){
    fill(Trie[toUsed],Trie[toUsed]+ALPHA_SIZE,0);
    Flag[toUsed] = 0;
    Fail[toUsed] = 0;
    return toUsed++;
}

//to insert a string into Trie
void insert(char const word[],int idx=1){
    int state = StartState;
    for(char const*p=word;*p;++p){
        int sn = L2I[(int)*p];
        if ( 0 == Trie[state][sn] ) Trie[state][sn] = _newState();
        state = Trie[state][sn];
    }
    Flag[state] = idx;
}

//it is to build fails in fact
void buildAC(){
    Fail[StartState] = StartState;

    queue<int> q;
    for(int i=0;i<ALPHA_SIZE;++i){
        int& state = Trie[StartState][i];
        if ( state ){
            Fail[state] = StartState;
            q.push(state);
        }else{
            state = StartState;
        }
    }

    while( !q.empty() ){
        int u = q.front();
        q.pop();

        for(int i=0;i<ALPHA_SIZE;++i){
            int& state = Trie[u][i];
            if ( state ){
                Fail[state] = Trie[Fail[u]][i];
                q.push(state);
            }else{
                state = Trie[Fail[u]][i];
            }
        }
    }
}

void initTrie(){
    toUsed = 0;
    ErrorState = _newState();
    StartState = _newState();
}

//this is basically find operation
//to find patterns that appears in the given target
int find(char const target[],bool ans[]){
    int state = StartState;
    for(char const*p=target;*p;++p){
        state = Trie[state][L2I[(int)*p]];
        int t = state;
        while( t != StartState ){
            ans[Flag[t]] = true;
            //Flag[t] = -1;//can't do it here because AC is used for many webs
            t = Fail[t];
        }
    }
    return 0;
}

int N;
char S[10001];
bool read(){
    if ( EOF == scanf("%d",&N) ) return false;

    initTrie();
    for(int i=1;i<=N;++i){
        scanf("%s",S);
        insert(S,i);
    }
    buildAC();

    return true;
}

char Output[3000];
bool Ans[501];
void proc(){
    int m;
    scanf("%d",&m);

    int total = 0;
    for(int i=1;i<=m;++i){
        scanf("%s",S);

        fill(Ans,Ans+501,false);
        find(S,Ans);
        int offset = 0;
        for(int j=1;j<=N;++j){
            if ( Ans[j] ){
                offset += sprintf(Output+offset," %d",j);
            }
        }
        if ( 0 == offset ) continue;

        ++total;
        printf("web %d:%s\n",i,Output);
    }

    printf("total: %d\n",total);
}

int main(){
    //freopen("1.txt","r",stdin);
    initL2I();
    while( read() ) proc();
    return 0;
}

