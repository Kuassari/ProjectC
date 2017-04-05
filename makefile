Assembler : assembler.o utilities.o FirstLoop.o SecondLoop.o structs.o
	gcc -g -ansi -Wall -pedantic assembler.o utilities.o FirstLoop.o SecondLoop.o structs.o -o Assembler

assembler.o : assembler.c common.h
	gcc -c -ansi -Wall -pedantic assembler.c -o assembler.o

utilities.o : utilities.c common.h
	gcc -c -ansi -Wall -pedantic utilities.c -o utilities.o

FirstLoop.o : FirstLoop.c structs.h 
	gcc -c -ansi -Wall -pedantic FirstLoop.c -o FirstLoop.o

SecondLoop.o : SecondLoop.c structs.h 
	gcc -c -ansi -Wall -pedantic SecondLoop.c -o SecondLoop.o

structs.o : structs.c structs.h
	gcc -c -ansi -Wall -pedantic structs.c -o structs.o
