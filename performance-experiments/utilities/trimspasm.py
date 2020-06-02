import sys

with open(sys.argv[1], 'r') as spasm:
	split = spasm.readline().split()
	size = int(split[1])
	split[1] = '1'
	print(' '.join(split), end='')
	print(spasm.readline(), end='')
	print(spasm.readline(), end='')
	for _ in range(size - 1):
		spasm.readline()
	print(spasm.readline(), end='')
	for line in spasm:
		if line.split()[0] == 's':
			break
		print(line, end='')

