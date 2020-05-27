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
            adjLists[v-1].append(u-1)

print(n)

u = 0
for uList in adjLists:
    print(len(uList), end="")
    for v in uList:
        print("", v, end="")
    print()
    u = u + 1

