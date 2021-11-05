#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

int const MOD = 100000LL;

//Just as its name
int const SIZE = 105;
//The count of all valid letters
int const ALPHA_SIZE = 4;
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
int Flag[SIZE];//Flag[i] means the index of the current pattern
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

        //it is important because we won't track the fail chain as generally as what we do in normal matching problem
        if ( Flag[Fail[u]] ) Flag[u] = 1;

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
typedef long long llt;
typedef llt (*mat_ptr_t) [SIZE];

void buildMat(mat_ptr_t mat){
    for(int i=StartState;i<toUsed;++i){
        fill(mat[i],mat[i]+toUsed,0LL);

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
void multiMat(llt a[SIZE][SIZE],llt b[SIZE][SIZE],llt c[SIZE][SIZE]){
    for(int i=1;i<toUsed;++i)for(int j=1;j<toUsed;++j){
        c[i][j] = 0LL;
        for(int k=1;k<toUsed;++k) c[i][j] += a[i][k] * b[k][j];
        c[i][j] %= MOD;
    }
}

//swap pointers to matrix
void swap(llt(*&a)[SIZE],llt(*&b)[SIZE]){
    llt(*t)[SIZE] = a;
    a = b;
    b = t;
}

llt Mat[SIZE][SIZE];
llt TM1[SIZE][SIZE],TM2[SIZE][SIZE];
//to calculate Mat^n, the return is the pointer to the result
mat_ptr_t powerMat(int n){
    for(int i=1;i<toUsed;++i){
        fill(TM1[i],TM1[i]+toUsed,0LL);
        TM1[i][i] = 1LL;
    }

    llt(*a)[SIZE] = Mat;
    llt(*ans)[SIZE] = TM1;
    llt(*t)[SIZE] = TM2;
    while(n){
        if ( n & 1 ){
            multiMat(a,ans,t);
            swap(ans,t);
        }

        multiMat(a,a,t);
        swap(a,t);

        n >>= 1;
    }

    return ans;
}

int N,M;
char S[12];
bool read(){
    if ( EOF == scanf("%d%d",&M,&N) ) return false;

    initTrie();
    for(int i=1;i<=M;++i){
        scanf("%s",S);
        insert(S);
    }
    buildAC();
    buildMat(Mat);

    return true;
}

void proc(){
    mat_ptr_t p = powerMat(N);
    int ret = 0;
    for(int i=StartState;i<toUsed;++i){
        ret += p[StartState][i];
    }
    printf("%d\n",ret%MOD);
}

int main(){
    //freopen("1.txt","r",stdin);
    initL2I();
    while( read() ) proc();
    return 0;
}

