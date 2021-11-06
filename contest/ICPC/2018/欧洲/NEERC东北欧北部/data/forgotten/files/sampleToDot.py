n, k = map(int, input().split())
a = list(map(int, input().split()))
u = []
v = []
for i in range(n - 1):
    uu, vv = map(int, input().split())
    u.append(uu)
    v.append(vv)

#styles = ["solid", "rounded", "filled", "dashed", "bold", "dotted", "diagonals", "striped", "wedged"]
shapes = ["circle", "triangle", "square", "pentagon", "octagon"]

print("graph G {")
for i in range(n):
    shape = shapes[a[i]]
    print("    " + str(i + 1) + " [shape=" + shape + "]")
for i in range(n - 1):
    color = "black"
    print("    " + str(u[i]) + " -- " + str(v[i]) + " [color=" + color + "]")
print("}")
