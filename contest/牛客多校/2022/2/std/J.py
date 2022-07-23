def work():
    x=0
    y=0
    z=0
    k=0 
    s=0
    n=int(input())
    w = input().split()
    for i in range(n):
        a=int(w[i])
        x+=i*i
        y+=a*i
        z+=a
        k+=i
        s+=a*a
        # print(a)
    A=-k*k+n*x
    B=2*(z*x-k*y)
    C=s*x-y*y
    print("%.15f"%((C*4*A-B*B)/(4*A*x)))

t=int(input())
while t>0:
    work()
    t-=1
