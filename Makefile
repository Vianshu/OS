all: c d

c:
	gcc threadsched.c -o threadsched

d:
	gcc processsched.c -o processsched
