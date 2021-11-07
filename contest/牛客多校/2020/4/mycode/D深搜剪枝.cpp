/**
   ����һ�����ִ���10��λ
   �����ֳ����ɣ�Ҫ�����ֵ��ȥ��Сֵ��С
   ���Ѽ�֦��nλnλ�Ľ��л���
   ��ÿһ����ǰλ�������ֿ��ܣ�nλ��n+1λ
   ��ϼ�֦���ٶȺܿ�
*/
#include <bits/stdc++.h>
using namespace std;

int const SIZE = 100010;
char Input[SIZE];
int N;
int A[SIZE];
int Cnt0[SIZE], Cnt1[SIZE], Cnt9[SIZE];//1��������0��������9

int Ans; //�ܴ�
int OnceAns;//��ǰ��һ�εĴ�
struct _t{
    int index;//��ʼλ��
    int cnt;  //����
}Maxx,Minn,OriginMaxx,OriginMinn;

//��index��ʼ��cntλ�Ƿ�Ϊ�µ����ֵ������ǻ����и��£�����true�����򲻸��¡�����false
_t updateNewMax(int index,int cnt,_t maxx){
    if(maxx.index==-1){//���ԭ��û�����ֵ����Ȼ��
        maxx.index = index;
        maxx.cnt = cnt;
        return maxx;
    }
    if(cnt>maxx.cnt){//���λ������Ȼ��
        maxx.index = index;
        maxx.cnt = cnt;
        return maxx;
    }
    if(cnt<maxx.cnt){
        maxx.index = -1;
        return maxx;
    }
    for(int i=index,j=maxx.index,k=0;k<cnt;++i,++j,++k){
        if(A[i]>A[j]){//��Ȼ��
            maxx.index = index;
            maxx.cnt = cnt;
            return maxx;
        }
        if(A[i]<A[j]){//��ȻС
            maxx.index = -1;
            return maxx;
        }
    }

    //���ֵ����������
    maxx.index = index;
    maxx.cnt = cnt;
    return maxx;
}
_t updateNewMin(int index,int cnt,_t minn){
    if(minn.index==-1){//���ԭ��û����Сֵ����ȻС
        minn.index = index;
        minn.cnt = cnt;
        return minn;
    }
    if(cnt<minn.cnt){//���λ��С����ȻС
        minn.index = index;
        minn.cnt = cnt;
        return minn;
    }
    if(cnt>minn.cnt){
        minn.index = -1;
        return minn;
    }
    for(int i=index,j=minn.index,k=0;k<cnt;++i,++j,++k){
        if(A[i]<A[j]){//��ȻС
            minn.index = index;
            minn.cnt = cnt;
            return minn;
        }
        if(A[i]>A[j]){//��Ȼ��
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
    if(icnt>jcnt){//���ֻ��һλ
        ret = A[idx] * 10 + A[idx+1] - A[jdx];
        if(ret > Ans){//����ȵ�ǰ���ܴ𰸴󣬲�������
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

//һλһλ��
void dfs_1(int depth,_t maxx,_t minn){
    //printf("%d\n",depth);
    if(depth==N){//������
        if((-1==Ans || OnceAns<Ans)&&-1!=OnceAns){
            Ans = OnceAns;
        }
        return;
    }

    //����һλ�����Ǳ����
    _t tmaxx = updateNewMax(depth,1,maxx);
    _t tminn = updateNewMin(depth,1,minn);
    bool f1 = tmaxx.index != -1;
    bool f2 = tminn.index != -1;
    int tmp;
    if(f1 && !f2 && minn.index != -1){//������ֵ�б仯����Сֵ�ޱ仯������Сֵ
        if(cha(tmaxx,minn,tmp)){
            OnceAns = tmp;
            dfs_1(depth+1,tmaxx,minn);
        }//else ��Ҫ������
    }else if(!f1 && f2 && maxx.index != -1){//�����Сֵ�б仯�����ֵ�ޱ仯�������ֵ
        if(cha(maxx,tminn,tmp)){
            OnceAns = tmp;
            dfs_1(depth+1,maxx,tminn);
        }//else ��Ҫ������
    }else{//û�б仯Ҫ���ѣ������п����õ�tmaxx��tminn
        dfs_1(depth+1,f1?tmaxx:maxx,f2?tminn:minn);
    }

    //����λ
    if(1==A[depth]&&depth+1<N){//��������λ
        tmaxx = updateNewMax(depth,2,maxx);
        tminn = updateNewMin(depth,2,minn);
        f1 = tmaxx.index != -1;
        f2 = tminn.index != -1;
        if(f1 && !f2 && minn.index != -1){//������ֵ�б仯����Сֵ�ޱ仯������Сֵ
            if(cha(tmaxx,minn,tmp)){
                OnceAns = tmp;
                dfs_1(depth+2,tmaxx,minn);
            }//else ��Ҫ������
        }else if(!f1 && f2 && maxx.index != -1){//�����Сֵ�б仯�����ֵ�ޱ仯�������ֵ
            if(cha(maxx,tminn,tmp)){
                OnceAns = tmp;
                dfs_1(depth+2,maxx,tminn);
            }//else ��Ҫ������
        }else{//û�б仯Ҫ���ѣ������п����õ�tmaxx��tminn
            dfs_1(depth+2,f1?tmaxx:maxx,f2?tminn:minn);
        }
    }
}

//��λ��λ��
void dfs_2(int depth,_t maxx,_t minn){
    //printf("%d\n",depth);
    if(depth==N){//������
        if((-1==Ans || OnceAns<Ans)&&OnceAns!=-1){
            Ans = OnceAns;
        }
        return;
    }

    if(depth+2>N||0==A[depth]){//ʣ�µĲ�����λ��ֱ�ӷ��أ�����0��ͷ
        return;
    }

    //������λ�����Ǳ����
    _t tmaxx = updateNewMax(depth,2,maxx);
    _t tminn = updateNewMin(depth,2,minn);
    bool f1 = tmaxx.index != -1;
    bool f2 = tminn.index != -1;
    int tmp;
    if(f1 && !f2 && minn.index != -1){//������ֵ�б仯����Сֵ�ޱ仯������Сֵ
        if(cha(tmaxx,minn,tmp)){
            OnceAns = tmp;
            dfs_2(depth+2,tmaxx,minn);
        }//else ��Ҫ������
    }else if(!f1 && f2 && maxx.index != -1){//�����Сֵ�б仯�����ֵ�ޱ仯�������ֵ
        if(cha(maxx,tminn,tmp)){
            OnceAns = tmp;
            dfs_2(depth+2,maxx,tminn);
        }//else ��Ҫ������
    }else{//û�б仯Ҫ���ѣ������п����õ�tmaxx��tminn
        dfs_2(depth+2,f1?tmaxx:maxx,f2?tminn:minn);
    }

    //����λ
    if(1==A[depth]&&0==A[depth+1]&&depth+2<N){//��������λ
        tmaxx = updateNewMax(depth,3,maxx);
        tminn = updateNewMin(depth,3,minn);
        f1 = tmaxx.index != -1;
        f2 = tminn.index != -1;
        if(f1 && !f2 && minn.index != -1){//������ֵ�б仯����Сֵ�ޱ仯������Сֵ
            if(cha(tmaxx,minn,tmp)){
                OnceAns = tmp;
                dfs_2(depth+3,tmaxx,minn);
            }//else ��Ҫ������
        }else if(!f1 && f2 && maxx.index != -1){//�����Сֵ�б仯�����ֵ�ޱ仯�������ֵ
            if(cha(maxx,tminn,tmp)){
                OnceAns = tmp;
                dfs_2(depth+3,maxx,tminn);
            }//else ��Ҫ������
        }else{//û�б仯Ҫ���ѣ������п����õ�tmaxx��tminn
            dfs_2(depth+3,f1?tmaxx:maxx,f2?tminn:minn);
        }
    }
}

//�ܷ���nλ
bool isOK4n(int index,int n){
    if(index+n>N||1!=A[index++]) return false;
    for(int i=1;i<=n-2;++i){
        if(0!=A[index++]) return false;
    }
    return true;
}
//nλnλ��
void dfs_n(int depth,_t maxx,_t minn,int n){
    //printf("%d\n",depth);
    if(depth==N){//������
        if((-1==Ans || OnceAns<Ans)&&-1!=OnceAns){
            Ans = OnceAns;
        }
        return;
    }

    if(depth+n>N||0==A[depth]){//ʣ�µĲ���nλ��ֱ�ӷ���
        return;
    }

    long long int left = (N-depth) % n;//��һ�»������ٸ������ٻ�Ҫ��ô���n+1λ��
    long long int yichu = Cnt9[depth]/(n-1);
    if(Cnt1[depth]<left) return;        //�����֦��Ч��������ֻ�ܹ�87%
    if(Cnt0[depth]<(left)*(n-1)) return;//�����֦Ч������

    //����nλ�����Ǳ����
    _t tmaxx = updateNewMax(depth,n,maxx);
    _t tminn = updateNewMin(depth,n,minn);
    bool f1 = tmaxx.index != -1;
    bool f2 = tminn.index != -1;
    int tmp;
    if(f1 && !f2 && minn.index != -1){//������ֵ�б仯����Сֵ�ޱ仯������Сֵ
        if(cha(tmaxx,minn,tmp)){
            OnceAns = tmp;
            dfs_n(depth+n,tmaxx,minn,n);
        }//else ��Ҫ������
    }else if(!f1 && f2 && maxx.index != -1){//�����Сֵ�б仯�����ֵ�ޱ仯�������ֵ
        if(cha(maxx,tminn,tmp)){
            OnceAns = tmp;
            dfs_n(depth+n,maxx,tminn,n);
        }//else ��Ҫ������
    }else{//û�б仯Ҫ���ѣ������п����õ�tmaxx��tminn
        dfs_n(depth+n,f1?tmaxx:maxx,f2?tminn:minn,n);
    }

    //��n+1λ
    if(isOK4n(depth,n+1)){//������n+1λ
        tmaxx = updateNewMax(depth,n+1,maxx);
        tminn = updateNewMin(depth,n+1,minn);
        f1 = tmaxx.index != -1;
        f2 = tminn.index != -1;
        if(f1 && !f2 && minn.index != -1){//������ֵ�б仯����Сֵ�ޱ仯������Сֵ
            if(cha(tmaxx,minn,tmp)){
                OnceAns = tmp;
                dfs_n(depth+n+1,tmaxx,minn,n);
            }//else ��Ҫ������
        }else if(!f1 && f2 && maxx.index != -1){//�����Сֵ�б仯�����ֵ�ޱ仯�������ֵ
            if(cha(maxx,tminn,tmp)){
                OnceAns = tmp;
                dfs_n(depth+n+1,maxx,tminn,n);
            }//else ��Ҫ������
        }else{//û�б仯Ҫ���ѣ������п����õ�tmaxx��tminn
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

        Ans = mmx - mmi;//�ֹ�����һλ�����
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
        //��3��ʼ��
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
