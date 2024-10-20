#make file - this is a comment section
ASSIGNMENT_ITERATION=p2
SOURCE_DIRECTORY=/src

all: $(ASSIGNMENT_ITERATION).c p0lib p1lib p2lib list
	gcc -Wall -g -O0 -o $(ASSIGNMENT_ITERATION) $(ASSIGNMENT_ITERATION).c p0lib.o p1lib.o p2lib.o list.o

p0lib: 
	gcc -Wall -g -c .$(SOURCE_DIRECTORY)/p0/clangintro.c -o p0lib.o
p1lib: 
	gcc -Wall -g -c .$(SOURCE_DIRECTORY)/p1/filesystems.c -o p1lib.o
p2lib:
	gcc -Wall -g -c .$(SOURCE_DIRECTORY)/p2/memory.c -o p2lib.o
ayudaP1:
	gcc -Wall -g -c .$(SOURCE_DIRECTORY)/ayuda/ayudaP1.c -o ayudap1.o
list: 
	gcc -Wall -g -c .$(SOURCE_DIRECTORY)/list/dynamic_list.c -o list.o

clean: 
	rm p0lib.o p1lib.o $(ASSIGNMENT_ITERATION)
run: 
	./$(ASSIGNMENT_ITERATION)
