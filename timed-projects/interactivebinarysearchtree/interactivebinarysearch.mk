CC = g++ # Compiler to use
OPTIONS = -O2 -g -Wall # -g for debug, -O2 for optimise and -Wall additional messages
INCLUDES = -I . # Directory for header file
TARGET = binarysearchtree.run
.PHONY: all clean list # To declare all, clean are not files
 
OBJS = main.o  # List of objects to be built

#TODO: Figure out how to make this work
#%.o:
#	%.cpp
#	${CC} ${OPTIONS} -c $*.cpp ${INCLUDES}

all:
	@echo `date`
	@echo "Linking it all ..."
#	${OBJS}
	main.o
	${CC} ${OPTIONS} ${INCLUDES} ${OBJS} -o ${TARGET}
 
main.o:
	@echo `date`
	@echo "Compiling main ..."
	${CC} ${OPTIONS }-c main.cpp ${INCLUDES}

list:
	@echo $(shell ls) # To print output of command 'ls'
 
clean:
	@echo `date`
	@echo "Cleaning up.."
	-rm -rf *.o
	-rm ${TARGET} 
