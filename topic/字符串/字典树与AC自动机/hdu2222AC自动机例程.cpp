#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

//Just as its name
int const SIZE = 5000000;
//The count of all valid letters
int const ALPHA_SIZE = 26;
//The map from letters to ints
int L2I[256];
//To initialize L2I array, don't forget calling it!!!
void initL2I(){
    for(int i=0;i<ALPHA_SIZE;++i) L2I[i + 'a'] = i;
}

//The transition matrix of DFA
int Trie[SIZE][ALPHA_SIZE];
int Flag[SIZE];//Flag[i] means the count of the current pattern
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
    ++Flag[state];
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
//to return the number of patterns found in the given target
int find(char const target[]){
    int state = StartState;
    int ans = 0;
    for(char const*p=target;*p;++p){
        state = Trie[state][L2I[(int)*p]];
        int t = state;
        while( t != StartState && Flag[t] != -1 ){
            ans += Flag[t];
            Flag[t] = -1;  //the accessed fail chain is never access again
            t = Fail[t];
        }
    }
    return ans;
}

char S[1000001];
void read(){
    int n;
    scanf("%d",&n);

    initTrie();
    while(n--){
        scanf("%s",S);
        insert(S);
    }
    buildAC();
}

void proc(){
    scanf("%s",S);
    printf("%d\n",find(S));
}

int main(){
    //freopen("1.txt","r",stdin);
    initL2I();
    int kase;
    scanf("%d",&kase);
    while( kase-- ){
        read();
        proc();
    }
    return 0;
}



