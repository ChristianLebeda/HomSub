import sys

n = -1
m = 0

adjLists = []

with open(sys.argv[1]) as openfileobject:
    i = 0
    for line in openfileobject:
        words = line.split()
        if(n < 0):
            n = int(words[0])
            adjLists = [[] for i in range(n)]
        if(i < n+1):
            i = i + 1
            continue
        
        if(len(words) < 2):
            continue

        u = int(words[0])
        v = int(words[1])
        adjLists[u].append(v)
        m = m + 1

print("p tw " + str(n) + " " + str(m))

u = 0
for uList in adjLists:
    for v in uList:
        print(u+1, v+1)
    u = u + 1
