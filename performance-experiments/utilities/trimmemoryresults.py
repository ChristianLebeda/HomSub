import sys

print("Creating results.csv")

def appendAverage(out, algo, tests, rep):
    with open("output/" + algo + ".log", "r") as f:
        for i in range(tests):
            memory = []
            for line in f:
                if line.strip().startswith('Maximum resident set size'):
                    memory.append(int(line.strip().split()[-1]))
                    if len(memory) == rep:
                        break
            out.write(algo + ',' + str(i) +',')
            out.write(str(sum(memory) // len(memory)))
            out.write('\n')

                

with open("output/results.csv", "w") as result:
    result.write("algorithm,input,memory\n")
    tests = int(sys.argv[1])
    rep = int(sys.argv[2])
    for arg in sys.argv[3:]:
        print('Appending', arg, 'results')
        if(arg == 'treewidth'):
            appendAverage(result, arg, tests, 1)
        else:
            appendAverage(result, arg, tests, rep)
