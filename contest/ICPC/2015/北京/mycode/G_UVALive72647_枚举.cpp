/**
   ����4�����εĳߴ磬���ܲ��ܴ���ѡ3��ƴ��һ�������
   ����ö��
   ����ܹ���ֻ��2�ֿ��ܣ�����������
   1�У�abc
   2�У�ab/c
*/
#include <stdio.h>
#include <algorithm>
using namespace std;

int W[4],H[4];

//�ų�һ�У����Ȼ3����ͬһ�ߴ�
bool f1(int const w[],int const h[]){
    int t = w[0];
    bool flag = true;
    for(int i=1;i<3;++i){
        if(t==w[i]||t==h[i])continue;
        flag = false;
        break;
    }
    if(flag) return true;
    t = h[0];
    for(int i=1;i<3;++i){
        if(t==w[i]||t==h[i])continue;
        return false;
    }
    return true;
}

//��֤w��h������������������Ƿ����dw����dh����ʣ�µ����������
bool f2(int const w[],int const h[],int dw,int dh){
    if(h[0]==h[1]&&(w[0]+w[1]==dw||w[0]+w[1]==dh)) return true;
    if(h[0]==w[1]&&(w[0]+h[1]==dw||w[0]+h[1]==dh)) return true;
    if(w[0]==h[1]&&(h[0]+w[1]==dw||h[0]+w[1]==dh)) return true;
    return w[0]==w[1]&&(h[0]+h[1]==dw||h[0]+h[1]==dh);
}
//�ų�2�У����Ȼ2��֮�͵��ڵ�3��
bool f2(int const w[],int const h[]){
    for(int i=0;i<3;++i){
        int a[2],b[2],k=0;
        for(int j=0;j<3;++j)if(i!=j){
            a[k] = w[j];
            b[k++] = h[j];
        }
        if(f2(a,b,w[i],h[i])) return true;
    }
    return false;
}

//����n�������ó�������ʣ�µ�3���ܷ񹹳ɴ����
bool f(int n){
    int k = 0;
    int w[3],h[3];
    for(int i=0;i<4;++i)if(i!=n){
        w[k] = W[i];
        h[k++] = H[i];
    }
    return f1(w,h)||f2(w,h);
}
bool f(){
    for(int i=0;i<4;++i)if(f(i)){
        return true;
    }
    return false;
}

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);
    while(nofkase--){
        for(int i=0;i<4;++i)scanf("%d%d",W+i,H+i);
        printf(f()?"Yes\n":"No\n");
    }
    return 0;
}
