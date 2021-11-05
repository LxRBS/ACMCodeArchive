#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

//Just as its name
int const SIZE_OF_TRIE = 10000*10;//TODO
//The count of all valid letters
int const ALPHA_SIZE = 52;//TODO
//The map from letters to ints
int L2I[256];
//To initialize L2I array, don't forget calling it!!!
void initL2I(){
    for(int i=0;i<26;++i) L2I['a'+i] = i;
    for(int i=0;i<26;++i) L2I['A'+i] = i + 26;
}

//The transition matrix of DFA
int Trie[SIZE_OF_TRIE][ALPHA_SIZE];
int Flag[SIZE_OF_TRIE];
int SCnt;

int StartState;
int ErrorState;

//to new a state
inline int _newState(){
    fill(Trie[SCnt],Trie[SCnt]+ALPHA_SIZE,0);
    Flag[SCnt] = 0;
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
    for(char const*p=word;*p;++p){
        int sn = L2I[(int)*p];
        if ( 0 == Trie[state][sn] ) Trie[state][sn] = _newState();
        state = Trie[state][sn];
    }
    ++Flag[state];
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
char P[10001];
void read(){
    initTrie();

    scanf("%d",&N);
    for(int i=0;i<N;++i){
        scanf("%s",P);

        int length = strlen(P);
        if ( length > 3 ) sort(P+1,P+length-1);
        insert(P);
    }
}
int M;
char T[1001];
int proc(){
    scanf("%d",&M);gets(P);
    for(int i=0;i<M;++i){
        gets(P);
        int ret = 1;
        int offset = 0;
        while( EOF != sscanf(P+offset,"%s",T) ){
            int length = strlen(T);
            offset += length;
            while( ' ' == P[offset] ) ++offset;

            if ( ret ){
                if ( length > 3 )sort(T+1,T+length-1);
                ret *= find(T);
            }
        }
        printf("%d\n",ret);
    }
}
int main(){
    //freopen("1.txt","r",stdin);
    initL2I();

    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        read();
        printf("Case %d:\n",kase);
        proc();
    }
    return 0;
}
