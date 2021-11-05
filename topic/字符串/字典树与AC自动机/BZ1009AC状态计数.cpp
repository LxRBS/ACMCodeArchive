#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

//Just as its name
int const SIZE = 1000;
//The count of all valid letters
int const ALPHA_SIZE = 10;
//The map from letters to ints
int L2I[256];
//To initialize L2I array, don't forget calling it!!!
void initL2I(){
    for(int i=0;i<ALPHA_SIZE;++i) L2I[i + '0'] = i;
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

//the following is about Matrix
typedef int ull;
typedef ull (*mat_ptr_t) [SIZE];

void buildMat(mat_ptr_t mat){
    for(int i=StartState;i<toUsed;++i){
        fill(mat[i],mat[i]+toUsed,0);

        if ( Flag[i] ){//it cannot go anywhere from final state but final state
            mat[i][i] = ALPHA_SIZE;
            continue;
        }

        for(int j=0;j<ALPHA_SIZE;++j){
            int state = Trie[i][j];
            ++mat[i][state];
        }
    }

    //to remove final states from transition matrix
    for(int i=toUsed-1;i>=StartState;--i){
        if ( !Flag[i] ) continue;

        //to remove row i
        for(int k=i+1;k<toUsed;++k){
            copy(mat[k],mat[k]+toUsed,mat[k-1]);
        }

        //to remove column i
        for(int k=StartState;k<toUsed;++k){
            copy(mat[k]+i+1,mat[k]+toUsed,mat[k]+i);
        }

        --toUsed;
    }
}

//multiplication of matrices with mod
void multiMat(ull a[SIZE][SIZE],ull b[SIZE][SIZE],ull c[SIZE][SIZE],ull mod){
    for(int i=1;i<toUsed;++i)for(int j=1;j<toUsed;++j){
        c[i][j] = 0;
        for(int k=1;k<toUsed;++k) c[i][j] = ( c[i][j] + a[i][k] * b[k][j] % mod ) % mod;
    }
}

//swap pointers to matrix
void swap(ull(*&a)[SIZE],ull(*&b)[SIZE]){
    ull(*t)[SIZE] = a;
    a = b;
    b = t;
}

ull Mat[SIZE][SIZE];
ull TM1[SIZE][SIZE],TM2[SIZE][SIZE];
//to calculate Mat^n, the return is the pointer to the result
mat_ptr_t powerMat(int n,ull mod){
    for(int i=1;i<toUsed;++i){
        fill(TM1[i],TM1[i]+toUsed,0);
        TM1[i][i] = 1;
    }

    ull(*a)[SIZE] = Mat;
    ull(*ans)[SIZE] = TM1;
    ull(*t)[SIZE] = TM2;
    while(n){
        if ( n & 1 ){
            multiMat(a,ans,t,mod);
            swap(ans,t);
        }

        multiMat(a,a,t,mod);
        swap(a,t);

        n >>= 1;
    }

    return ans;
}

int N,M,K;
char A[21];
int main(){
    initL2I();
    scanf("%d%d%d%s",&N,&M,&K,A);

    initTrie();
    insert(A);
    buildAC();
    buildMat(Mat);

    mat_ptr_t p = powerMat(N,K);

    int ret = 0;
    for(int i=StartState;i<toUsed;++i) ret = ( ret + p[StartState][i] ) % K;
    printf("%d\n",ret);

    return 0;
}

