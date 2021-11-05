#include <cstdio>
#include <algorithm>
using namespace std;

//Just as its name
int const SIZE_OF_TRIE = 50000*30;//TODO
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
int Trie[SIZE_OF_TRIE][ALPHA_SIZE];
int Flag[SIZE_OF_TRIE];
int SCnt;

int Depth[SIZE_OF_TRIE];
int Count[SIZE_OF_TRIE];

int StartState;
int ErrorState;

//to new a state
inline int _newState(){
    fill(Trie[SCnt],Trie[SCnt]+ALPHA_SIZE,0);
    Flag[SCnt] = Depth[SCnt] = Count[SCnt] = 0;
    return SCnt++;
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
    int depth = 0;
    ++Count[state];

    for(char const*p=word;*p;++p){
        int sn = L2I[(int)*p];
        if ( 0 == Trie[state][sn] ) Trie[state][sn] = _newState();
        state = Trie[state][sn];

        Depth[state] = ++depth;
        ++Count[state];
    }
    Flag[state] = idx;
}

//to find whether a given string exists in Trie
int find(char const word[]){
    return Flag[_run(word)];
}

void initTrie(){
    SCnt = 0;
    ErrorState = _newState();
    StartState = _newState();
}

int N;
char P[55];
void read(){
    initTrie();

    scanf("%d",&N);
    for(int i=0;i<N;++i){
        scanf("%s",P);
        insert(P);
    }
}
int proc(){
   int ret = 0;
   for(int i=StartState;i<SCnt;++i){
       int t = Count[i] * Depth[i];
       if ( ret < t ) ret = t;
   }
   return ret;
}
int main(){
    //freopen("1.txt","r",stdin);
    initL2I();

    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        read();
        printf("Case %d: %d\n",kase,proc());
    }
    return 0;
}

