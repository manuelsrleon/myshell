#make file - this is a comment section
ASSIGNMENT_ITERATION=shell
MODULES_DIR=modules

all: $(ASSIGNMENT_ITERATION).c p0lib p1lib cmdlist
	gcc -Wall -g -O0 -o $(ASSIGNMENT_ITERATION) $(ASSIGNMENT_ITERATION).c p0lib.o p1lib.o cmdlist.o
cmdlist:
	gcc -Wall -c $(MODULES_DIR)/cmdlist/cmdlist.c -o cmdlist.o
p0lib:
	gcc -Wall -g -c $(MODULES_DIR)/p0-clangintro.c -o p0lib.o
p1lib:
	gcc -Wall -g -c $(MODULES_DIR)/p1-filesystems.c -o p1lib.o
# p2lib:
# gcc -Wall -g -c .$(MODULES_DIR)/p2/memory.c -o p2lib.o
# ayudaP1:
# gcc -Wall -g -c .$(MODULES_DIR)/ayuda/ayudaP1.c -o ayudap1.o
# list: 
# gcc -Wall -g -c .$(MODULES_DIR)/list/dynamic_list.c -o list.o

clean: 
	rm *.o $(ASSIGNMENT_ITERATION)
run: 
	./a.out
