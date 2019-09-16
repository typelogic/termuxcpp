
main: main.cpp Makefile
	g++ main.cpp -o main

clean:
	@rm -f main *.o 
