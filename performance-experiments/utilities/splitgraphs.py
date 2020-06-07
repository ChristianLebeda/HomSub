import sys

# Splits graphs outputted by HomSub

n = -1
m = -1

graphs = []

graph = []

with open(sys.argv[1]) as f:
    for line in f:
        words = line.split()
        if(words[0] == 'c'): continue

        if(words[0] == 'p'):
            graphs.append(''.join(graph))
            graph = []
        
        graph.append(line)

graphs.append(''.join(graph))

for i in range(1, len(graphs)):
    with open(str(i) + '.gr', 'w') as f:
        f.write(graphs[i])