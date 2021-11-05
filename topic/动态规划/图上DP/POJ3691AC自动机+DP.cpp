#include <cstdio>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

//Just as its name
int const SIZE = 5000;//TODO
//The count of all valid letters
int const ALPHA_SIZE = 4;//TODO
//The map from letters to ints
int L2I[256];
//To initialize L2I array, don't forget calling it!!!
void initL2I(){
    L2I['A'] = 0;
    L2I['C'] = 1;
    L2I['G'] = 2;
    L2I['T'] = 3;
}

//The transition matrix of DFA
int Trie[SIZE][ALPHA_SIZE];
int Flag[SIZE];
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
                if ( Flag[Fail[state]] ) Flag[state] = 1;
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

int N;
char S[1010];
bool read(){
    scanf("%d",&N);
    if ( 0 == N ) return false;

    initTrie();
    for(int i=0;i<N;++i){
        scanf("%s",S);
        insert(S);
    }

    buildAC();
    scanf("%s",S);
    return true;
}

int const INF = 1000000000;
int D[1010][SIZE];
char const CH[] = "ACGT";
int proc(){
    int n = strlen(S);

    for(int i=0;i<=n;++i) fill(D[i],D[i]+toUsed,INF);
    D[0][StartState] = 0;

    for(int i=1;i<=n;++i){
        for(int state=StartState;state<toUsed;++state){
            if ( INF == D[i-1][state] ) continue;

            for(int j=0;j<ALPHA_SIZE;++j){
                int nextState = Trie[state][j];
                if ( Flag[nextState] ) continue;

                int t = D[i-1][state] + ( CH[j] != S[i-1] ? 1 : 0 );
                if ( t < D[i][nextState] ) D[i][nextState] = t;
            }
        }
    }

    int ret = INF;
    for(int state=StartState;state<toUsed;++state){
        if ( !Flag[state] && D[n][state] < ret ) ret = D[n][state];
    }

    return ret == INF ? -1 : ret;
}

int main(){
    //freopen("1.txt","r",stdin);
    initL2I();
    for(int kase=1;read();++kase){
        printf("Case %d: %d\n",kase,proc());
    }
    return 0;
}

