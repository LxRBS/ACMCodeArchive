/**
    给定1万个长度8以内的字符串
    再给定5万个询问，每次问是否为上述串的子串，
    问一共有多少个，且任意输出其中一个
    
    暴力法，把每个字符串的所有子串建立字典树，
    然后对每个询问直接在字典树上跑即可
*/
#include<bits/stdc++.h>
using namespace std;

//Just as its name
int const SIZE_OF_TRIE = 1051000;//TODO
//The count of all valid letters
int const ALPHA_SIZE = 37;//TODO
//The map from letters to ints
int L2I[256];
//To initialize L2I array, don't forget calling it!!!
void initL2I(){
    for(int i=0;i<26;++i) L2I[i + 'a'] = i; //TODO
    L2I['.'] = 26;
    for(int i=0;i<=9;++i) L2I[i+'0'] = 27+i;
}

//The transition matrix of DFA
int Trie[SIZE_OF_TRIE][ALPHA_SIZE];
unordered_set<int> Flag[SIZE_OF_TRIE];
int SCnt;

int StartState;
int ErrorState;

//to new a state
inline int _newState(){
    fill(Trie[SCnt],Trie[SCnt]+ALPHA_SIZE,0);
    Flag[SCnt].clear();
    return SCnt++;
}

//to insert a string into Trie
void insert(char const word[],int left,int right,int idx=1){
    int state = StartState;
    for(int i=left;i<=right;++i){
        int sn = L2I[(int)word[i]];
        if ( 0 == Trie[state][sn] ) Trie[state][sn] = _newState();
        state = Trie[state][sn];
    }
    if(Flag[state].find(idx)==Flag[state].end()){
        Flag[state].insert(idx);
    }
}

void initTrie(){
    SCnt = 0;
    ErrorState = _newState();
    StartState = _newState();
}

//this is basically find operation
//ans记录匹配的单词的具体编号
int find(char const target[]){
    int state = StartState;
    for(char const*p=target;*p;++p){
        state = Trie[state][L2I[(int)*p]];
        if(state==ErrorState) return ErrorState;
    }
    return state;
}

char Word[10010][10];
int main(){
    //freopen("1.txt","r",stdin);
    initL2I();
    initTrie();

    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;++i){
        scanf("%s",Word[i]);
        int m = strlen(Word[i]);
        for(int start=0;start<m;++start){
            for(int end=start;end<m;++end){
                insert(Word[i],start,end,i);
            }
        }
    }

    int q;
    scanf("%d",&q);
    while(q--){
        char s[12];
        scanf("%s",s);
        int ans = find(s);
        if(ans==ErrorState||Flag[ans].empty()){
            printf("0 -\n");
        }else{
            printf("%d %s\n",Flag[ans].size(),Word[*Flag[ans].begin()]);
        }
    }
    return 0;
}

