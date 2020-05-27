import sys

print("Creating results.csv")

def appendTreewidth(out):
    print("Appending treewidth results")
    with open("output/treewidth.csv", "r") as f:
        for line in f:
            out.write(line)

def appendDegree(out):
    print("Appending degree results")
    with open("output/degree.csv", "r") as f:
        for line in f:
            out.write(line)

def appendVF3(out):
    print("Appending VF3 results")
    with open("output/vf3.out", "r") as f:
        for line in f:
            out.write(line.replace(' ',','))

def appendGlasgow(out):
    print("Appending glasgow results")
    with open("output/glasgow.out", "r") as f:
        for line in f:
            if(line.startswith("glasgow")):
                out.write(line.strip())
            if(line.startswith("solution_count")):
                out.write(line.strip().split()[-1])
            if(line.startswith("runtime")):
                time = float(line.split()[-1]) / 1000
                out.write(",," + str(time) + "\n")
                


with open("output/results.csv", "w") as result:
    result.write("algorithm,input,count,foundfirst,time\n")
    appendTreewidth(result)
    #appendDegree(result)
    appendVF3(result)
    appendGlasgow(result)


