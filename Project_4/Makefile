# Khai Nguyen
#

# define a target for the application
#
all: myfilesystem

# define a target to link the application
#
myfilesystem: main.c function.c disk.c
	g++ main.c function.c disk.c -o myfilesystem 

# define a target to clean the directory
#
clean:
	rm -f *.o *.exe
#
# end of file
