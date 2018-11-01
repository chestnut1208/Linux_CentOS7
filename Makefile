objects = test5-1.c test5-2.c test5-3.c
all : test5-1 test5-2 test5-3

test5-1 : test5-1.o
	gcc -o test5-1 test5-1.o
test5-2 : test5-2.o
	gcc -o test5-2 test5-2.o
test5-3 : test5-3.o
	gcc -o test5-3 test5-3.o
.PHONY : clean
clean :
	rm -f *.o test5-1 test5-2 test5-3
