CC=g++
CFLAG=-Wall
MAIN=main
OUT=main

OBJ_DIR=obj
OBJ=error.o state.o tokenizer.o expression.o token.o parse.o detector.o statement.o
OBJS=$(OBJ:%=$(OBJ_DIR)/%)

all: $(OBJ)
	$(CC) $(CFLAG) src/$(MAIN).cpp ${OBJS} -o bin/$(OUT).out
	#release-binary: ./bin/$(OUT).out

debug: OUT=main-debug
debug: CFLAG+= -D DEBUG -g
debug: debug-show $(OBJ)
	$(CC) $(CFLAG) src/$(MAIN).cpp ${OBJS} -o bin/$(OUT).out
	#debug-binary: ./bin/$(OUT).out

todo:
	#Lising TODO
	grep -rn TODO *

#.cpp.o:
#	${CC} ${CFLAG} ${INCLUDES} -c $<
error: error.o
	#error

error.o: inc/error.cpp inc/error.h
	$(CC) ${CFLAG} -c inc/error.cpp -o obj/error.o

debug-state: OUT=test-state-debug
debug-state: CFLAG+= -D DEBUG -g
debug-state: OBJ=state.o
debug-state: OBJS=$(OBJ:%=$(OBJ_DIR)/%)
debug-state: debug-show state.o
	$(CC) $(CFLAG) src/test-state.cpp ${OBJS} -o bin/$(OUT).out
	#state:test-debug-binary: ./bin/$(OUT).out

state: OUT=test-state
state: OBJ=state.o
state: OBJS=$(OBJ:%=$(OBJ_DIR)/%)
state: state.o
	$(CC) $(CFLAG) src/test-state.cpp ${OBJS} -o bin/$(OUT).out
	#state:test-binary: ./bin/$(OUT).out

state.o: inc/state.cpp inc/state.h
	$(CC) ${CFLAG} -c inc/state.cpp -o obj/state.o

debug-tokenizer: OUT=test-tokenizer-debug
debug-tokenizer: CFLAG+= -D DEBUG -g
debug-tokenizer: OBJ=tokenizer.o token.o
debug-tokenizer: OBJS=$(OBJ:%=$(OBJ_DIR)/%)
debug-tokenizer: debug-show tokenizer.o
	$(CC) $(CFLAG) src/test-tokenizer.cpp ${OBJS} -o bin/$(OUT).out
	#tokenizer:test-debug-binary: ./bin/$(OUT).out

tokenizer: OUT=test-tokenizer
tokenizer: OBJ= tokenizer.o token.o
tokenizer: OBJS=$(OBJ:%=$(OBJ_DIR)/%)
tokenizer: debug-show tokenizer.o
	$(CC) $(CFLAG) src/test-tokenizer.cpp ${OBJS} -o bin/$(OUT).out
	#tokenizer:test-binary: ./bin/$(OUT).out

tokenizer.o: token.o inc/tokenizer.cpp inc/tokenizer.h
	$(CC) ${CFLAG} -c inc/tokenizer.cpp -o obj/tokenizer.o

debug-expression: OUT=test-expression-debug
debug-expression: CFLAG+= -D DEBUG -g
debug-expression: OBJ= state.o tokenizer.o error.o expression.o token.o
debug-expression: OBJS=$(OBJ:%=$(OBJ_DIR)/%)
debug-expression: debug-show expression.o
	$(CC) $(CFLAG) src/test-expression.cpp ${OBJS} -o bin/$(OUT).out
	#expression:test-debug-binary: ./bin/$(OUT).out

expression: OUT=test-expression
expression: OBJ= state.o tokenizer.o error.o expression.o token.o
expression: OBJS=$(OBJ:%=$(OBJ_DIR)/%)
expression: debug-show expression.o
	$(CC) $(CFLAG) src/test-expression.cpp ${OBJS} -o bin/$(OUT).out
	#expression:test-binary: ./bin/$(OUT).out

expression.o: state.o tokenizer.o error.o token.o inc/expression.cpp inc/expression.h
	$(CC) ${CFLAG} -c inc/expression.cpp -o obj/expression.o

debug-statement: OUT=test-statement-debug
debug-statement: CFLAG+= -D DEBUG -g
debug-statement: OBJ=expression.o tokenizer.o parse.o state.o token.o error.o statement.o detector.o
debug-statement: OBJS=$(OBJ:%=$(OBJ_DIR)/%)
debug-statement: debug-show detector.o statement.o
	$(CC) $(CFLAG) src/test-statement.cpp ${OBJS} -o bin/$(OUT).out
	#statement:test-debug-binary: ./bin/$(OUT).out

statement: OUT=test-statement
statement: OBJ=expression.o tokenizer.o parse.o state.o token.o error.o statement.o detector.o
statement: OBJS=$(OBJ:%=$(OBJ_DIR)/%)
statement: detector.o statement.o
	$(CC) $(CFLAG) src/test-statement.cpp ${OBJS} -o bin/$(OUT).out
	#statement:test-binary: ./bin/$(OUT).out

statement.o: expression.o tokenizer.o parse.o state.o token.o error.o detector.o inc/statement.cpp inc/statement.h
	$(CC) ${CFLAG} -c inc/statement.cpp -o obj/statement.o

debug-token: token


token: token.o
	#token: No test build configured

token.o: inc/token.cpp inc/token.h
	$(CC) ${CFLAG} -c inc/token.cpp -o obj/token.o

debug-parse: OUT=test-parse-debug
debug-parse: CFLAG+= -D DEBUG -g
debug-parse: OBJ=tokenizer.o expression.o token.o state.o parse.o error.o
debug-parse: OBJS=$(OBJ:%=$(OBJ_DIR)/%)
debug-parse: debug-show state.o parse.o
	$(CC) $(CFLAG) src/test-parse.cpp ${OBJS} -o bin/$(OUT).out
	#parse:test-debug-binary: ./bin/$(OUT).out

parse: OUT=test-parse
parse: OBJ=tokenizer.o expression.o token.o state.o parse.o error.o
parse: OBJS=$(OBJ:%=$(OBJ_DIR)/%)
parse: state.o parse.o
	$(CC) $(CFLAG) src/test-parse.cpp ${OBJS} -o bin/$(OUT).out
	#parse:test-binary: ./bin/$(OUT).out

parse.o: tokenizer.o expression.o token.o error.o inc/parse.cpp inc/parse.h
	$(CC) ${CFLAG} -c inc/parse.cpp -o obj/parse.o

detector: detector.o
    #detector: No test build configured
    
detector.o: inc/detector.cpp inc/detector.h
	$(CC) ${CFLAG} -c inc/detector.cpp -o obj/detector.o


clean: delete all 
	#clean build

delete:
	rm -rf obj/* bin/*

debug-show:
	#debug: enabled