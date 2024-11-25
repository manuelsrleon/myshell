#make file - this is a comment section
ASSIGNMENT_ITERATION=shell
MODULES_DIR=modules

all: $(ASSIGNMENT_ITERATION).c p0lib p1lib p2lib cmdlist memorylist
	gcc -Wall -g -O0 -o $(ASSIGNMENT_ITERATION) $(ASSIGNMENT_ITERATION).c p0lib.o p1lib.o p2lib.o cmdlist.o memorylist.o
cmdlist:
	gcc -Wall -c $(MODULES_DIR)/cmdlist/cmdlist.c -o cmdlist.o
memorylist:
	gcc -Wall -c $(MODULES_DIR)/memorylist/memorylist.c -o memorylist.o
p0lib:
	gcc -Wall -g -c $(MODULES_DIR)/p0-clangintro.c -o p0lib.o
p1lib:
	gcc -Wall -g -c $(MODULES_DIR)/p1-filesystems.c -o p1lib.o
p2lib:
	gcc -Wall -g -c $(MODULES_DIR)/p2-memory.c -o p2lib.o
clean:
	rm *.o $(ASSIGNMENT_ITERATION)
run:
	./a.out

