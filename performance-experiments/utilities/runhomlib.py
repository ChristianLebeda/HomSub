import sys, os
import timeit

from homlib import Graph, homint

# Use homlib to count argv[1] copies in argv[2]

with open(sys.argv[1], 'r') as f:
	H = Graph(int(f.readline().split()[2]))
	for line in f:
		u, v = [int(vert) - 1 for vert in line.split()]
		H.addEdge(u, v)
	

with open(sys.argv[2], 'r') as f:
	G = Graph(int(f.readline().split()[2]))
	for line in f:
		u, v = [int(vert) - 1 for vert in line.split()]
		G.addEdge(u, v)
	
def count():
	print(homint(H, G), end=',,')

print('homlib,' + sys.argv[2], end=',')
print(timeit.timeit(count, number=1))

