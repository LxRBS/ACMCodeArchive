//太简单，不用解题报告
#include<stdio.h>
#include<math.h>
int main()
{
 int n,m,i,j,a,b,sum;
 while(scanf("%d%d",&n,&m)!=EOF)
 {   
  sum=0;
  for(i=0;i<n;i++)
  {
   scanf("%d%d",&a,&b);
   sum=(abs(a-b)-1)^sum;
  }
  if(sum==0) printf("BAD LUCK!\n");
  else printf("I WIN!\n");
 }
 return 0;
}
