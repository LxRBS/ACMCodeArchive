#include <cstdio>
#include <algorithm>
using namespace std;

//Just as its name
int const SIZE = 1000000;
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
int Flag[SIZE];
int toUsed;

int StartState;
int ErrorState;

//to new a state
inline int _newState(){
    fill(Trie[toUsed],Trie[toUsed]+ALPHA_SIZE,0);
    Flag[toUsed] = false;
    return toUsed++;
}

//run DFA by a string
int _run(char const word[]){
    int state = StartState;
    for(char const*p=word;*p;++p){
        int sn = L2I[(int)*p];
        state = Trie[state][sn];
        if ( ErrorState == state ) return ErrorState;
    }
    return state;
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

//to find whether a given string exists in Trie
int find(char const word[]){
    return Flag[_run(word)];
}

void initTrie(){
    toUsed = 0;
    ErrorState = _newState();
    StartState = _newState();
}

char S[30],SS[12];
char Dic[100001][12] = {"eh"};
void read(){
    initTrie();

    int k = 0;
    while(1){
        gets(S);
        if ( '\0' == *S ) return;

        sscanf(S,"%s%s",Dic[++k],SS);
        insert(SS,k);
    }
}

void proc(){
    while( gets(S) ){
        printf("%s\n",Dic[find(S)]);
    }
}

int main(){
    //freopen("1.txt","r",stdin);
    initL2I();
    read();
    proc();
    return 0;
}

