CC=g++
CFLAGS=-c -Wall
LDFLAGS=
OBJECTS=$(SOURCES:.cpp=.o)

all: pe-parser.cpp pe-parser

validation-pe-tests: all
	python3 -m tests ValidatingPeTestCases -f

import-dll-tests: all
	python3 -m tests ImportDllTestCases -f

import-function-tests: all
	python3 -m tests ImportFunctionTestCases -f

export-function-tests: all
	python3 -m tests ExportFunctionTestCases -f

clean:
	-rm  pe-parser