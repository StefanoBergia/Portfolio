#
# Makefile
#

target :
	echo "compiling my applications"
	gcc -Wall main.c -o main.o



install : target
	mkdir bin
	mv main.o ./bin
	

clean :
	rm -f *.o

distclean : clean
	rm -R ./bin
