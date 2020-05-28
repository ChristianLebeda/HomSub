import sys

n = -1
m = -1

adjLists = []

with open(sys.argv[1]) as openfileobject:
    for line in openfileobject:
        words = line.split()
        if(words[0] == 'c'): continue

        if(words[0] == 'p'):
            n = int(words[2])
            m = int(words[3])
            adjLists = [[] for i in range(n)]
        else:
            u = int(words[0])
            v = int(words[1])
            adjLists[u-1].append(v-1)

print(n)

for i in range(0, n):
    print(i, 1)

u = 0
for uList in adjLists:
    print(len(uList))
    for v in uList:
        print(u, v)
    u = u + 1

