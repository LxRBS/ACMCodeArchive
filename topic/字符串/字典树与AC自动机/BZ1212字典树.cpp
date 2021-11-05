#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

//Just as its name
int const SIZE_OF_TRIE = 20000;//TODO
//The count of all valid letters
int const ALPHA_SIZE = 26;//TODO
//The map from letters to ints
int L2I[256];
//To initialize L2I array, don't forget calling it!!!
void initL2I(){
    for(int i=0;i<ALPHA_SIZE;++i) L2I[i + 'a'] = i;//TODO
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

void initTrie(){
    SCnt = 0;
    ErrorState = _newState();
    StartState = _newState();
}

int N,M;
char S[1000010];
int MaxLen;

typedef vector<int> vit;
int run(int from,vit&v){
    v.clear();
    int state = StartState;
    for(int i=from,j=0;S[i]&&j<MaxLen;++i,++j){
        state = Trie[state][L2I[S[i]]];
        if ( Flag[state] ) v.push_back(Flag[state]);
    }
    return 0;
}

void read(){
    initTrie();

    scanf("%d%d",&N,&M);

    MaxLen = -1;
    for(int i=0;i<N;++i){
        scanf("%s",S);
        int len = strlen(S);
        insert(S,len);

        if ( MaxLen < len ) MaxLen = len;
    }
}

bool D[1000010];
vit Vec;
int proc(){
    int n = strlen(S);
    fill(D,D+n+1,false);
    D[0] = true;

    int ret = 0;
    int t;
    for(int i=0;i<n;++i){
        if ( !D[i] ) continue;

        run(i,Vec);
        for(vit::const_iterator it=Vec.begin();it!=Vec.end();++it){
            D[t=i+*it] = true;
            if ( ret < t ) ret = t;
        }
    }
    return ret;
}

int main(){
    //freopen("1.txt","r",stdin);
    initL2I();
    read();
    for(int i=0;i<M;++i){
        scanf("%s",S);
        printf("%d\n",proc());
    }
    return 0;
}

