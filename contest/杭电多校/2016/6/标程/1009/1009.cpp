#include<bits/stdc++.h>
using namespace std;

const int maxn=1e5+100;
char s[maxn],t[50];
int nxt[maxn*20][5],num[maxn*20];
int tr[20][maxn],sz;
void update(int &tr,int pre,char buf[],int pos)
{
	tr=++sz;
	num[tr]=num[pre]+1;
	for(int i=0;i<5;++i)
		nxt[tr][i]=nxt[pre][i];
	if(buf[pos]=='\0')return;
	update(nxt[tr][buf[pos]-'a'],nxt[pre][buf[pos]-'a'],buf,pos+1);
}
int query(int lch,int rch,char buf[],int pos)
{
	if(buf[pos]=='\0')
		return num[rch]-num[lch];
	return query(nxt[lch][buf[pos]-'a'],nxt[rch][buf[pos]-'a'],buf,pos+1);
}
bool is(int i)
{
	for(int p=0,q=i-1;p<q;++p,--q)
		if(t[p]!=t[q])return false;
	return true;
}
int main()
{
	int cas=1;
	while(scanf("%s",s+1)!=EOF)	
	{
		sz=0;
		memset(tr,0,sizeof(tr));
		int n=strlen(s+1);
		for(int i=1;i<=20;++i)
			for(int j=i,k=1;j<=n;++j,++k)
			{
				for(int p=k,q=0;p<=j;++p,++q)
					t[q]=s[p];
				t[i]='\0';
				if(is(i))
				{
					//cout <<k<<" "<<j<<" "<<t<<" "<<i/2<<endl;
					update(tr[i-1][j],tr[i-1][j-1],t,i/2);
				}
				else tr[i-1][j]=tr[i-1][j-1];
			}
		int q,l,r;
		scanf("%d",&q);
	//	printf("Case #%d:\n",cas++);
		for(int i=0;i<q;++i)
		{
			scanf("%d%d%s",&l,&r,t);
			if(l>r)cerr <<"should swap"<<endl;
			if(r<=0||r>n||l<=0||l>n)cerr <<i<<" j&r limit error:"<<l<<" "<<r<<endl;
			int res=0;
			for(int i=0,j=l-1;i<20&&j<r;++i,++j)
			{
				res+=query(tr[i][j],tr[i][r],t,0);
				//cout <<"length:"<<i+1<<" "<<res<<endl;
				//cout <<query(0,tr[i][j],t,0)<<" "<<query(0,tr[i][r],t,0)<<endl;
			}
			printf("%d\n",res);
		}
	}
	return 0;
}
