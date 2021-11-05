/*
    两个字符串的集合A、B，有空格或者空行
    问A连接B的集合中一共有多少个元素
*/
#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;

//Just as its name
int const SIZE_OF_TRIE = 1000000;//TODO
//The count of all valid letters
int const ALPHA_SIZE = 27;//TODO
//The map from letters to ints
int L2I[256];
//To initialize L2I array, don't forget calling it!!!
void initL2I(){
    for(int i=0;i<26;++i) L2I[i + 'a'] = i;//TODO
    L2I[' '] = 26;
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

//to insert a string into ，返回状态
int insert(char const word[],int startState){
    int state = startState;
    for(char const*p=word;*p!='\n';++p){
        int sn = L2I[(int)*p];
        if ( 0 == Trie[state][sn] ) Trie[state][sn] = _newState();
        state = Trie[state][sn];
    }
    //Flag[state] = idx;
    return state;
}

void initTrie(){
    SCnt = 0;
    ErrorState = _newState();
    StartState = _newState();
}

char A[20];
int S[1550];
int main(){
    //freopen("1.txt","r",stdin);
    initL2I();
    int nofkase,n,m;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        initTrie();
        scanf("%d%d",&n,&m);
        fgets(A,20,stdin);
        for(int i=0;i<n;++i){
            fgets(A,20,stdin);
            S[i] = insert(A,StartState);
        }

        int s,ans = 0;
        for(int i=0;i<m;++i){
            fgets(A,20,stdin);
            for(int j=0;j<n;++j){
                if ( 0 == Flag[s = insert(A,S[j])] ){
                    ++ans;
                    Flag[s] = 1;
                }
            }
        }

        printf("Case %d: %d\n",kase,ans);
    }
    return 0;
}
