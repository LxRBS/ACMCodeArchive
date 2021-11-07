/**
   给定一个数字串，10万位
   将其拆分成若干，要求最大值减去最小值最小
   深搜剪枝，n位n位的进行划分
   对每一个当前位置有两种可能：n位和n+1位
   配合剪枝，速度很快
*/
#include <bits/stdc++.h>
using namespace std;

int const SIZE = 100010;
char Input[SIZE];
int N;
int A[SIZE];
int Cnt0[SIZE], Cnt1[SIZE], Cnt9[SIZE];//1的数量和0的数量和9

int Ans; //总答案
int OnceAns;//当前这一次的答案
struct _t{
    int index;//起始位置
    int cnt;  //数量
}Maxx,Minn,OriginMaxx,OriginMinn;

//从index开始的cnt位是否为新的最大值，如果是还进行更新，返回true，否则不更新、返回false
_t updateNewMax(int index,int cnt,_t maxx){
    if(maxx.index==-1){//如果原来没有最大值，显然大
        maxx.index = index;
        maxx.cnt = cnt;
        return maxx;
    }
    if(cnt>maxx.cnt){//如果位数大，显然大
        maxx.index = index;
        maxx.cnt = cnt;
        return maxx;
    }
    if(cnt<maxx.cnt){
        maxx.index = -1;
        return maxx;
    }
    for(int i=index,j=maxx.index,k=0;k<cnt;++i,++j,++k){
        if(A[i]>A[j]){//显然大
            maxx.index = index;
            maxx.cnt = cnt;
            return maxx;
        }
        if(A[i]<A[j]){//显然小
            maxx.index = -1;
            return maxx;
        }
    }

    //最大值倾向于往后
    maxx.index = index;
    maxx.cnt = cnt;
    return maxx;
}
_t updateNewMin(int index,int cnt,_t minn){
    if(minn.index==-1){//如果原来没有最小值，显然小
        minn.index = index;
        minn.cnt = cnt;
        return minn;
    }
    if(cnt<minn.cnt){//如果位数小，显然小
        minn.index = index;
        minn.cnt = cnt;
        return minn;
    }
    if(cnt>minn.cnt){
        minn.index = -1;
        return minn;
    }
    for(int i=index,j=minn.index,k=0;k<cnt;++i,++j,++k){
        if(A[i]<A[j]){//显然小
            minn.index = index;
            minn.cnt = cnt;
            return minn;
        }
        if(A[i]>A[j]){//显然大
            minn.index = -1;
            return minn;
        }
    }
    minn.index = -1;
    return minn;
}

inline int ABS(int n){return n>=0?n:-n;}

bool cha(_t const&maxx,_t const&minn,int&ret){
    int icnt = maxx.cnt, jcnt = minn.cnt;
    int idx = maxx.index, jdx = minn.index;

    ret = 0;
    if(icnt>jcnt){//最多只多一位
        ret = A[idx] * 10 + A[idx+1] - A[jdx];
        if(ret > Ans){//如果比当前的总答案大，不用算了
            return false;
        }
        idx += 2, ++jdx, icnt-=2, --jcnt;
        if(icnt!=jcnt){
            int xx=6;
            throw runtime_error("XXXXXXXXXXXXXX");
        }
    }
    for(int i=idx,j=jdx,k=0;k<icnt;++i,++j,++k){
        ret = ret * 10 + A[i] - A[j];
        if(ret>=Ans) return false;
    }
    return ret < Ans;
}

//一位一位搜
void dfs_1(int depth,_t maxx,_t minn){
    //printf("%d\n",depth);
    if(depth==N){//到底了
        if((-1==Ans || OnceAns<Ans)&&-1!=OnceAns){
            Ans = OnceAns;
        }
        return;
    }

    //先搜一位，这是必须的
    _t tmaxx = updateNewMax(depth,1,maxx);
    _t tminn = updateNewMin(depth,1,minn);
    bool f1 = tmaxx.index != -1;
    bool f2 = tminn.index != -1;
    int tmp;
    if(f1 && !f2 && minn.index != -1){//如果最大值有变化，最小值无变化且有最小值
        if(cha(tmaxx,minn,tmp)){
            OnceAns = tmp;
            dfs_1(depth+1,tmaxx,minn);
        }//else 就要被剪掉
    }else if(!f1 && f2 && maxx.index != -1){//如果最小值有变化且最大值无变化且有最大值
        if(cha(maxx,tminn,tmp)){
            OnceAns = tmp;
            dfs_1(depth+1,maxx,tminn);
        }//else 就要被剪掉
    }else{//没有变化要深搜，还是有可能用到tmaxx与tminn
        dfs_1(depth+1,f1?tmaxx:maxx,f2?tminn:minn);
    }

    //搜两位
    if(1==A[depth]&&depth+1<N){//可以搜两位
        tmaxx = updateNewMax(depth,2,maxx);
        tminn = updateNewMin(depth,2,minn);
        f1 = tmaxx.index != -1;
        f2 = tminn.index != -1;
        if(f1 && !f2 && minn.index != -1){//如果最大值有变化，最小值无变化且有最小值
            if(cha(tmaxx,minn,tmp)){
                OnceAns = tmp;
                dfs_1(depth+2,tmaxx,minn);
            }//else 就要被剪掉
        }else if(!f1 && f2 && maxx.index != -1){//如果最小值有变化且最大值无变化且有最大值
            if(cha(maxx,tminn,tmp)){
                OnceAns = tmp;
                dfs_1(depth+2,maxx,tminn);
            }//else 就要被剪掉
        }else{//没有变化要深搜，还是有可能用到tmaxx与tminn
            dfs_1(depth+2,f1?tmaxx:maxx,f2?tminn:minn);
        }
    }
}

//两位两位搜
void dfs_2(int depth,_t maxx,_t minn){
    //printf("%d\n",depth);
    if(depth==N){//到底了
        if((-1==Ans || OnceAns<Ans)&&OnceAns!=-1){
            Ans = OnceAns;
        }
        return;
    }

    if(depth+2>N||0==A[depth]){//剩下的不足两位，直接返回，或者0开头
        return;
    }

    //先搜两位，这是必须的
    _t tmaxx = updateNewMax(depth,2,maxx);
    _t tminn = updateNewMin(depth,2,minn);
    bool f1 = tmaxx.index != -1;
    bool f2 = tminn.index != -1;
    int tmp;
    if(f1 && !f2 && minn.index != -1){//如果最大值有变化，最小值无变化且有最小值
        if(cha(tmaxx,minn,tmp)){
            OnceAns = tmp;
            dfs_2(depth+2,tmaxx,minn);
        }//else 就要被剪掉
    }else if(!f1 && f2 && maxx.index != -1){//如果最小值有变化且最大值无变化且有最大值
        if(cha(maxx,tminn,tmp)){
            OnceAns = tmp;
            dfs_2(depth+2,maxx,tminn);
        }//else 就要被剪掉
    }else{//没有变化要深搜，还是有可能用到tmaxx与tminn
        dfs_2(depth+2,f1?tmaxx:maxx,f2?tminn:minn);
    }

    //搜三位
    if(1==A[depth]&&0==A[depth+1]&&depth+2<N){//可以搜三位
        tmaxx = updateNewMax(depth,3,maxx);
        tminn = updateNewMin(depth,3,minn);
        f1 = tmaxx.index != -1;
        f2 = tminn.index != -1;
        if(f1 && !f2 && minn.index != -1){//如果最大值有变化，最小值无变化且有最小值
            if(cha(tmaxx,minn,tmp)){
                OnceAns = tmp;
                dfs_2(depth+3,tmaxx,minn);
            }//else 就要被剪掉
        }else if(!f1 && f2 && maxx.index != -1){//如果最小值有变化且最大值无变化且有最大值
            if(cha(maxx,tminn,tmp)){
                OnceAns = tmp;
                dfs_2(depth+3,maxx,tminn);
            }//else 就要被剪掉
        }else{//没有变化要深搜，还是有可能用到tmaxx与tminn
            dfs_2(depth+3,f1?tmaxx:maxx,f2?tminn:minn);
        }
    }
}

//能否搜n位
bool isOK4n(int index,int n){
    if(index+n>N||1!=A[index++]) return false;
    for(int i=1;i<=n-2;++i){
        if(0!=A[index++]) return false;
    }
    return true;
}
//n位n位搜
void dfs_n(int depth,_t maxx,_t minn,int n){
    //printf("%d\n",depth);
    if(depth==N){//到底了
        if((-1==Ans || OnceAns<Ans)&&-1!=OnceAns){
            Ans = OnceAns;
        }
        return;
    }

    if(depth+n>N||0==A[depth]){//剩下的不足n位，直接返回
        return;
    }

    long long int left = (N-depth) % n;//看一下还单多少个，至少还要这么多个n+1位的
    long long int yichu = Cnt9[depth]/(n-1);
    if(Cnt1[depth]<left) return;        //这个剪枝有效果，否则只能过87%
    if(Cnt0[depth]<(left)*(n-1)) return;//这个剪枝效果不大

    //先搜n位，这是必须的
    _t tmaxx = updateNewMax(depth,n,maxx);
    _t tminn = updateNewMin(depth,n,minn);
    bool f1 = tmaxx.index != -1;
    bool f2 = tminn.index != -1;
    int tmp;
    if(f1 && !f2 && minn.index != -1){//如果最大值有变化，最小值无变化且有最小值
        if(cha(tmaxx,minn,tmp)){
            OnceAns = tmp;
            dfs_n(depth+n,tmaxx,minn,n);
        }//else 就要被剪掉
    }else if(!f1 && f2 && maxx.index != -1){//如果最小值有变化且最大值无变化且有最大值
        if(cha(maxx,tminn,tmp)){
            OnceAns = tmp;
            dfs_n(depth+n,maxx,tminn,n);
        }//else 就要被剪掉
    }else{//没有变化要深搜，还是有可能用到tmaxx与tminn
        dfs_n(depth+n,f1?tmaxx:maxx,f2?tminn:minn,n);
    }

    //搜n+1位
    if(isOK4n(depth,n+1)){//可以搜n+1位
        tmaxx = updateNewMax(depth,n+1,maxx);
        tminn = updateNewMin(depth,n+1,minn);
        f1 = tmaxx.index != -1;
        f2 = tminn.index != -1;
        if(f1 && !f2 && minn.index != -1){//如果最大值有变化，最小值无变化且有最小值
            if(cha(tmaxx,minn,tmp)){
                OnceAns = tmp;
                dfs_n(depth+n+1,tmaxx,minn,n);
            }//else 就要被剪掉
        }else if(!f1 && f2 && maxx.index != -1){//如果最小值有变化且最大值无变化且有最大值
            if(cha(maxx,tminn,tmp)){
                OnceAns = tmp;
                dfs_n(depth+n+1,maxx,tminn,n);
            }//else 就要被剪掉
        }else{//没有变化要深搜，还是有可能用到tmaxx与tminn
            dfs_n(depth+n+1,f1?tmaxx:maxx,f2?tminn:minn,n);
        }
    }
}
int main(){
    //freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);

    int nofkase;
    scanf("%d",&nofkase);

    while(nofkase--){
        scanf("%d%s",&N,Input);
        fill(Cnt0,Cnt0+N+1,0);
        fill(Cnt1,Cnt1+N+1,0);
        fill(Cnt9,Cnt9+N+1,0);

        int mmx = -1, mmi = 10;
        for(int i=N-1;i>=0;--i){
            mmx = max(mmx, A[i] = Input[i] - '0');
            mmi = min(mmi, A[i]);
            Cnt0[i] = Cnt0[i+1] + (0==A[i]?1:0);
            Cnt1[i] = Cnt1[i+1] + (1==A[i]?1:0);
            Cnt9[i] = Cnt9[i+1] + (9==A[i]?1:0);
        }

        Ans = mmx - mmi;//手工计算一位的情况
        if(0==Ans||2==N){
            printf("%d\n",Ans);
            continue;
        }

        OnceAns = Maxx.index = Minn.index = -1;
        dfs_1(0,Maxx,Minn);
        if(0 == Ans || 0 == A[0]){
            printf("%d\n",Ans);
            continue;
        }

        OnceAns = Maxx.index = Minn.index = -1;
        dfs_2(0,Maxx,Minn);
        if(0 == Ans||N<=4){
            printf("%d\n",Ans);
            continue;
        }
        //从3开始搜
        int m = N / 2 + 1;
        for(int i=3;i<=m;++i){
            OnceAns = Maxx.index = Minn.index = -1;
            dfs_n(0,Maxx,Minn,i);
            if(0==Ans)break;
        }
        printf("%d\n",Ans);
    }
    return 0;
}
