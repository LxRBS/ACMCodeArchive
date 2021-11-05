#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

//Just as its name
int const SIZE_OF_TRIE = 1000000;//TODO
//The count of all valid letters
int const ALPHA_SIZE = 26;//TODO
//The map from letters to ints
int L2I[256];
//To initialize L2I array, don't forget calling it!!!
void initL2I(){
    for(int i=0;i<ALPHA_SIZE;++i) L2I[i + 'a'] = i; //TODO
}

//The transition matrix of DFA
int Trie[SIZE_OF_TRIE][ALPHA_SIZE];
int Flag[SIZE_OF_TRIE];
int Fail[SIZE_OF_TRIE];
int SCnt;

int StartState;
int ErrorState;

//to new a state
inline int _newState(){
    fill(Trie[SCnt],Trie[SCnt]+ALPHA_SIZE,0);
    Flag[SCnt] = 0;
    Fail[SCnt] = 0;
    return SCnt++;
}

//to insert a string into Trie
void insert(char const word[],int& idx){
    int state = StartState;
    for(char const*p=word;*p;++p){
        int sn = L2I[(int)*p];
        if ( 0 == Trie[state][sn] ) Trie[state][sn] = _newState();
        state = Trie[state][sn];
    }
    //There is possible a string appeared previously
    if ( Flag[state] ) idx = Flag[state];
    else Flag[state] = idx;
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
    SCnt = 0;
    ErrorState = _newState();
    StartState = _newState();
}

int Ans[501];
void search(char const word[]){
    int state = StartState;
    char const *p = word;
    while( *p ){
        state = Trie[state][L2I[*p++]];
        int t = state;
        while( t != StartState ){
            ++Ans[Flag[t]];
            t = Fail[t];
        }
    }
}

int N;
char T[1000001];
char P[501][501];
int Map[501];
void read(){
    initTrie();

    scanf("%d",&N);
    scanf("%s",T);

    fill(Map+1,Map+N+1,0);
    for(int i=1;i<=N;++i){
        scanf("%s",P[i]);
        Map[i] = i;
        insert(P[i],Map[i]);
    }
    buildAC();
}


int main(){
    //freopen("1.txt","r",stdin);
    initL2I();

    int nofkase;
    scanf("%d",&nofkase);

    for(int kase=1;kase<=nofkase;++kase){
        read();

        fill(Ans+1,Ans+N+1,0);
        search(T);

        printf("Case %d:\n",kase);
        for(int i=1;i<=N;++i)printf("%d\n",Ans[Map[i]]);
    }
}


