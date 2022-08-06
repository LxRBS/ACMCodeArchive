#include<cstdio>
#include<cstring>
const int N=1000005;
int Case,n,i;char s[N];
int main(){
  fgets(s,N,stdin);
  sscanf(s,"%d",&Case);
  while(Case--){
    fgets(s,N,stdin);
    n=strlen(s);
    for(i=0;i<n;i++)
      if(s[i]>='a'&&s[i]<='z')
        if(!i||(i>0&&s[i-1]==' '))
          putchar(s[i]-'a'+'A');
    puts("");
  }
}