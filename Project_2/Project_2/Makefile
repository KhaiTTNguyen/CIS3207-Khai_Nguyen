# Khai Nguyen
#

# define a target for the application
#
all: myshell

# define a target to link the application
#
myshell: myshell.o function.o
	g++ -lm myshell.o function.o -o myshell

# define targets to compile the source code
#
myshell.o: main.c header.h Makefile
	g++ -O2 -c main.c -o myshell.o
function.o: function.c header.h Makefile
	g++ -O2 -c function.c -o function.o

# define a target to clean the directory
#
clean:
	rm -f *.o *.exe

#
# end of file

