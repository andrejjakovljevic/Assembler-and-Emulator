all: linker

linker: src/*.cpp inc/*.h 
	g++ -std=c++17 -Wall -o linker src/linker_main.cpp src/reallocation_table.cpp src/sectioninfo.cpp src/symboltable.cpp src/linker_input.cpp -Iinc -fpermissive -g

install: linker
	cp linker /usr/bin

test1: linker
	./linker -o ../zadatak3/test/test.hex test/interrupts.o test/main.o -hex -place=ivt@0x0000
	./linker -o ../zadatak3/test/test2.hex test/interrupts2.o test/main2.o -hex -place=ivt@0x0000