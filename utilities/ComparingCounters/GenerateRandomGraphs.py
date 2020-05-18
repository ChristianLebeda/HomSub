import sys
import random

n = int(sys.argv[1])
p = float(sys.argv[2].replace(",", "."))

edges = []

for u in range(n):
    for v in range(n):
        if(u < v):
            r = random.random()
            if ( r < p):
                edges.append((u,v))

print("p tw",n,len(edges))

for edge in edges:
    print(edge[0], edge[1])