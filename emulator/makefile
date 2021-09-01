all: emulator

emulator: src/*.cpp inc/*.h 
	g++ -std=c++17 -Wall -o emulator src/emulator_main.cpp src/processor.cpp src/terminal.cpp -Iinc -fpermissive -g

install: emulator
	cp emulator /usr/bin

test1: emulator
	./emulator test/test.hex