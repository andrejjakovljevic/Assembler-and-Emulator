all: assembler

src/parser.cpp inc/parser.h: src/parser.y
	bison -o src/parser.cpp --define=api.location.file='"../inc/location.h"' --defines=inc/parser.h src/parser.y 

src/scanner.cpp: src/scanner.l src/parser.cpp
	flex -o src/scanner.cpp --header-file=inc/scanner.h src/scanner.l

assembler: src/*.cpp inc/*.h src/scanner.cpp
	g++ -std=c++17 -Wall -o assembler src/driver.cpp src/asm_main.cpp src/parser.cpp src/reallocation_table.cpp src/scanner.cpp src/sectioninfo.cpp src/symboltable.cpp -Iinc -fpermissive -g

install: assembler
	cp assembler /usr/bin

test1: assembler 
	./assembler -o ../zadatak2/test/interrupts.o test/interrupts.s
	./assembler -o ../zadatak2/test/main.o test/main.s
	./assembler -o ../zadatak2/test/interrupts2.o test/interrupts2.s
	./assembler -o ../zadatak2/test/main2.o test/main2.s