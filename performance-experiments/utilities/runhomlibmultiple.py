import sys, os
import timeit

from homlib import Graph, homint

# Counts multiple patterns using homlib in argv[1]

with open(sys.argv[1], 'r') as f:
	G = Graph(int(f.readline().split()[2]))
	for line in f:
		u, v = [int(vert) - 1 for vert in line.split()]
		G.addEdge(u, v)

patterns = []

for i in range(2, len(sys.argv)):
	with open(sys.argv[i], 'r') as f:
		H = Graph(int(f.readline().split()[2]))
		for line in f:
			u, v = [int(vert) - 1 for vert in line.split()]
			H.addEdge(u, v)
		patterns.append(H)
		
		
def count():
	counts = ''.join([str(homint(H, G)) + ";" for H in patterns])[:-1]
	print(counts, end=',,')

print('homlib,' + sys.argv[1], end=',')
print(timeit.timeit(count, number=1))

