#include <cstdio>
#include <cstring>
//字典树
struct node_t{
    bool flag;
    node_t* son[26];
}Node[2000000];
int toUsed = 1;

void insert(char const word[]){
    int k = 0,sn;
    node_t* loc = Node;
    while( word[k] ){
        sn = word[k] - 'a';
        if ( 0 == loc->son[sn] ){
            loc->son[sn] = Node + toUsed ++;
        }
        loc = loc -> son[sn];
        ++k;
    }
    loc->flag = true;
}

bool find(char const word[],int len=0){
    int k=0,sn;
    node_t* loc = Node;
    while( word[k] ){
        sn = word[k] - 'a';
        if ( 0 == loc->son[sn] )
            return false;
        loc = loc->son[sn];
        ++k;
        if ( len == k ) return loc->flag;
    }
    return loc->flag;
}

char Words[50001][50];
int main(){
    //建立字典树
    int k = 0;
    for(k=0;EOF!=scanf("%s",Words+k);++k){
        insert(Words[k]);
    }

    //查找，对每个单词
    for(int i=0;i<k;++i){
        int len = strlen(Words[i]);
        for(int j=1;j<len;++j){
            bool t = find(Words[i],j);
            if ( !t ) continue;

            t = find(Words[i]+j);
            if ( !t ) continue;

            printf("%s\n",Words[i]);
            break;
        }
    }

    return 0;
}