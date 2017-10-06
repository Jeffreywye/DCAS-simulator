all: compile

compile:
	g++ src/DCAS.cpp -o run

run:
	g++ src/DCAS.cpp -o run
	./run

clean:
	rm -f run.exe

capture:
