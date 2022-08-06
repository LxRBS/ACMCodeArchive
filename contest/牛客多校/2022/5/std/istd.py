n, m, k, x=map(int, input().split())

ans=0
for tmp1 in range(max(n//k-m,0), n//k+1):
    tmp2=(n-k*tmp1)%m
    if tmp2==0:
        tmp2=m
    tmp3=m-tmp2 
    mx=(n-k*tmp1+m-1)//m 
    res2=tmp1*n-k*tmp1*(tmp1-1)//2
    res2+=(n-k*tmp1)*tmp2-mx*tmp2*(tmp2-1)//2
    res2+=(n-k*tmp1-mx*tmp2)*tmp3-(mx-1)*tmp3*(tmp3-1)//2
    ans=max(ans, res2)

if(ans >= int(x)):
    print("YES "+str(ans)+"\n")
else:
    print("NO\n")
