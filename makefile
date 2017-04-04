Assembler : assembler.o utilities.o FirstLoop.o SecondLoop.o
	gcc -g -ansi -Wall -pedantic assembler.o utilities.o FirstLoop.o SecondLoop.o -o Assembler

assembler.o : assembler.c common.h
	gcc -c -ansi -Wall -pedantic assembler.o -o assembler.c

utilities.o : utilities.c common.h
	gcc -c -ansi -Wall -pedantic utilities.o -o utilities.c

FirstLoop.o : FirstLoop.c common.h
	gcc -c -ansi -Wall -pedantic FirstLoop.o -o FirstLoop.c

SecondLoop.o : SecondLoop.c common.h
	gcc -c -ansi -Wall -pedantic SecondLoop.o -o SecondLoop.c
