# Khai Nguyen
#

# define a target for the application
#
all: myserver

# define a target to link the application
#
myserver: main.cpp function.cpp
	g++ main.cpp function.cpp -o myserver -lpthread

# define a target to clean the directory
#
clean:
	rm -f *.o *.exe
#
# end of file
