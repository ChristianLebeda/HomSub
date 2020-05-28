import sys
import os

# Args:
# rangelow rangehigh rangestep rangefactor graphsize rep

low = int(sys.argv[1])
high = int(sys.argv[2])
step = int(sys.argv[3])
factor = float(sys.argv[4])

for i in range(low, high + 1, step):
    os.system("./gen.sh 42 " + sys.argv[5] + " " + '{:.4f}'.format(i * factor) + " " + sys.argv[6])

