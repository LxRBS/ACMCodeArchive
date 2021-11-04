#include<bits/stdc++.h>
using namespace std;

int T,n,cnt[27];
char s[200010];

int main()
{
    scanf("%d",&T);
    for (int TT=1; TT<=T; TT++)
    {
        scanf("%s",s),n=strlen(s);
        memset(cnt,0,sizeof(cnt));
        for (int i=0; i<n; i++) cnt[s[i]-'a']++;
        int ma=0;
        for (int i=0; i<26; i++) ma=max(ma,cnt[i]);
        printf("Case #%d: %d\n",TT,ma);
    }
}